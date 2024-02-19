#include "additional.hpp"
#include <iomanip>

Additional::Additional(std::string name, DNSRecordType type, uint16_t class_, uint32_t ttl, uint16_t rdlength, std::shared_ptr<std::vector<uint8_t>> RDATA)
    : Preamble(name, type, class_, ttl, rdlength)
{
    this->RDATA = RDATA;
}

void Additional::print()
{
    std::cout << "---------- Additional ----------" << std::endl;
    Preamble::print();
    std::cout << "RDATA: ";
    for (auto byte : *RDATA)
    {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)byte;
    }
    std::cout << std::endl;
    std::cout << "---------- end Additional ----------" << std::endl;
}