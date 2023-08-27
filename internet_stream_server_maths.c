#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SIZE 1024


int main(int argc, char *argv [])
{
    int psock, sock,cli_addr_len;
    char msg[SIZE];
    struct sockaddr_in addr,cli_addr; // Internet socket
    char reply[SIZE];
    
    memset(&cli_addr, 0, sizeof(cli_addr));
    cli_addr_len = sizeof(cli_addr);

    addr.sin_family = AF_INET; // Internet socket
    addr.sin_addr.s_addr = htonl(INADDR_ANY); // All interfaces
    addr.sin_port = htons(atoi(argv [1]) ) ;
    psock = socket(AF_INET, SOCK_STREAM, 0); // Stream socket
    bind(psock, ( struct sockaddr *)&addr, sizeof(addr));
    listen (psock, 1) ;

    strcpy(msg,"") ;
    
    printf("\nwaiting for new connection (port : %s) ...\n", argv [1]) ;
    sock = accept(psock, (struct sockaddr *)&cli_addr, &cli_addr_len);
    printf("connection established...\n") ;
    recv(sock, msg, SIZE, 0) ;
    printf("Received : %s\n", msg);
    int res=0;
    char* token = strtok(msg,"+");
    while (token){
        res=res+atoi(token);
        token = strtok(NULL,"+");
    }
    sprintf(reply,"%d",res);
    send(sock, reply, strlen(reply) + 1, 0) ;
    close(psock);
    unlink(argv [1]) ;
    return 0;
}

