#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc , char *argv[])
{
    struct  sockaddr_in server;
    int     sock, n;
    char    buf[32];

    // Create Scoket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // Setup Socket
    server.sin_family   = AF_INET;
    server.sin_port     = htons(12345);

    // localhost
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr.s_addr);

    // Connect to server
    connect(sock, (struct sockaddr *)&server, sizeof(server));

    // Receive data from server
    memset(buf, 0, sizeof(buf));
    n = read(sock, buf, sizeof(buf));

    printf("%d, %s\n", n, buf);

    // Close Scoket
    close(sock);

    return 0;
}

