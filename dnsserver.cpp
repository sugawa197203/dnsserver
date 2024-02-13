#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <iostream>
#include <byteswap.h>
#include "utils/binaryreader.cpp"
#include "utils/binarywriter.cpp"
#include <bit>
#include <regex>
#include <iomanip>
#include <ios>
#include <netdb.h>
#include <byteswap.h>
#include <vector>
#include "dnspacket.h"

#define BUFFER_SIZE 512

class DNSHeader
{
private:
	uint16_t id;
	uint16_t flags;
	uint16_t qdcount;
	uint16_t ancount;
	uint16_t nscount;
	uint16_t arcount;

public:
	DNSHeader(uint16_t id, uint16_t flags, uint16_t qdcount, uint16_t ancount, uint16_t nscount, uint16_t arcount)
	{
		this->id = id;
		this->flags = flags;
		this->qdcount = qdcount;
		this->ancount = ancount;
		this->nscount = nscount;
		this->arcount = arcount;
	}

	DNSHeader()
	{
		id = 0;
		flags = 0;
		qdcount = 0;
		ancount = 0;
		nscount = 0;
		arcount = 0;
	}

	~DNSHeader() {}

	void setID(uint16_t id)
	{
		this->id = id;
	}

	void setFlags(uint16_t flags)
	{
		this->flags = flags;
	}

	void setQDCount(uint16_t qdcount)
	{
		this->qdcount = qdcount;
	}

	void setANCount(uint16_t ancount)
	{
		this->ancount = ancount;
	}

	void setNSCount(uint16_t nscount)
	{
		this->nscount = nscount;
	}

	void setARCount(uint16_t arcount)
	{
		this->arcount = arcount;
	}

	uint16_t getID()
	{
		return id;
	}

	uint16_t getFlags()
	{
		return flags;
	}

	uint16_t getQDCount()
	{
		return qdcount;
	}

	uint16_t getANCount()
	{
		return ancount;
	}

	uint16_t getNSCount()
	{
		return nscount;
	}

	uint16_t getARCount()
	{
		return arcount;
	}

	bool getQR()
	{
		return (flags & 0x8000) >> 15;
	}

	uint8_t getOpcode()
	{
		return (flags & 0x7800) >> 11;
	}

	bool getAA()
	{
		return (flags & 0x0400) >> 10;
	}

	bool getTC()
	{
		return (flags & 0x0200) >> 9;
	}

	bool getRD()
	{
		return (flags & 0x0100) >> 8;
	}

	bool getRA()
	{
		return (flags & 0x0080) >> 7;
	}

	bool getZ()
	{
		return (flags & 0x0070) >> 4;
	}

	bool getAD()
	{
		return (flags & 0x0020) >> 5;
	}

	bool getCD()
	{
		return (flags & 0x0010) >> 4;
	}

	uint8_t getRCODE()
	{
		return flags & 0x000F;
	}

	void setQR(bool qr)
	{
		flags = (flags & 0x7FFF) | (qr << 15);
	}

	void setOpcode(uint8_t opcode)
	{
		flags = (flags & 0x87FF) | (opcode << 11);
	}

	void setAA(bool aa)
	{
		flags = (flags & 0xFBFF) | (aa << 10);
	}

	void setTC(bool tc)
	{
		flags = (flags & 0xFDFF) | (tc << 9);
	}

	void setRD(bool rd)
	{
		flags = (flags & 0xFEFF) | (rd << 8);
	}

	void setRA(bool ra)
	{
		flags = (flags & 0xFF7F) | (ra << 7);
	}

	void setZ(bool z)
	{
		flags = (flags & 0xFFF0) | (z << 4);
	}

	void setAD(bool ad)
	{
		flags = (flags & 0xFFDF) | (ad << 5);
	}

	void setCD(bool cd)
	{
		flags = (flags & 0xFFEF) | (cd << 4);
	}

	void setRCODE(uint8_t rcode)
	{
		flags = (flags & 0xFFF0) | rcode;
	}

	void print()
	{
		std::cout << "---------- DNS Header ----------" << std::endl;
		std::cout << "ID: " << id << std::endl;
		std::cout << "Flags: " << std::setfill('0') << std::setw(4) << std::right << std::hex << flags << std::endl;
		std::cout << "\tQR: " << ((flags & 0x8000) >> 15) << std::endl;
		std::cout << "\tOpcode: " << std::setfill('0') << std::setw(4) << std::right << ((flags & 0x7800) >> 11) << std::endl;
		std::cout << "\tAA: " << ((flags & 0x0400) >> 10) << std::endl;
		std::cout << "\tTC: " << ((flags & 0x0200) >> 9) << std::endl;
		std::cout << "\tRD: " << ((flags & 0x0100) >> 8) << std::endl;
		std::cout << "\tRA: " << ((flags & 0x0080) >> 7) << std::endl;
		std::cout << "\tZ: " << ((flags & 0x0070) >> 4) << std::endl;
		std::cout << "\tRCODE: " << std::setfill('0') << std::setw(4) << std::right << (flags & 0x000F) << std::endl;
		std::cout << "QDCount: " << qdcount << std::endl;
		std::cout << "ANCount: " << ancount << std::endl;
		std::cout << "NSCount: " << nscount << std::endl;
		std::cout << "ARCount: " << arcount << std::endl;
		std::cout << "--------------------------------" << std::endl;
	}
};

