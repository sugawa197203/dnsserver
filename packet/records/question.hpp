#pragma once

#include <bits/stdint-uintn.h>
#include <string>
#include <iostream>

class Question
{
public:
	std::string qname;
	uint16_t qtype;
	uint16_t qclass;

	Question(std::string qname, uint16_t qtype, uint16_t qclass);

	~Question();

	std::string qNameFormat();

	void print();
};
