#pragma once

#include "../dnspacketutil.hpp"
#include <string>
#include <iostream>

class Preamble
{
public:
	std::string name;
	DNSRecordType type;
	uint16_t class_;
	uint32_t ttl;
	uint16_t rdlength;

	Preamble(std::string name, DNSRecordType type, uint16_t class_, uint32_t ttl, uint16_t rdlength);

    Preamble();
    ~Preamble();

    virtual void print();
};
