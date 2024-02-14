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
#include "packet/dnspacket.cpp"
#include "packet/dnspacketutil.hpp"
#include <bit>
#include <regex>
#include <iomanip>
#include <ios>
#include <netdb.h>
#include <byteswap.h>
#include <vector>
#include <memory>

void printBinary(uint8_t *binary, int length)
{
	for (int i = 0; i < length; i++)
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
}

class DNSServer
{
private:
	const int BUFFER_SIZE = 1024;
	int sock;
	struct sockaddr_in addr;
	socklen_t addr_len = sizeof(struct sockaddr_in);

	std::list<std::unique_ptr<hostent>> getHost(std::shared_ptr<DNSPacket> packet)
	{
		std::list<std::unique_ptr<hostent>> hosts;
		struct hostent *host;

		for (Question &question : packet->questions)
		{
			if ((host = gethostbyname(question.qNameFormat().c_str())) == NULL)
			{
				std::cout << "gethostbyname failed" << std::endl;
				return;
			}

			hosts.push_back(std::make_unique<hostent>(*host));
		}

		return hosts;
	}

public:
	uint16_t port;

	DNSServer(uint16_t port = 53)
	{
		this->port = port;

		if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		{
			perror("socket");
			return;
		}

		bzero((char *)&addr, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
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

	std::shared_ptr<DNSPacket> receivePacket()
	{
		ssize_t len;
		uint8_t buf[BUFFER_SIZE];
		memset(buf, 0, sizeof(buf));
		std::shared_ptr<DNSPacket> packet = std::make_shared<DNSPacket>();

		if ((len = recvfrom(sock, buf, sizeof(buf) - 1, 0, (struct sockaddr *)&addr, &addr_len)) < 0)
		{
			perror("recvfrom");
			return;
		}

		packet->fromBinary(buf, len);
		packet->print();

		return packet;
	}

	void res(std::shared_ptr<DNSPacket> packet)
	{
		std::list<std::unique_ptr<hostent>> hosts = getHost(packet);

		DNSPacket res;
		res.header = packet->header;
		res.header.setQR(true);
		res.header.setRD(packet->header.getRD());

		res.header.qdcount = packet->header.qdcount;
		res.header.ancount = hosts.size();

		res.questions = packet->questions;

		for (std::unique_ptr<hostent> &host : hosts)
		{
			res.answers.push_back(Answer(
				host->h_name,
				DNSRecordType::A,
				1,
				0,
				4,
				*((uint32_t *)host->h_addr_list[0])));
		}

		res.print();

		std::array<uint8_t, 1024> binary;
		int length = res.toBinary(binary.data(), binary.size());

		if (sendto(sock, binary.data(), length, 0, (struct sockaddr *)&addr, addr_len) < 0)
		{
			perror("sendto");
			return;
		}

		printBinary(binary.data(), length);
	}
};

int main()
{
	DNSServer server;
	std::cout << "---------- Server started ----------" << std::endl;
	std::shared_ptr<DNSPacket> packet = server.receivePacket();

	std::cout << "---------- Received packet ----------" << std::endl;
	server.res(packet);

	return 0;
}