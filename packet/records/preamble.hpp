#pragma once

#include <string>
#include <iostream>

class Preamble
{
public:
	std::string name;
	uint16_t type;
	uint16_t class_;
	uint32_t ttl;
	uint16_t rdlength;

	Preamble(std::string name, uint16_t type, uint16_t class_, uint32_t ttl, uint16_t rdlength);

    Preamble();
    ~Preamble();

	void print();
};
