#!/bin/bash

function run_test() {
  name=$1
  if [ -f "$name" ]; then
    echo "Compiling $name..."
    g++ -std=c++11 "$name" -o "${name%.cpp}"
    if [ $? -eq 0 ]; then
      echo "Running $name..."
      "./${name%.cpp}"
      rm ${name%.cpp}
    else
      echo -e "\033[5;31mTest is unsucessfull. Be sure that you implemented all methods required in test!\033[0m"
      echo -e "\033[5;31mFollow \"Undefined symbol\" error message. That means that you are missing implementation of that method that is specified!\033[0m"
      exit 1
    fi
    else
        echo "Test file $filename not found."
    fi
}

if [ $# -gt 1 ]; then
  echo -e "\033[5;31mInvalid number of arguments!\033[0m"
  exit 1
fi
dir="tests/"
# run specific test
if [ $# -eq 1 ]; then
  filename="Test$1.cpp"
  run_test $dir$filename
# run all tests
else
num_of_tests=$(ls ./tests | wc -l)
for (( i = 1; i <= $num_of_tests - 1; i++ )); do
  filename="Test$i.cpp"
  run_test $dir$filename
done
fi
