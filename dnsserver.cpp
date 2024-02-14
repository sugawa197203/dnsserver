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
#include "records/records.hpp"

#define BUFFER_SIZE 512

class DNSPacket
{
private:
	DNSHeader *header;
	Question *question;
	DNSAnswer *answer;
	Authority *authority;
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

		question = new Question(
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

	Question *getQuestion()
	{
		return question;
	}

	DNSAnswer *getAnswer()
	{
		return answer;
	}

	Authority *getAuthority()
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

	void setQuestion(Question *question)
	{
		this->question = question;
	}

	void setAnswer(DNSAnswer *answer)
	{
		this->answer = answer;
	}

	void setAuthority(Authority *authority)
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

		Question question = *packet->getQuestion();

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