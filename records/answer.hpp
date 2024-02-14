#pragma once

#include <bits/stdint-uintn.h>
#include "preamble.hpp"

class Answer : Preamble
{
private:
	uint32_t IP;

public:
	Answer();

	Answer(std::string name, uint16_t type, uint16_t class_, uint32_t ttl, uint16_t rdlength, uint32_t IP);

	~Answer();

	void setName(std::string name);

	std::string getName();

	void setIP(uint32_t IP);

	uint32_t getIP();

	void print();
};
