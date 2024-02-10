#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

int main()
{
	// UDP recive
	int sock;
	struct sockaddr_in addr;
	socklen_t addr_len = sizeof(struct sockaddr_in);
	char buf[1024];

	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("socket");
		return 1;
	}

	bzero((char *)&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(25565);
	addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("bind");
		return 1;
	}

	memset(buf, 0, sizeof(buf));

	if (recvfrom(sock, buf, sizeof(buf) - 1, 0, (struct sockaddr *)&addr, &addr_len) < 0)
	{
		perror("recvfrom");
		return 1;
	}

	// print hex

	for (int i = 0; i < 1024; i++)
	{
		printf("%02x ", buf[i]);
		if (i % 16 == 15)
		{
			printf("\n");
		}
	}

	return 0;
}
