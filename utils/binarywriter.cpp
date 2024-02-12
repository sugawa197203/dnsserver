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
	BinaryWriter(uint8_t *head, int length, std::endian endian = std::endian::big)
	{
		this->head = head;
		this->pos = head;
		this->length = length;
		this->endian = endian;
	}

	~BinaryWriter() {}

	void writeUInt8(uint8_t value)
	{
		*pos = value;
		pos++;
	}

	void writeUInt16(uint16_t value)
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

	void writeUInt32(uint32_t value)
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

	void writeString(std::string value)
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

	void writeBytes(uint8_t *value, int length)
	{
		for (int i = 0; i < length; i++)
		{
			*pos = value[i];
			pos++;
		}
	}

	int getPosition()
	{
		return pos - head;
	}

	int getLength()
	{
		return length;
	}
};
