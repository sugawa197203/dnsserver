#include "answer.hpp"

#include <arpa/inet.h>
#include <netinet/in.h>

#include <utility>

Answer::Answer(std::string name, DNSRecordType type, uint16_t class_, uint32_t ttl, uint16_t rdlength, uint32_t IP)
    : Preamble(std::move(name), type, class_, ttl, rdlength)
{
    this->IP = IP;
}

void Answer::print()
{
    std::cout << "---------- Answer ----------" << std::endl;
    Preamble::print();
    std::cout << "IP: " << inet_ntoa(*(in_addr *)&IP) << std::endl;
    std::cout << "---------- end Answer ----------" << std::endl;
}
