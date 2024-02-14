#pragma once

#include <bits/stdint-uintn.h>
#include "preamble.hpp"

class Answer : public Preamble
{
public:
	uint32_t IP;

	Answer();

	Answer(std::string name, uint16_t type, uint16_t class_, uint32_t ttl, uint16_t rdlength, uint32_t IP);

	~Answer();

	void print();
};
