#pragma once

#include <bits/stdint-uintn.h>
#include <string>
#include <iostream>
#include "../dnspacketutil.hpp"

class Question
{
public:
	std::string qname;
	DNSRecordType qtype;
	uint16_t qclass;

	Question(std::string qname, DNSRecordType qtype, uint16_t qclass);

	~Question();

	[[nodiscard]] std::string qNameFormat() const;

	void print() const;
};
