#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char **args) {

    char hostname[64];
    struct addrinfo hints, *res;
    struct in_addr addr;
    int err;

    if (argc == 1) {
        if (gethostname(hostname, 64) != 0) {
            printf("gethostname error %d %s\n", err, strerror(err));
            return 1;
        }
    } else {
        strcpy(hostname, args[1]);
    }
    printf("hostname: %s\n", hostname);

    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_INET;

    if ((err = getaddrinfo(hostname, NULL, &hints, &res)) != 0) {
        printf("getaddrinfo error %d %s\n", err, strerror(err));
        return 1;
    }

    struct addrinfo *ai = res;
    while (ai) {
        addr.s_addr= ((struct sockaddr_in *)(ai->ai_addr))->sin_addr.s_addr;
        printf("ip addres: %s\n", inet_ntoa(addr));
        ai = ai->ai_next;
    }

    freeaddrinfo(res);

    return 0;
}