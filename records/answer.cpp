#include "answer.hpp"

#include <arpa/inet.h>
#include <netinet/in.h>

Answer::Answer()
{
	name = nullptr;
	type = 0;
	class_ = 0;
	ttl = 0;
	rdlength = 0;
	IP = 0;
}

Answer::Answer(std::string name, uint16_t type, uint16_t class_, uint32_t ttl, uint16_t rdlength, uint32_t IP)
{
	this->name = name;
	this->type = type;
	this->class_ = class_;
	this->ttl = ttl;
	this->rdlength = rdlength;
	this->IP = IP;
}

Answer::~Answer()
{
}

void Answer::setName(std::string name)
{
	this->name = name;
}

std::string Answer::getName()
{
	return name;
}

void Answer::setIP(uint32_t IP)
{
	this->IP = IP;
}

uint32_t Answer::getIP()
{
	return IP;
}

void Answer::print()
{
	struct in_addr IP;
	IP.s_addr = this->IP;
	std::cout << "---------- DNS Answer ----------" << std::endl;
	Preamble::print();
	std::cout << "IP: " << inet_ntoa(IP) << std::endl;
	std::cout << "--------------------------------" << std::endl;
}
