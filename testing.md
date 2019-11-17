# Testing

We use [Catch 2.11.0](https://github.com/catchorg/Catch2) for testing. The test script `test.sh` downloads this version by itself, if needed.

## Running the tests with docker

Running the test once:
```
docker run --rm -it -v ${PWD}:/app -w /app --entrypoint tests.sh gcc:4.9.2
```

Using the running docker container to execute tests:
```
docker run --rm -it -v ${PWD}:/app -w /app --entrypoint bash gcc:4.9.2
# then use the bash from docker to run:
./tests.sh
```
