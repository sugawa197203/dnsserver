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
	BinaryWriter(uint8_t *head, int length, std::endian endian = std::endian::big);

	~BinaryWriter();

	void writeUInt8(uint8_t value);

	void writeUInt16(uint16_t value);

	void writeUInt32(uint32_t value);

	void writeString(std::string value);

	void writeBytes(uint8_t *value, int length);

	int getPosition();

	int getLength();
};
