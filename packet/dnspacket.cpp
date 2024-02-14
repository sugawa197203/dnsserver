#include "dnspacket.hpp"
#include "records/header.hpp"
#include "records/question.hpp"
#include "records/answer.hpp"
#include "records/authority.hpp"
#include "records/additional.hpp"
#include "records/preamble.hpp"
#include <list>

class DNSPacket
{
public:
	Header header;
	std::list<Question> questions;
	std::list<Answer> answers;
	std::list<Authority> authorities;
	std::list<Additional> additionals;

	DNSPacket()
	{
	}

	~DNSPacket()
	{
	}

	void fromBinary(uint8_t *binary, int length)
	{
		BinaryReader reader(binary, length, std::endian::big);

		header.id = reader.readUInt16();
		header.flags = reader.readUInt16();
		header.qdcount = reader.readUInt16();
		header.ancount = reader.readUInt16();
		header.nscount = reader.readUInt16();
		header.arcount = reader.readUInt16();

		if (reader.isEOF())
			return;

		for (int i = 0; i < header.qdcount; i++)
		{
			questions.push_back(Question(
				reader.readString(),
				reader.readUInt16(),
				reader.readUInt16()));
		}

		if (reader.isEOF())
			return;

		if (reader.isEOF())
			return;
	}

	int toBinary(uint8_t *binary, int length)
	{
		BinaryWriter writer(binary, length, std::endian::big);

		writer.writeUInt16(header.id);
		writer.writeUInt16(header.flags);
		writer.writeUInt16(header.qdcount);
		writer.writeUInt16(header.ancount);
		writer.writeUInt16(header.nscount);
		writer.writeUInt16(header.arcount);

		for (Question &question : questions)
		{
			writer.writeString(question.qname);
			writer.writeUInt16(question.qtype);
			writer.writeUInt16(question.qclass);
		}

		for (Answer &answer : answers)
		{
			std::string name = "\x06" + std::string(answer.name);
			name.replace(name.find("."), 1, 1, '\x03');
			writer.writeString(name);
			writer.writeUInt16(answer.type);
			writer.writeUInt16(answer.class_);
			writer.writeUInt32(answer.ttl);
			writer.writeUInt16(answer.rdlength);
			writer.writeUInt32(answer.IP);
		}

		return writer.getPosition();
	}

	void print()
	{
		header.print();
		std::cout << "Questions: " << questions.size() << std::endl;
		for (auto &question : questions)
		{
			question.print();
		}

		std::cout << "Answers: " << answers.size() << std::endl;
		for (auto &answer : answers)
		{
			answer.print();
		}

		// std::cout << "Authorities: " << authorities.size() << std::endl;
		// for (auto &authority : authorities)
		// {
		// 	authority.print();
		// }

		// std::cout << "Additionals: " << additionals.size() << std::endl;
		// for (auto &additional : additionals)
		// {
		// 	additional.print();
		// }
	}
};