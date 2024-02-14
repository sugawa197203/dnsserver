#include "question.hpp"

#include <regex>

Question::Question(std::string qname, uint16_t qtype, uint16_t qclass)
{
	this->qname = qname;
	this->qtype = qtype;
	this->qclass = qclass;
}

Question::~Question()
{
}

void Question::setQName(char *qname)
{
	this->qname = qname;
}

void Question::setQType(uint16_t qtype)
{
	this->qtype = qtype;
}

void Question::setQClass(uint16_t qclass)
{
	this->qclass = qclass;
}

std::string Question::getQName()
{
	return qname;
}

uint16_t Question::getQType()
{
	return qtype;
}

uint16_t Question::getQClass()
{
	return qclass;
}

std::string Question::qNameFormat()
{
	std::string result = qname;
	// to lower case
	std::transform(result.begin(), result.end(), result.begin(), ::tolower);
	// replace 0x03 with '.'
	std::regex re("\\x03");
	result = std::regex_replace(result, re, ".");
	// remove control characters
	re = std::regex("[\\x00-\\x1F]");
	result = std::regex_replace(result, re, "");
	return result;
}

void Question::print()
{
	std::cout << "---------- DNS Question ----------" << std::endl;
	std::cout << "QName: " << qNameFormat() << std::endl;
	std::cout << "QType: " << qtype << std::endl;
	std::cout << "QClass: " << qclass << std::endl;
	std::cout << "----------------------------------" << std::endl;
}
