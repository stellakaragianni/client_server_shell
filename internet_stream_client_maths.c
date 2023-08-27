#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SIZE 1024

int main(int argc, char *argv [])
{
    int sock, i ;
    char msg[SIZE],reply[SIZE];
    struct sockaddr_in addr; // Internet socket

    addr.sin_family = AF_INET; // Internet socket
    inet_aton(argv [1], &addr.sin_addr);
    addr.sin_port = htons(atoi(argv[2]) ) ;
    sock = socket(AF_INET, SOCK_STREAM, 0); // Stream socket
    connect(sock, ( struct sockaddr *)&addr, sizeof(addr));
    
    strcpy(msg,"") ;
    strcpy(reply,"") ;
    
    fgets(msg,sizeof(msg),stdin);
    send(sock, msg, strlen(msg) + 1, 0) ;
    strcpy(reply,"") ;
    recv(sock, reply, SIZE, 0) ;
    printf("Received : %s\n",reply);
    
    close(sock);
    return 0;
}