class DNSQuestion
{
private:
	std::string qname;
	uint16_t qtype;
	uint16_t qclass;

public:
	DNSQuestion(std::string qname, uint16_t qtype, uint16_t qclass)
	{
		this->qname = qname;
		this->qtype = qtype;
		this->qclass = qclass;
	}

	~DNSQuestion()
	{
	}

	void setQName(char *qname)
	{
		this->qname = qname;
	}

	void setQType(uint16_t qtype)
	{
		this->qtype = qtype;
	}

	void setQClass(uint16_t qclass)
	{
		this->qclass = qclass;
	}

	std::string getQName()
	{
		return qname;
	}

	uint16_t getQType()
	{
		return qtype;
	}

	uint16_t getQClass()
	{
		return qclass;
	}

	std::string qNameFormat()
	{
		std::string result = qname;
		// to lower case
		std::transform(result.begin(), result.end(), result.begin(), ::tolower);
		// replace 0x03 with '.'
		std::regex re("\\x03");
		result = std::regex_replace(result, re, ".");
		// remove control characters
		re = std::regex("[\\x00-\\x1F]");
		result = std::regex_replace(result, re, "");
		return result;
	}

	void
	print()
	{
		std::cout << "---------- DNS Question ----------" << std::endl;
		std::cout << "QName: " << qNameFormat() << std::endl;
		std::cout << "QType: " << qtype << std::endl;
		std::cout << "QClass: " << qclass << std::endl;
		std::cout << "----------------------------------" << std::endl;
	}
};

class DNSAnswer : Preamble
{
private:
	uint32_t IP;

public:
	DNSAnswer()
	{
		name = nullptr;
		type = 0;
		class_ = 0;
		ttl = 0;
		rdlength = 0;
		IP = 0;
	}

	DNSAnswer(std::string name, uint16_t type, uint16_t class_, uint32_t ttl, uint16_t rdlength, uint32_t IP)
	{
		this->name = name;
		this->type = type;
		this->class_ = class_;
		this->ttl = ttl;
		this->rdlength = rdlength;
		this->IP = IP;
	}

	~DNSAnswer()
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

	void setIP(uint32_t IP)
	{
		this->IP = IP;
	}

	uint32_t getIP()
	{
		return IP;
	}

	void print()
	{
		struct in_addr IP;
		IP.s_addr = this->IP;
		std::cout << "---------- DNS Answer ----------" << std::endl;
		Preamble::print();
		std::cout << "IP: " << inet_ntoa(IP) << std::endl;
		std::cout << "--------------------------------" << std::endl;
	}
};

class DNSAuthority
{
private:
	char *name;
	uint16_t type;
	uint16_t class_;
	uint32_t ttl;
	uint16_t rdlength;
	char *rdata;
};

class DNSAdditional
{
private:
	char *name;
	uint16_t type;
	uint16_t class_;
	uint32_t ttl;
	uint16_t rdlength;
	char *rdata;
};

class DNSPacket
{
private:
	DNSHeader *header;
	DNSQuestion *question;
	DNSAnswer *answer;
	DNSAuthority *authority;
	DNSAdditional *additional;

public:
	DNSPacket(uint8_t *binary, int length)
	{
		question = nullptr;
		answer = nullptr;
		authority = nullptr;

		BinaryReader reader(binary, length, std::endian::big);
		header = new DNSHeader(
			reader.readUInt16(),
			reader.readUInt16(),
			reader.readUInt16(),
			reader.readUInt16(),
			reader.readUInt16(),
			reader.readUInt16());

		if (reader.isEOF())
			return;

		question = new DNSQuestion(
			reader.readString(),
			reader.readUInt16(),
			reader.readUInt16());

		if (reader.isEOF())
			return;

		if (reader.isEOF())
			return;
	}

	DNSPacket()
	{
		header = nullptr;
		question = nullptr;
		answer = nullptr;
		authority = nullptr;
		additional = nullptr;
	}
	~DNSPacket() {}

	DNSHeader *getHeader()
	{
		return header;
	}

	DNSQuestion *getQuestion()
	{
		return question;
	}

	DNSAnswer *getAnswer()
	{
		return answer;
	}

