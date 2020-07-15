#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc , char *argv[])
{
    struct sockaddr_in info;
    int sockfd = 0, err;

    char message[] = {"Hi there"};
    char receiveMessage[100] = {};

    // Create socket
    sockfd = socket(AF_INET , SOCK_STREAM , 0);
    if (sockfd == -1){
        printf("Fail to create a socket.");
    }

    // Setup Socket
    bzero(&info,sizeof(info));
    info.sin_family = AF_INET;
    info.sin_port   = htons(8700);
    info.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to socket
    err = connect(sockfd, (struct sockaddr *)&info, sizeof(info));
    if(err == -1){
        printf("Connection error");
    }

    // Send a message to server
    send(sockfd, message, sizeof(message),0);
    recv(sockfd, receiveMessage, sizeof(receiveMessage),0);

    printf("%s", receiveMessage);
    printf("close Socket\n");

    close(sockfd);

    return 0;
}
