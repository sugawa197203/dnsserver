#include "answer.hpp"

#include <arpa/inet.h>
#include <netinet/in.h>


Answer::Answer(std::string name, uint16_t type, uint16_t class_, uint32_t ttl, uint16_t rdlength, uint32_t IP) : Preamble(name, type, class_, ttl, rdlength)
{
	this->IP = IP;
}

Answer::~Answer()
{
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
