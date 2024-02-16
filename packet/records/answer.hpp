#pragma once

#include <bits/stdint-uintn.h>
#include "preamble.hpp"
#include "answer/arecord.hpp"
#include "answer/aaaarecord.hpp"

class Answer : public Preamble
{
public:
    Answer(std::string name, DNSRecordType type, uint16_t class_, uint32_t ttl, uint16_t rdlength);
    void print() override;
    virtual uint8_t *getIP();

    static Answer getAnswer(std::string name, DNSRecordType type, uint16_t class_, uint32_t ttl, uint16_t rdlength, uint8_t IP[])
    {
        switch (type) {
            case DNSRecordType::A:
                return ARecord(name, type, class_, ttl, rdlength, IP);
            case DNSRecordType::AAAA:
                return AAAARecord(name, type, class_, ttl, rdlength, IP);
            default:
                throw std::invalid_argument("Invalid DNSRecordType");
        }
    }
};
