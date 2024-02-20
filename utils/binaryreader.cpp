#include <iostream>
#include <string>
#include <bit>
#include <byteswap.h>
#include "binaryreader.hpp"

bool BinaryReader::isOutOfBounds()
{
	return pos > head + length;
}

bool BinaryReader::isEOF()
{
	return pos == head + length;
}

BinaryReader::BinaryReader(uint8_t *head, ssize_t length, std::endian endian = std::endian::big)
{
	this->head = head;
	this->pos = head;
	this->length = length;
	this->endian = endian;
}

BinaryReader::~BinaryReader() = default;

[[maybe_unused]] ssize_t BinaryReader::getLength() const
{
	return length;
}

[[maybe_unused]] ssize_t BinaryReader::getPosition()
{
	return pos - head;
}

template <typename T>
[[maybe_unused]] T BinaryReader::read()
{
	if (isEOF())
	{
		throw std::out_of_range("End of file");
	}

	T value = *reinterpret_cast<T *>(pos);
	pos += sizeof(T);
	if (isOutOfBounds())
	{
		pos -= sizeof(T);
		throw std::out_of_range("Out of bounds");
	}
	return value;
}

[[maybe_unused]] uint8_t BinaryReader::readUInt8()
{
	if (isEOF())
	{
		throw std::out_of_range("End of file");
	}
	uint8_t value = *reinterpret_cast<uint8_t *>(pos);
	pos += sizeof(uint8_t);
	if (isOutOfBounds())
	{
		pos -= sizeof(uint8_t);
		throw std::out_of_range("Out of bounds readUInt8");
	}
	return value;
}

uint16_t BinaryReader::readUInt16()
{
	if (isEOF())
	{
		throw std::out_of_range("End of file");
	}
	uint16_t value = *reinterpret_cast<uint16_t *>(pos);
	pos += sizeof(uint16_t);
	if (isOutOfBounds())
	{
		pos -= sizeof(uint16_t);
		throw std::out_of_range("Out of bounds readUInt16");
	}
	return endian == std::endian::big ? bswap_16(value) : value;
}

[[maybe_unused]] uint32_t BinaryReader::readUInt32()
{
	if (isEOF())
	{
		throw std::out_of_range("End of file");
	}
	uint32_t value = *reinterpret_cast<uint32_t *>(pos);
	pos += sizeof(uint32_t);
	if (isOutOfBounds())
	{
		pos -= sizeof(uint32_t);
		throw std::out_of_range("Out of bounds readUInt32");
	}
	return endian == std::endian::big ? bswap_32(value) : value;
}

[[maybe_unused]] uint64_t BinaryReader::readUInt64()
{
	if (isEOF())
	{
		throw std::out_of_range("End of file");
	}
	uint64_t value = *reinterpret_cast<uint64_t *>(pos);
	pos += sizeof(uint64_t);
	if (isOutOfBounds())
	{
		pos -= sizeof(uint64_t);
		throw std::out_of_range("Out of bounds readUInt64");
	}
	return endian == std::endian::big ? bswap_64(value) : value;
}

std::string BinaryReader::readString()
{
	if (isEOF())
	{
		throw std::out_of_range("End of file");
	}
	std::string value = (char *)pos;
	pos += value.length() + 1;
	if (isOutOfBounds())
	{
		pos -= value.length() + 1;
		throw std::out_of_range("Out of bounds readString");
	}
	return value;
}
