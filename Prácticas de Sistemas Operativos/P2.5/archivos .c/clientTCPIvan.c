#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]){
    char buffer[81];
    char enviar[256];

    struct addrinfo hints, cliente;
    struct addrinfo *res;

    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = PF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo(argv[1], argv[2], &hints, &res);

    int miSocket = socket(res->ai_family,res->ai_socktype,0);
    
    connect(miSocket, (struct sockaddr*) res->ai_addr, res->ai_addrlen);
    
    while(1) {

       scanf("%s",enviar);

       if(strlen(enviar)==1 && enviar[0] == 'q') {
          close(miSocket);
          break;
       }

       send(miSocket,enviar,strlen(enviar), 0);
       recv(miSocket,buffer,80,0);
       printf("%s\n", buffer);
    }
    
    return 0;
}
