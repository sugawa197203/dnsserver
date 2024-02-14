#pragma once

#include <iostream>
#include <string>
#include <bit>
#include <byteswap.h>

class BinaryReader
{
private:
	uint8_t *head;
	uint8_t *pos;
	int length;
	std::endian endian;

	bool isOutOfBounds()
	{
		return pos > head + length;
	}

public:
	bool isEOF();

	BinaryReader(uint8_t *head, int length, std::endian endian = std::endian::big);

	~BinaryReader();

	int getLength();

	int getPosition();

	template <typename T>
	T read();

	uint8_t readUInt8();

	uint16_t readUInt16();

	uint32_t readUInt32();

	uint64_t readUInt64();

	std::string readString();
};