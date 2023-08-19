#!/bin/bash

c_files=$(ls *.c)
script_file=$(basename "$0")

for file in $c_files; do
  if [ "$file" != "$script_file" ]; then
    echo "Running test for $file"
    gcc "$file" ../../string-utilities.c -g -O3 -fanalyzer && valgrind -q ./a.out && rm a.out
  fi
done