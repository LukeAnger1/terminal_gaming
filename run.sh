#!/usr/bin/env bash

# Clean the previous builds
rm main

# Compile the code
# clang++ src/main.cpp -o main -std=c++26 -Wall -Wextra -O2 -pthread
# NOTE: Temporarily changing compilers because there is a system issue with clang++ on my laptop
g++ src/main.cpp -o main -std=c++20 -Wall -Wextra -O2 -pthread

# Run the code
./main
