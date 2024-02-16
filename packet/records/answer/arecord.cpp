#include "arecord.hpp"
#include "../preamble.hpp"

#include <iostream>

ARecord::ARecord(std::string name, DNSRecordType type, uint16_t class_, uint32_t ttl, uint16_t rdlength, uint8_t IP[4])
    : Answer(name, type, class_, ttl, rdlength)
{
    for (int i = 4; i; i--)
    {
        this->IP[i] = IP[i];
    }
}

ARecord::~ARecord()
{

}

uint8_t *ARecord::getIP()
{
    return IP;
}

void ARecord::print()
{
    std::cout << "----------Answer A Record ----------" << std::endl;
    Answer::print();
    std::cout << "IP: " << (int)IP[0] << "." << (int)IP[1] << "." << (int)IP[2] << "." << (int)IP[3] << std::endl;
    std::cout << "--------------------------------" << std::endl;
}