#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>

int main(int argc, char *argv[]) {
        if(argc != 2) {
                printf("Vuelve a ejecutar el programa especificando un fichero\n");
                exit(EXIT_FAILURE);
        }
        struct flock lock;
        time_t rawtime;
        struct tm* timeinfo;
        char buffer [9];
        int fd;

        printf("Comprobando el estado del cerrojo...\n");
        fd = open(argv[1], O_WRONLY);
        memset(&lock, 0, sizeof(lock));
        fcntl(fd, F_GETLK, &lock); // Trying to get the lock on the file

        if(lock.l_type != F_UNLCK) {
                printf("Cerrojo bloqueado\n");
                exit(EXIT_SUCCESS);
        } else {
                printf("Cerrojo desbloqueado, tratando adquirir el cerrojo...\n");
                lock.l_type = F_WRLCK; // Write lock type
                memset(&lock, 0, sizeof(lock));
                fcntl(fd, F_SETLKW, &lock); // Locked
                // Writing the actual hour
                time(&rawtime);
                timeinfo = localtime(&rawtime);
                strftime(buffer, sizeof(buffer), "%T", timeinfo);
                write(fd, buffer, 8);

                printf("Cerrojo adquirido, escribiendo la hora actual en el fichero...\n");
                //getchar();
                sleep(5);

                printf("Liberando cerrojo...\n");
                lock.l_type = F_UNLCK;
                fcntl(fd, F_SETLKW, &lock);
        }
        close(fd);
        return 0;
}