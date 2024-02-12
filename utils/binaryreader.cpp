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
	bool isEOF()
	{
		return pos == head + length;
	}

	BinaryReader(uint8_t *head, int length, std::endian endian = std::endian::big)
	{
		this->head = head;
		this->pos = head;
		this->length = length;
		this->endian = endian;

		std::cout << "--------------------------------" << std::endl;
		for (int i = 0; i < length; i++)
		{
			printf("%02x ", head[i]);
			if (i % 8 == 7)
			{
				if (i % 16 == 15)
				{
					std::cout << std::endl;
				}
				else
				{
					std::cout << "  ";
				}
			}
		}
		std::cout << "\n--------------------------------" << std::endl;
	}

	~BinaryReader() {}

	int getLength()
	{
		return length;
	}

	int getPosition()
	{
		return pos - head;
	}

	template <typename T>
	T read()
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

	uint8_t readUInt8()
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

	uint16_t readUInt16()
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

	uint32_t readUInt32()
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

	uint64_t readUInt64()
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

	std::string readString()
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
};