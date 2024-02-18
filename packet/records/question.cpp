#include "question.hpp"

#include <regex>

Question::Question(std::string qname, DNSRecordType qtype, uint16_t qclass)
{
	this->qname = qname;
	this->qtype = qtype;
	this->qclass = qclass;
}

Question::~Question()
{
}

std::string Question::qNameFormat()
{
    std::string result = qname.substr(1);\
    for (int i = 0; i < result.length(); i++)
    {
        if (result[i] < 20)
        {
            result[i] = '.';
        }
    }

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
