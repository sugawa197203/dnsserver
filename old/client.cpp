#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main()
{
	// UDP 通信で送る

	int port = 53;
	int sock;
	struct sockaddr_in addr;

	sock = socket(AF_INET, SOCK_DGRAM, 0);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr("192.168.213.109");

	char buf[2048];

	memset(buf, 0, sizeof(buf));

	sprintf(buf, "Hello, world!");

	sendto(sock, buf, sizeof(buf), 0, (struct sockaddr *)&addr, sizeof(addr));

	close(sock);

	return 0;
}
