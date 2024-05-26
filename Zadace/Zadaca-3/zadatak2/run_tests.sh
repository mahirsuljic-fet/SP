#!/bin/bash

g++ tests/test.cpp tests/Test.cpp Number.cpp -o tests/test_temp
./tests/test_temp
rm tests/test_temp
