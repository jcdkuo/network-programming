#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc , char *argv[])
{
    int     sock0, sock;
    struct  sockaddr_in client;
    socklen_t len;
    struct  addrinfo    hints, *res;
    int     err;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_flags  = AI_PASSIVE;
    hints.ai_socktype = SOCK_STREAM;
    err = getaddrinfo(NULL, "12345", &hints, &res);
    if (err != 0) {
        printf("getaddrinfo : %s\n", gai_strerror(err));
        return 1;
    }
    
    // Create Socket
    sock0 = socket(res->ai_family, res->ai_socktype, 0);
    if (sock0 < 0) {
        perror("socket");
        return 1;
    }

    // Setup Socket
    if (bind(sock0, res->ai_addr, res->ai_addrlen) != 0) {
        perror("socket");
        return 1;
    }

    freeaddrinfo(res);

    listen(sock0, 5);

    len = sizeof(client);
    sock = accept(sock0, (struct sockaddr *)&client, &len);

    // Send 5 characters
    write(sock, "HELLO", 5);

    // Close TCP connection
    close(sock);

    // Close listened socket
    close(sock0);

    return 0;
}

