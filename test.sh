#!/usr/bin/env bash

# Clean the previous builds
rm main

# Compile the code
clang++ src/main.cpp -o main -std=c++26 -Wall -Wextra -O2 -pthread -D DEBUG=1

# Run the code
./main
