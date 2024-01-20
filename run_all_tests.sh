#!/bin/bash

# Author: Peter Arandorenko
# Date: January 26, 2024

# Compile and run all .cpp files with main() in the tests directory

for file in *.cpp; do
    # Extract the filename without extension
    filename=$(basename -- "$file")
    extension="${filename##*.}"
    filename="${filename%.*}"

    # Compile the .cpp file
    if g++ -fdiagnostics-color=always -g -std=c++17 -o bin/"$filename" "$file" -lgtest -lgtest_main -pthread; then #-v
        # Run the resulting executable if compilation succeeds
        bin/"$filename"
    else
        echo "Compilation failed for $file"
    fi
done
