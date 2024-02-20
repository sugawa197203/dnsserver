cmake_minimum_required(VERSION 3.13)
project(dnsserver CXX)
set(CMAKE_CXX_STANDARD 23)
add_executable(dnsserver
	dnsserver.cpp
	packet/records/additional.cpp
	packet/records/answer.cpp
	packet/records/authority.cpp
	packet/records/question.cpp
	packet/records/header.cpp
	packet/records/preamble.cpp
	packet/dnspacket.cpp
	utils/binaryreader.cpp
	utils/binarywriter.cpp
	sitesnippet/sitesnippet.hpp
	sitesnippet/sitesnippet.cpp
)
