#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
	int sock;
	struct sockaddr_in addr;

	char buf[2048];
	int packet_size;
	int port = 53;

	sock = socket(AF_INET, SOCK_DGRAM, 0);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)))
	{
		perror("bind");
		return 1;
	}

	// Is ok soket?
	if (sock < 0)
	{
		perror("socket");
		return 1;
	}

	memset(buf, 0, sizeof(buf));
	recv(sock, buf, sizeof(buf), 0);

	packet_size = strlen(buf);

	printf("packet_size: %d\n", packet_size);
	for (int i = 0; i < packet_size; i++)
	{
		printf("%02x ", (unsigned char)buf[i]);
	}

	printf("\n");

	close(sock);

	return 0;
}