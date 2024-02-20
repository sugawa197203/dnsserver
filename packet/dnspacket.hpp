#pragma once

#include "records/header.hpp"
#include "records/question.hpp"
#include "records/answer.hpp"
#include "records/authority.hpp"
#include "records/additional.hpp"
#include "../utils/binaryreader.hpp"
#include "../utils/binarywriter.hpp"
#include <list>
#include <memory>

class DNSPacket
{
public:
	Header header;
	std::list<Question> questions;
	std::list<Answer> answers;
	std::list<Authority> authorities;
	std::list<Additional> additionals;

	DNSPacket();

	~DNSPacket();

	void fromBinary(uint8_t *binary, ssize_t length);

	ssize_t toBinary(uint8_t *binary, ssize_t length);

	void print();
};