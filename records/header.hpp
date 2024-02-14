#pragma once

#include <bits/stdint-uintn.h>

class DNSHeader
{
private:
	uint16_t id;
	uint16_t flags;
	uint16_t qdcount;
	uint16_t ancount;
	uint16_t nscount;
	uint16_t arcount;

public:
	DNSHeader(uint16_t id, uint16_t flags, uint16_t qdcount, uint16_t ancount, uint16_t nscount, uint16_t arcount);

	DNSHeader();

	~DNSHeader();

	void setID(uint16_t id);

	void setFlags(uint16_t flags);

	void setQDCount(uint16_t qdcount);

	void setANCount(uint16_t ancount);

	void setNSCount(uint16_t nscount);

	void setARCount(uint16_t arcount);

	uint16_t getID();

	uint16_t getFlags();

	uint16_t getQDCount();

	uint16_t getANCount();

	uint16_t getNSCount();

	uint16_t getARCount();

	bool getQR();

	uint8_t getOpcode();

	bool getAA();

	bool getTC();

	bool getRD();

	bool getRA();

	bool getZ();

	bool getAD();

	bool getCD();

	uint8_t getRCODE();

	void setQR(bool qr);

	void setOpcode(uint8_t opcode);

	void setAA(bool aa);

	void setTC(bool tc);

	void setRD(bool rd);

	void setRA(bool ra);

	void setZ(bool z);

	void setAD(bool ad);

	void setCD(bool cd);

	void setRCODE(uint8_t rcode);

	void print();
};
