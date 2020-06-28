#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc , char *argv[])
{
    int sockfd = 0, forClientSockfd = 0;
    struct sockaddr_in serverInfo;
    struct sockaddr_in clientInfo;
    socklen_t addrlen;

    char message[] = {"Hi,this is server.\n"};
    char inputBuffer[256] = {};

    // Create Socket
    sockfd = socket(AF_INET , SOCK_STREAM , 0);

    if (sockfd == -1){
        printf("Fail to create a socket.");
    }

    // Setup Socket
    bzero(&serverInfo, sizeof(serverInfo));

    serverInfo.sin_family   = AF_INET;
    serverInfo.sin_port     = htons(8700);
    serverInfo.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&serverInfo, sizeof(serverInfo));
    listen(sockfd, 5);

    addrlen = sizeof(clientInfo);

    while(1)
    {
        forClientSockfd = accept(sockfd,(struct sockaddr*) &clientInfo, &addrlen);

        send(forClientSockfd, message, sizeof(message), 0);
        recv(forClientSockfd, inputBuffer, sizeof(inputBuffer), 0);

        printf("Get:%s:%d\n", inputBuffer, forClientSockfd);
        close(forClientSockfd);
    }

    close(sockfd);
    return 0;
}
