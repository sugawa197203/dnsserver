#pragma once

#include <string>
#include <iostream>

class Preamble
{
protected:
	std::string name;
	uint16_t type;
	uint16_t class_;
	uint32_t ttl;
	uint16_t rdlength;

public:
	Preamble();

	Preamble(std::string name, uint16_t type, uint16_t class_, uint32_t ttl, uint16_t rdlength);

	~Preamble();

	void setName(std::string name);

	std::string getName();

	void setType(uint16_t type);

	uint16_t getType();

	void setClass(uint16_t class_);

	uint16_t getClass();

	void setTTL(uint32_t ttl);

	uint32_t getTTL();

	void setRDLength(uint16_t rdlength);

	uint16_t getRDLength();

	void print();
};
