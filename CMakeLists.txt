cmake_minimum_required(VERSION 3.13)
project(dnsserver CXX)
add_executable(
	dnsserver
	dnsserver.cpp
	records/records.cpp
	utils/binaryreader.cpp
	utils/binarywriter.cpp
	)