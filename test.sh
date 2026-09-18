#!/usr/bin/env bash

# Clean the previous builds
rm main

# Compile the code
clang++ src/main.cpp -o main -std=c++26 -Wall -Wextra -O2 -pthread -D DEBUG=1

# Run the code
./main

# Format the code
# CREDIT: https://leimao.github.io/blog/Clang-Format-Quick-Tutorial/
find . -regex '.*\.\(cpp\|hpp\|cu\|cuh\|c\|h\)' -exec clang-format -style=file -i {} \;
