#include "answer.hpp"
#include "answer/arecord.hpp"
#include "answer/aaaarecord.hpp"

#include <arpa/inet.h>
#include <netinet/in.h>

Answer::Answer(std::string name, DNSRecordType type, uint16_t class_, uint32_t ttl, uint16_t rdlength)
    : Preamble(name, type, class_, ttl, rdlength)
{
}



void Answer::print()
{
    Preamble::print();
}
