#pragma once

#include <iostream>
#include <string>
#include <bit>
#include <byteswap.h>

class BinaryWriter
{
private:
	uint8_t *head;
	uint8_t *pos;
	int length;
	std::endian endian;

public:
	BinaryWriter(uint8_t *head, int length, std::endian endian);

	~BinaryWriter();

	void writeUInt8(uint8_t value);

	void writeUInt16(uint16_t value);

	void writeUInt32(uint32_t value);

	void writeString(const std::string& value);

    [[maybe_unused]] void writeBytes(const uint8_t *value, int valueLength);

	int getPosition();

    [[maybe_unused]] [[maybe_unused]] [[nodiscard]] int getLength() const;
};
