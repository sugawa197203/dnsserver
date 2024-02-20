#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include "packet/dnspacket.hpp"
#include "packet/dnspacketutil.hpp"
#include "sitesnippet/sitesnippet.hpp"
#include <iomanip>
#include <netdb.h>
#include <vector>
#include <memory>

void printBinary(uint8_t *binary, ssize_t length)
{
    std::cout << "---------- binary ----------" << std::endl;
	for (ssize_t i = 0; i < length; i++)
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
	std::cout << std::endl;
    std::cout << "---------- end binary ----------" << std::endl;
}

class DNSServer
{
private:
	const int BUFFER_SIZE = 1024;
	int sock;
	struct sockaddr_in addr{};
	socklen_t addr_len = sizeof(struct sockaddr_in);

	static std::list<std::shared_ptr<hostent>> getHost(const std::shared_ptr<DNSPacket>& packet)
	{
		std::list<std::shared_ptr<hostent>> hosts;
		struct hostent *host;

		for (Question &question : packet->questions)
		{
            if (question.qtype == DNSRecordType::AAAA)
            {
                std::cerr << "Not supported qtype : " << question.qtype << std::endl;
                continue;
            }

			if ((host = gethostbyname(question.qNameFormat().c_str())) == nullptr)
			{
				perror("gethostbyname");
				fprintf(stderr, "\tqName : %s\n", question.qNameFormat().c_str());
				abort();
			}

			hosts.push_back(std::make_unique<hostent>(*host));
		}

		return hosts;
	}

public:
	uint16_t port;

	explicit DNSServer(uint16_t port = 53)
	{
		this->port = port;

		if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		{
			perror("socket");
            throw std::runtime_error("socket");
		}

		bzero((char *)&addr, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_port = htons(this->port);
		addr.sin_addr.s_addr = INADDR_ANY;

		if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		{
			perror("bind");
            throw std::runtime_error("bind");
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
            return nullptr;
		}

		packet->fromBinary(buf, len);
		std::cout << "---------- received ----------" << std::endl;
		printBinary(buf, len);
		packet->print();
		std::cout << "---------- end received ----------" << std::endl;

		return packet;
	}

	void res(const std::shared_ptr<DNSPacket>& packet)
	{
		std::list<std::shared_ptr<hostent>> hosts = getHost(packet);

		DNSPacket res;
		res.header = packet->header;
		res.header.setQR(true);
		res.header.setRD(false);

		res.header.qdcount = packet->header.qdcount;

		res.questions = packet->questions;

		for (std::shared_ptr<hostent> &host : hosts)
		{
            for (int i = 0; host->h_addr_list[i] != nullptr; i++)
            {
                std::string name = host->h_name;
                uint32_t IP = *(uint32_t *)host->h_addr_list[i];
                res.answers.emplace_back(name, DNSRecordType::A, 1, 0, 4, IP);
            }
		}

        res.header.ancount = res.answers.size();

        std::cout << "#################### SNIPPET ####################" << std::endl;
        std::string snippet = SiteSnippet::getSnippetText(res.answers.front().name);
        std::cout << "-------------------- SNIPPET --------------------" << std::endl;
        std::cout << snippet << std::endl;
        std::cout << "#################### END SNIPPET ####################" << std::endl;

        snippet = '\x03' + snippet;
        std::shared_ptr<std::vector<uint8_t>> RDATA = std::make_shared<std::vector<uint8_t>>(snippet.begin(), snippet.end());
        Additional additional(res.questions.front().qname, DNSRecordType::TXT, 1, 0, snippet.size(), RDATA);
        res.additionals.push_back(additional);
        res.header.arcount = res.additionals.size();

		res.print();

		std::array<uint8_t, 1024> binary{};
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
	DNSServer server(25565);
	std::cout << "---------- Server started ----------" << std::endl;

    while (true) {
        std::cout << "#################### Listening packet ####################" << std::endl;
        std::shared_ptr<DNSPacket> packet = server.receivePacket();
        std::cout << "#################### Response packet ####################" << std::endl;

        if (packet == nullptr)
        {
            continue;
        }

        server.res(packet);
    }
}