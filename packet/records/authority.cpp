#include "authority.hpp"
#include <iomanip>
#include <utility>

Authority::Authority(std::string name, DNSRecordType type, uint16_t class_, uint32_t ttl, uint16_t rdlength, std::shared_ptr<std::vector<uint8_t>> RDATA)
    : Preamble(std::move(name), type, class_, ttl, rdlength)
{
    this->RDATA = std::move(RDATA);
}

void Authority::print()
{
    std::cout << "---------- Authority ----------" << std::endl;
    Preamble::print();
    std::cout << "RDATA: ";
    for (auto byte : *RDATA)
    {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)byte;
    }
    std::cout << std::endl;
    std::cout << "---------- end Authority ----------" << std::endl;
}