	DNSAuthority *getAuthority()
	{
		return authority;
	}

	DNSAdditional *getAdditional()
	{
		return additional;
	}

	void setHeader(DNSHeader *header)
	{
		this->header = header;
	}

	void setQuestion(DNSQuestion *question)
	{
		this->question = question;
	}

	void setAnswer(DNSAnswer *answer)
	{
		this->answer = answer;
	}

	void setAuthority(DNSAuthority *authority)
	{
		this->authority = authority;
	}

	void setAdditional(DNSAdditional *additional)
	{
		this->additional = additional;
	}

	void print()
	{
		if (header != nullptr)
			header->print();
		else
			std::cout << "Header is null" << std::endl;
		if (question != nullptr)
			question->print();
		else
			std::cout << "Question is null" << std::endl;
		if (answer != nullptr)
			answer->print();
		else
			std::cout << "Answer is null" << std::endl;
	}

	// std::vector<DNSAnswer> CreateDNSAnswers()
	// {
	// 	std::vector<DNSAnswer> answers;
	//	}
};

class DNSServer
{
private:
	int sock;
	struct sockaddr_in addr;
	socklen_t addr_len = sizeof(struct sockaddr_in);
	uint8_t buf[BUFFER_SIZE];
	DNSPacket *packet;

public:
	DNSServer()
	{
		if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		{
			perror("socket");
			return;
		}

		bzero((char *)&addr, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_port = htons(25565);
		addr.sin_addr.s_addr = INADDR_ANY;

		if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		{
			perror("bind");
			return;
		}
	}

	~DNSServer()
	{
		close(sock);
	}

	void receive()
	{
		ssize_t len;
		memset(buf, 0, sizeof(buf));

		if ((len = recvfrom(sock, buf, sizeof(buf) - 1, 0, (struct sockaddr *)&addr, &addr_len)) < 0)
		{
			perror("recvfrom");
			return;
		}

		packet = new DNSPacket(buf, len);
		packet->print();
	}

	void res()
	{
		struct hostent *host;

		if ((host = gethostbyname(packet->getQuestion()->qNameFormat().c_str())) == NULL)
		{
			std::cout << "gethostbyname failed" << std::endl;
			return;
		}

		DNSPacket *res = new DNSPacket();

		DNSHeader *header = new DNSHeader();
		header->setID(packet->getHeader()->getID());
		header->setQR(1);
		header->setRD(packet->getHeader()->getRD());

		header->setQDCount(1);
		header->setANCount(1);

		DNSQuestion question = *packet->getQuestion();

		DNSAnswer *answer = new DNSAnswer();
		answer->setPreamble(
			host->h_name,
			DNSRecordType::A,
			1,
			0,
			4);
		answer->setIP(*((uint32_t *)host->h_addr_list[0]));

		res->setHeader(header);
		res->setQuestion(&question);
		res->setAnswer(answer);

		std::cout << "\n----- Response -----" << std::endl;
		res->print();

		uint8_t *binary = new uint8_t[BUFFER_SIZE];
		BinaryWriter writer(binary, BUFFER_SIZE, endian::big);
		std::cout << bswap_16(res->getHeader()->getID()) << std::endl;
		writer.writeUInt16(res->getHeader()->getID());
		writer.writeUInt16(res->getHeader()->getFlags());
		writer.writeUInt16(res->getHeader()->getQDCount());
		writer.writeUInt16(res->getHeader()->getANCount());
		writer.writeUInt16(res->getHeader()->getNSCount());
		writer.writeUInt16(res->getHeader()->getARCount());
		writer.writeString(res->getQuestion()->getQName());
		writer.writeUInt16(res->getQuestion()->getQType());
		writer.writeUInt16(res->getQuestion()->getQClass());
		std::string name = "\x06" + std::string(res->getAnswer()->getPreamble().name);
		name.replace(name.find("."), 1, 1, '\x03');
		writer.writeString(name);
		writer.writeUInt16(res->getAnswer()->getPreamble().type);
		writer.writeUInt16(res->getAnswer()->getPreamble().class_);
		writer.writeUInt32(res->getAnswer()->getPreamble().ttl);
		writer.writeUInt16(res->getAnswer()->getPreamble().rdlength);
		writer.writeUInt32(bswap_32(res->getAnswer()->getIP()));

		if (sendto(sock, binary, writer.getPosition(), 0, (struct sockaddr *)&addr, addr_len) < 0)
		{
			perror("sendto");
			return;
		}

		for (int i = 0; i < writer.getPosition(); i++)
		{
			printf("%02x ", binary[i]);
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

		delete[] binary;
		delete res;

		std::cout << "\n\nResponse sent" << std::endl;
	}
};

int main()
{
	DNSServer server;
	server.receive();
	server.res();

	return 0;
}