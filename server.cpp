#include <iostream>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 512
#define PORT 53

class DNSHeader
{
private:
	unsigned short id;
	unsigned short flags;
	unsigned short qdcount;
	unsigned short ancount;
	unsigned short nscount;
	unsigned short arcount;

public:
	DNSHeader(unsigned short id, unsigned short flags, unsigned short qdcount = 0, unsigned short ancount = 0, unsigned short nscount = 0, unsigned short arcount = 0)
		: id(id), flags(flags), qdcount(qdcount), ancount(ancount), nscount(nscount), arcount(arcount)
	{
	}

	unsigned short getID() const
	{
		return id;
	}

	unsigned short getFlags() const
	{
		return flags;
	}

	unsigned short getQDCount() const
	{
		return qdcount;
	}

	unsigned short getANCount() const
	{
		return ancount;
	}

	unsigned short getNSCount() const
	{
		return nscount;
	}

	unsigned short getARCount() const
	{
		return arcount;
	}

	void setID(unsigned short id)
	{
		this->id = id;
	}

	void setFlags(unsigned short flags)
	{
		this->flags = flags;
	}

	void setQDCount(unsigned short qdcount)
	{
		this->qdcount = qdcount;
	}

	void setANCount(unsigned short ancount)
	{
		this->ancount = ancount;
	}

	void setNSCount(unsigned short nscount)
	{
		this->nscount = nscount;
	}

	void setARCount(unsigned short arcount)
	{
		this->arcount = arcount;
	}

	void print() const
	{
		std::cout << "ID: " << id << std::endl;
		std::cout << "Flags: " << flags << std::endl;
		std::cout << "QDCount: " << qdcount << std::endl;
		std::cout << "ANCount: " << ancount << std::endl;
		std::cout << "NSCount: " << nscount << std::endl;
		std::cout << "ARCount: " << arcount << std::endl;
	}
}

class DNSServer
{
private:
	int sock;
	struct sockaddr_in addr;
	char buf[BUFFER_SIZE];
	ushort port;

public:
	DNSServer(int port = PORT)
		: port(port)
	{
		init();
		bind();
	}

	~DNSServer()
	{
		stop();
	}

	void start()
	{
		std::cout << "Waiting for a client..." << std::endl;
		receive();
		for (int i = 0; i < 512; i++)
		{
			printf("%02x ", (unsigned char)buf[i]);
		}
		std::cout << std::endl;
	}

	void stop()
	{
		std::cout << "Server stopped." << std::endl;
		close();
	}

private:
	void init()
	{
		sock = socket(AF_INET, SOCK_DGRAM, 0);
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		addr.sin_addr.s_addr = INADDR_ANY;
	}

	void bind()
	{
		if (::bind(sock, (struct sockaddr *)&addr, sizeof(addr)))
		{
			perror("bind");
			exit(1);
		}
	}

	void receive()
	{
		memset(buf, 0, sizeof(buf));
		recv(sock, buf, sizeof(buf), 0);
	}

	void close()
	{
		::close(sock);
	}
};

int main()
{
	DNSServer server(2000);
	server.start();
	return 0;
}