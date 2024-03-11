#!/bin/bash

RED="\033[5;31m"
NORMAL="\033[0m"

echo "Beep boop. Ova skripta će testirati Vaš kod"

tests_dir="tests"

test_files=$(find $tests_dir -type f -name "test*cpp" | sort)

for test_file in ${test_files}; do
  echo "Compiling ${test_file}..."
  if clang++ "$test_file" duration.cpp -o "${test_file%.cpp}" &> /dev/null; then 
      echo "Running $test_file"
      "./${test_file%.cpp}"
      "rm ${test_file%.cpp}"
  else
      echo -e "${RED}Desio se problem pri kompajliranju. Ovaj test primjer možete ručno kompajlirati komandom:"\
      "clang++ $test_file duration.cpp ili pogledajte file: ${test_file}${NORMAL}"
  fi
done
