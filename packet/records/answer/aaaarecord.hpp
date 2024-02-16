#pragma once

#include <bits/stdint-uintn.h>
#include "../answer.hpp"

class AAAARecord : public Answer
{
public:
    uint8_t IP[16];

    AAAARecord(std::string name, DNSRecordType type, uint16_t class_, uint32_t ttl, uint16_t rdlength, uint8_t IP[16]);

    ~AAAARecord();

    uint8_t *getIP() override;

    void print() override;
};
