#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
        char buf[256];
        int fd0, fd1;
        int rc;
        struct timeval timeout;
        timeout.tv_sec = 10;
        timeout.tv_usec = 0;
        fd_set fds;

        fd0 = open("tuberia", O_RDONLY | O_NONBLOCK);
        fd1 = open("tuberia2", O_RDONLY | O_NONBLOCK);
        if(fd0 == -1) perror("Error en el open fd0");
        if(fd1 == -1) perror("Error en el open fd1");

        while(1) {
                FD_ZERO(&fds);

                FD_SET(fd0, &fds);
                FD_SET(fd1, &fds);

                rc = select(fd1+1, &fds, NULL, NULL, &timeout);
                if(rc == 0) {
                        //printf("Han pasado 10 segundos sin recibir nada\n");
                        //return 0;
                } else if(rc == -1) {
                        perror("Fallo en el select()");
                } else {
                        if(FD_ISSET(fd0, &fds)) {
                                ssize_t size = read(fd0, buf, sizeof(buf));
                                if(size == -1) perror("Error en read()");
                                else if (size == 0) { // Cerramos y volvemos a abrir el descriptor
                                        close(fd0);
                                        fd0 = open("tuberia", O_RDONLY | O_NONBLOCK);
                                } else {
                                        buf[size] = '\0';
                                        printf("Se ha recibido algo por la tuberia 0: %s\n", buf);
                                }
                        }
                        if(FD_ISSET(fd1, &fds)) {
                                ssize_t size = read(fd1, buf, sizeof(buf));
                                if(size == -1) perror("Error en read()");
                                else if (size == 0) { // Cerramos y volvemos a abrir el descriptor
                                        close(fd1);
                                        fd1 = open("tuberia2", O_RDONLY | O_NONBLOCK);
                                } else {
                                        buf[size] = '\0';
                                        printf("Se ha recibido algo por la tuberia 1: %s\n", buf);
                                }
                        }
                }
        }
        close(fd0);
        close(fd1);
        return 0;
}
