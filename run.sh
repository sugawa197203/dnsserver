#!/bin/bash
@echo off
echo "Running the script"
cmake -S . -B build && cmake --build build && ./build/dnsserver