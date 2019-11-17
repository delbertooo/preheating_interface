#!/bin/bash

set -xe

info() {
    echo -e "\e[32m$1\e[0m"
}

if [ ! -f tests/catch.hpp ]; then
    info "Downloading Catch2..."
    wget -O tests/catch.hpp https://github.com/catchorg/Catch2/releases/download/v2.11.0/catch.hpp
    echo "c3e164751617483c25d42f7f71254d5e5ba39f6b4245c2cfd6cc7ea8d3918cad  tests/catch.hpp" | sha256sum -c
fi

info "Building tests..."
mkdir -p build
# Arduino IDE's arguments would be like:
#-g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto
g++ -std=gnu++11\
    -o build/run-tests tests/tests.cpp

info "Running tests..."
./build/run-tests
