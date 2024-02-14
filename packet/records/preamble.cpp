#include <string>
#include <iostream>
#include "preamble.hpp"
#include <iomanip>

Preamble::Preamble()
{
	name = nullptr;
	type = 0;
	class_ = 0;
	ttl = 0;
	rdlength = 0;
}

Preamble::Preamble(std::string name, uint16_t type, uint16_t class_, uint32_t ttl, uint16_t rdlength)
{
	this->name = name;
	this->type = type;
	this->class_ = class_;
	this->ttl = ttl;
	this->rdlength = rdlength;
}

Preamble::~Preamble()
{
}

void Preamble::print()
{
	std::cout << "Name: " << name << std::endl;
	std::cout << "Type: " << type << std::endl;
	std::cout << "Class: " << class_ << std::endl;
	std::cout << "TTL: " << ttl << std::endl;
	std::cout << "RDLength: " << rdlength << std::endl;
}
