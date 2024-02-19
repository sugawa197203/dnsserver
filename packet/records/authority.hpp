#pragma once

#include <bits/stdint-uintn.h>
#include <vector>
#include <memory>
#include "preamble.hpp"

class Authority : public Preamble
{
public:
    std::shared_ptr<std::vector<uint8_t>> RDATA;

    Authority(std::string name, DNSRecordType type, uint16_t class_, uint32_t ttl, uint16_t rdlength, std::shared_ptr<std::vector<uint8_t>> RDATA);
    void print() override;
};