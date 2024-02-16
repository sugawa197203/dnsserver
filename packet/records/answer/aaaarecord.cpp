#include "aaaarecord.hpp"
#include "../preamble.hpp"

#include <iostream>

AAAARecord::AAAARecord(std::string name, DNSRecordType type, uint16_t class_, uint32_t ttl, uint16_t rdlength, uint8_t IP[16])
    : Answer(name, type, class_, ttl, rdlength)
{
    for (int i = 16; i; i--)
    {
        this->IP[i] = IP[i];
    }
}

AAAARecord::~AAAARecord()
{

}

uint8_t *AAAARecord::getIP()
{
    return IP;
}

void AAAARecord::print()
{
    std::cout << "----------Answer AAAA Record ----------" << std::endl;
    Answer::print();
    std::cout << "IP: ";
    for (int i = 0; i < 16; i++)
    {
        std::cout << std::hex << (int)IP[i];
        if (i != 15)
        {
            std::cout << ":";
        }
    }
    std::cout << std::dec << std::endl;
    std::cout << "--------------------------------" << std::endl;
}
