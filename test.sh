#!/usr/bin/env bash

# Clean the previous builds
rm main

# Compile the code with the debug flag
clang++ src/main.cpp -o main -std=c++26 -Wall -Wextra -O2 -pthread -D DEBUG=1

# Run the code
./main

# Run the run code and quit to make sure it launches
# TODO: Make sure this code can exit on its own
./run.sh

# Format the code
# CREDIT: https://leimao.github.io/blog/Clang-Format-Quick-Tutorial/
find . -regex '.*\.\(cpp\|hpp\|cu\|cuh\|c\|h\)' -exec clang-format -style=file -i {} \;
