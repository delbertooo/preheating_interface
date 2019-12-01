#!/bin/bash

set -e

info() {
    echo -e "\e[32m$1\e[0m"
}

usage() {
    echo "usage: tests.sh [-l|--loop] [--debug] [-h|--help]"
}

prepare() {
    if [ ! -f tests/catch.hpp ]; then
        info "Downloading Catch2..."
        wget -O tests/catch.hpp https://github.com/catchorg/Catch2/releases/download/v2.11.0/catch.hpp
        echo "c3e164751617483c25d42f7f71254d5e5ba39f6b4245c2cfd6cc7ea8d3918cad  tests/catch.hpp" | sha256sum -c
    fi
}

run() {
    info "Building tests..."
    mkdir -p build
    # Arduino IDE's arguments would be like:
    #-g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto
    g++ -std=gnu++11\
        -o build/run-tests tests/tests.cpp tests/PowerOnCommandTest.cpp

    if [ "$?" == "0" ]; then
        info "Running tests..."
        ./build/run-tests
    else
        info "Error building the tests :("
    fi
}

do_loop=0
while [ "$1" != "" ]; do
    case $1 in
        -l | --loop )           do_loop=1
                                ;;
        --debug     )           set -x
                                ;;
        -h | --help )           usage
                                exit
                                ;;
        * )                     usage
                                exit 1
    esac
    shift
done

prepare


if [ "$do_loop" == "1" ]; then
    set +e
    while true
    do
        run
        echo "Press [Enter] to re-run the tests or input 'q' to exit."
        read line
        if [ "$line" == "q" ] || [ "$line" == "quit" ] || [ "$line" == "exit" ]; then break; fi
    done
else
    run
fi
