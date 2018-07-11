#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <time.h>

int main(int argc, char *argv[]) {
    struct addrinfo hints;
    struct addrinfo *res, *resp;
    int sd, j, s;
    size_t len;
    ssize_t nread, nwrite;
    char buf[500];

    if (argc < 3) {
        fprintf(stderr, "Usage: %s host port command...\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
    hints.ai_flags = 0;
    hints.ai_protocol = 0;          /* Any protocol */

    getaddrinfo(argv[1], argv[2], &hints, &res);

    for(resp = res; resp != NULL; resp = resp->ai_next) {
        sd = socket(resp->ai_family, resp->ai_socktype, resp->ai_protocol);
        if(sd == -1) {
            perror("socket()");
            continue;
        }

        if(connect(sd, resp->ai_addr, resp->ai_addrlen) == -1) {
            perror("socket()");
        } else {
            break;
        }

        close(sd);
    }
    
    freeaddrinfo(res);

    for(j = 3; j < argc; j++) {
        len = strlen(argv[j]) + 1;
        nwrite = write(sd, argv[j], len);
        if(nwrite == -1) perror("write()");
        nread = read(sd, buf, 500);
        buf[nread] = 0;
        if(nread == -1) perror("read()");
        printf("Recibidos %ld bytes: %s\n", (long) nread, buf);
    }

    exit(EXIT_SUCCESS);
}
