#include "header.hpp"
#include <iostream>
#include <iomanip>

Header::Header(uint16_t id, uint16_t flags, uint16_t qdcount, uint16_t ancount, uint16_t nscount, uint16_t arcount)
{
	this->id = id;
	this->flags = flags;
	this->qdcount = qdcount;
	this->ancount = ancount;
	this->nscount = nscount;
	this->arcount = arcount;
}

Header::Header()
{
	id = 0;
	flags = 0;
	qdcount = 0;
	ancount = 0;
	nscount = 0;
	arcount = 0;
}

Header::~Header() {}

bool Header::getQR()
{
	return (flags & 0x8000) >> 15;
}

uint8_t Header::getOpcode()
{
	return (flags & 0x7800) >> 11;
}

bool Header::getAA()
{
	return (flags & 0x0400) >> 10;
}

bool Header::getTC()
{
	return (flags & 0x0200) >> 9;
}

bool Header::getRD()
{
	return (flags & 0x0100) >> 8;
}

bool Header::getRA()
{
	return (flags & 0x0080) >> 7;
}

bool Header::getZ()
{
	return (flags & 0x0070) >> 4;
}

bool Header::getAD()
{
	return (flags & 0x0020) >> 5;
}

bool Header::getCD()
{
	return (flags & 0x0010) >> 4;
}

uint8_t Header::getRCODE()
{
	return flags & 0x000F;
}

void Header::setQR(bool qr)
{
	flags = (flags & 0x7FFF) | (qr << 15);
}

void Header::setOpcode(uint8_t opcode)
{
	flags = (flags & 0x87FF) | (opcode << 11);
}

void Header::setAA(bool aa)
{
	flags = (flags & 0xFBFF) | (aa << 10);
}

void Header::setTC(bool tc)
{
	flags = (flags & 0xFDFF) | (tc << 9);
}

void Header::setRD(bool rd)
{
	flags = (flags & 0xFEFF) | (rd << 8);
}

void Header::setRA(bool ra)
{
	flags = (flags & 0xFF7F) | (ra << 7);
}

void Header::setZ(bool z)
{
	flags = (flags & 0xFFF0) | (z << 4);
}

void Header::setAD(bool ad)
{
	flags = (flags & 0xFFDF) | (ad << 5);
}

void Header::setCD(bool cd)
{
	flags = (flags & 0xFFEF) | (cd << 4);
}

void Header::setRCODE(uint8_t rcode)
{
	flags = (flags & 0xFFF0) | rcode;
}

void Header::print()
{
	std::cout << "---------- DNS Header ----------" << std::endl;
	std::cout << "ID: " << id << std::endl;
	std::cout << "Flags: " << std::setfill('0') << std::setw(4) << std::right << std::hex << flags << std::endl;
	std::cout << "\tQR: " << ((flags & 0x8000) >> 15) << std::endl;
	std::cout << "\tOpcode: " << std::setfill('0') << std::setw(4) << std::right << ((flags & 0x7800) >> 11) << std::endl;
	std::cout << "\tAA: " << ((flags & 0x0400) >> 10) << std::endl;
	std::cout << "\tTC: " << ((flags & 0x0200) >> 9) << std::endl;
	std::cout << "\tRD: " << ((flags & 0x0100) >> 8) << std::endl;
	std::cout << "\tRA: " << ((flags & 0x0080) >> 7) << std::endl;
	std::cout << "\tZ: " << ((flags & 0x0070) >> 4) << std::endl;
	std::cout << "\tRCODE: " << std::setfill('0') << std::setw(4) << std::right << (flags & 0x000F) << std::endl;
	std::cout << "QDCount: " << qdcount << std::endl;
	std::cout << "ANCount: " << ancount << std::endl;
	std::cout << "NSCount: " << nscount << std::endl;
	std::cout << "ARCount: " << arcount << std::endl;
	std::cout << "--------------------------------" << std::endl;
}
