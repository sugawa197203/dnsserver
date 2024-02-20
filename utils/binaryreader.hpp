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
	ssize_t length;
	std::endian endian;

	bool isOutOfBounds();

public:
	bool isEOF();

	BinaryReader(uint8_t *head, ssize_t length, std::endian endian);

	~BinaryReader();

    [[maybe_unused]] [[nodiscard]] ssize_t getLength() const;

    [[maybe_unused]] ssize_t getPosition();

	template <typename T>
    [[maybe_unused]] T read();

    [[maybe_unused]] uint8_t readUInt8();

	uint16_t readUInt16();

    [[maybe_unused]] uint32_t readUInt32();

    [[maybe_unused]] uint64_t readUInt64();

	std::string readString();
};