#pragma once

#include <bits/stdint-uintn.h>

class Header
{
public:
	uint16_t id;
	uint16_t flags;
	uint16_t qdcount;
	uint16_t ancount;
	uint16_t nscount;
	uint16_t arcount;

	Header(uint16_t id, uint16_t flags, uint16_t qdcount, uint16_t ancount, uint16_t nscount, uint16_t arcount);

	Header();

	~Header();

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
