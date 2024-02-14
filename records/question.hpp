#pragma once

#include <bits/stdint-uintn.h>
#include <string>
#include <iostream>

class Question
{
private:
	std::string qname;
	uint16_t qtype;
	uint16_t qclass;

public:
	Question(std::string qname, uint16_t qtype, uint16_t qclass);

	~Question();

	void setQName(char *qname);

	void setQType(uint16_t qtype);

	void setQClass(uint16_t qclass);

	std::string getQName();

	uint16_t getQType();

	uint16_t getQClass();

	std::string qNameFormat();

	void print();
};
