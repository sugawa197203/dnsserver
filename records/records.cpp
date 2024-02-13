#include <string>
#include <iostream>

class Preamble
{
protected:
	std::string name;
	uint16_t type;
	uint16_t class_;
	uint32_t ttl;
	uint16_t rdlength;

public:
	Preamble()
	{
		name = nullptr;
		type = 0;
		class_ = 0;
		ttl = 0;
		rdlength = 0;
	}

	Preamble(std::string name, uint16_t type, uint16_t class_, uint32_t ttl, uint16_t rdlength)
	{
		this->name = name;
		this->type = type;
		this->class_ = class_;
		this->ttl = ttl;
		this->rdlength = rdlength;
	}

	~Preamble()
	{
	}

	void setName(std::string name)
	{
		this->name = name;
	}

	std::string getName()
	{
		return name;
	}

	void setType(uint16_t type)
	{
		this->type = type;
	}

	uint16_t getType()
	{
		return type;
	}

	void setClass(uint16_t class_)
	{
		this->class_ = class_;
	}

	uint16_t getClass()
	{
		return class_;
	}

	void setTTL(uint32_t ttl)
	{
		this->ttl = ttl;
	}

	uint32_t getTTL()
	{
		return ttl;
	}

	void setRDLength(uint16_t rdlength)
	{
		this->rdlength = rdlength;
	}

	uint16_t getRDLength()
	{
		return rdlength;
	}

	void print()
	{
		std::cout << "Name: " << name << std::endl;
		std::cout << "Type: " << type << std::endl;
		std::cout << "Class: " << class_ << std::endl;
		std::cout << "TTL: " << ttl << std::endl;
		std::cout << "RDLength: " << rdlength << std::endl;
	}
};
