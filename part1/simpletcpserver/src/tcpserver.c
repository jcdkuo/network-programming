#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc , char *argv[])
{
    int     sock0, sock;
    struct  sockaddr_in addr;
    struct  sockaddr_in client;
    socklen_t len;
    
    // Create Socket
    sock0 = socket(AF_INET, SOCK_STREAM, 0);

    // Setup Socket
    addr.sin_family = AF_INET;
    addr.sin_port   = htons(12345);
    addr.sin_addr.s_addr = INADDR_ANY;
    bind(sock0, (struct sockaddr *)&addr, sizeof(addr));

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

