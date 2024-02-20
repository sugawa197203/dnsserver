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

    [[maybe_unused]] Header(uint16_t id, uint16_t flags, uint16_t qdcount, uint16_t ancount, uint16_t nscount, uint16_t arcount);

	Header();

	~Header();

    [[maybe_unused]] [[nodiscard]] bool getQR() const;

    [[maybe_unused]] [[nodiscard]] uint8_t getOpcode() const;

    [[maybe_unused]] [[nodiscard]] bool getAA() const;

    [[maybe_unused]] [[nodiscard]] bool getTC() const;

    [[maybe_unused]] [[nodiscard]] bool getRD() const;

    [[maybe_unused]] [[nodiscard]] bool getRA() const;

    [[maybe_unused]] [[nodiscard]] bool getZ() const;

    [[maybe_unused]] [[nodiscard]] bool getAD() const;

    [[maybe_unused]] [[nodiscard]] bool getCD() const;

    [[maybe_unused]] [[nodiscard]] uint8_t getRCODE() const;

	void setQR(bool qr);

    [[maybe_unused]] void setOpcode(uint8_t opcode);

    [[maybe_unused]] void setAA(bool aa);

    [[maybe_unused]] void setTC(bool tc);

	void setRD(bool rd);

    [[maybe_unused]] void setRA(bool ra);

    [[maybe_unused]] void setZ(bool z);

    [[maybe_unused]] void setAD(bool ad);

    [[maybe_unused]] void setCD(bool cd);

    [[maybe_unused]] void setRCODE(uint8_t rcode);

	void print() const;
};
