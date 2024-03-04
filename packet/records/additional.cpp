#include "additional.hpp"
#include <iomanip>
#include <utility>

Additional::Additional(std::string name, DNSRecordType type, uint16_t class_, uint32_t ttl, uint16_t rdlength, std::shared_ptr<std::vector<uint8_t>> RDATA)
    : Preamble(std::move(name), type, class_, ttl, rdlength)
{
    this->RDATA = std::move(RDATA);
}

Additional::Additional()
    : Preamble()
{
}

void Additional::print()
{
    std::cout << "---------- Additional ----------" << std::endl;
    Preamble::print();
    std::string RDATAstr(RDATA->begin(), RDATA->end());
    std::cout << "RDATA: " << RDATAstr << std::endl;
    std::cout << "---------- end Additional ----------" << std::endl;
}