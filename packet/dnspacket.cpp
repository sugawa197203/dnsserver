#include "dnspacket.hpp"
#include "records/question.hpp"
#include "records/answer.hpp"
#include "records/authority.hpp"
#include "records/additional.hpp"
#include "dnspacketutil.hpp"

DNSPacket::DNSPacket()
= default;

DNSPacket::~DNSPacket()
= default;

void DNSPacket::fromBinary(uint8_t *binary, ssize_t length)
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
		std::string qname = reader.readString();
		auto qtype = (DNSRecordType)reader.readUInt16();
		uint16_t qclass = reader.readUInt16();
		questions.emplace_back(
			qname,
			qtype,
			qclass);
	}

	if (reader.isEOF())
		return;

	if (reader.isEOF())
		return;
}

ssize_t DNSPacket::toBinary(uint8_t *binary, ssize_t length)
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
		writer.writeString(questions.front().qname);
		writer.writeUInt16(answer.type);
		writer.writeUInt16(answer.class_);
		writer.writeUInt32(answer.ttl);
		writer.writeUInt16(answer.rdlength);
        writer.writeUInt32(bswap_32(answer.IP));
	}

    for (Authority &authority : authorities)
    {
        writer.writeString(authority.name);
        writer.writeUInt16(authority.type);
        writer.writeUInt16(authority.class_);
        writer.writeUInt32(authority.ttl);
        writer.writeUInt16(authority.rdlength);
        for (auto byte : *authority.RDATA)
        {
            writer.writeUInt8(byte);
        }
    }

    for (Additional &additional : additionals)
    {
        writer.writeString(questions.front().qname);
        writer.writeUInt16(additional.type);
        writer.writeUInt16(additional.class_);
        writer.writeUInt32(additional.ttl);

        if (additional.type == DNSRecordType::TXT)
        {
            writer.writeUInt16(additional.rdlength + 1);
            writer.writeUInt8(additional.RDATA->size());
        }
        else
        {
            writer.writeUInt16(additional.rdlength);
        }

        for (auto byte : *additional.RDATA)
        {
            writer.writeUInt8(byte);
        }
    }

	return writer.getPosition();
}

void DNSPacket::print()
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

	 std::cout << "Authorities: " << authorities.size() << std::endl;
	 for (auto &authority : authorities)
	 {
	 	authority.print();
	 }

	 std::cout << "Additionals: " << additionals.size() << std::endl;
	 for (auto &additional : additionals)
	 {
	 	additional.print();
	 }
}
