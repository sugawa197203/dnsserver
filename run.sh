#!/bin/bash
echo "Running the script"
cmake -S . -B build && cmake --build build && ./build/dnsserver 2> debug.log