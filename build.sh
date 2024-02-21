#!/bin/bash

g++ -std=c++23 -o main dnsserver.cpp\
 packet/records/additional.cpp\
 packet/records/answer.cpp\
 packet/records/authority.cpp\
 packet/records/question.cpp\
 packet/records/header.cpp\
 packet/records/preamble.cpp\
 packet/dnspacket.cpp\
 utils/binaryreader.cpp\
 utils/binarywriter.cpp\
 sitesnippet/sitesnippet.cpp