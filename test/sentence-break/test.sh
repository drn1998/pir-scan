#!/bin/bash

files=$(ls)
script_file=$(basename "$0")

for file in $files; do
  if [ -f "$file" ] && [ "$file" != "$script_file" ]; then
    echo "Running test for $file"
    gcc "$file" ../../sentence-break.c ../../string-utilities.c -g -O3 -fanalyzer && valgrind -q ./a.out && rm a.out
  fi
done
