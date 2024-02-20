#include <string>
#include <bit>
#include "binarywriter.hpp"

BinaryWriter::BinaryWriter(uint8_t *head, int length, std::endian endian = std::endian::big)
{
	this->head = head;
	this->pos = head;
	this->length = length;
	this->endian = endian;
}

BinaryWriter::~BinaryWriter() = default;

void BinaryWriter::writeUInt8(uint8_t value)
{
	*pos = value;
	pos++;
}

void BinaryWriter::writeUInt16(uint16_t value)
{
	if (endian == std::endian::big)
	{
		*pos = (value >> 8) & 0xff;
		pos++;
		*pos = value & 0xff;
		pos++;
	}
	else
	{
		*pos = value & 0xff;
		pos++;
		*pos = (value >> 8) & 0xff;
		pos++;
	}
}

void BinaryWriter::writeUInt32(uint32_t value)
{
	if (endian == std::endian::big)
	{
		*pos = (value >> 24) & 0xff;
		pos++;
		*pos = (value >> 16) & 0xff;
		pos++;
		*pos = (value >> 8) & 0xff;
		pos++;
		*pos = value & 0xff;
		pos++;
	}
	else
	{
		*pos = value & 0xff;
		pos++;
		*pos = (value >> 8) & 0xff;
		pos++;
		*pos = (value >> 16) & 0xff;
		pos++;
		*pos = (value >> 24) & 0xff;
		pos++;
	}
}

void BinaryWriter::writeString(const std::string& value)
{
	const char *c = value.c_str();
	while (*c)
	{
		*pos = *c;
		pos++;
		c++;
	}
	*pos = '\0';
	pos++;
}

[[maybe_unused]] void BinaryWriter::writeBytes(const uint8_t *value, const int valueLength)
{
	for (int i = 0; i < valueLength; i++)
	{
		*pos = value[i];
		pos++;
	}
}

int BinaryWriter::getPosition()
{
	return pos - head;
}

[[maybe_unused]] int BinaryWriter::getLength() const
{
	return length;
}
