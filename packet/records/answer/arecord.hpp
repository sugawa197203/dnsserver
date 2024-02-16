#pragma once

#include <bits/stdint-uintn.h>
#include "../answer.hpp"

class ARecord : public Answer {
public:
    uint8_t IP[4];

    ARecord(std::string name, DNSRecordType type, uint16_t class_, uint32_t ttl, uint16_t rdlength, uint8_t IP[4]);

    ~ARecord();

    uint8_t *getIP() override;

    void print() override;
};
