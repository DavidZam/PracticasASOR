#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
        if(argc != 2) {
                printf("Vuelve a ejecutar el programa especificando algo para escribir\n");
                exit(EXIT_FAILURE);
        }
        char *home = getenv("HOME");
        char *path = "/tuberia";
        char *buf = malloc(sizeof(argv[1]));
        strcat(home, path); // home: root/tuberia
        buf = strcat(argv[1], "\n");

        // Creamos la tuberia con mkfifo(<nombre>, <modo>)
        // Modo solo escritura (permisos): 0222 p-w--w--w-
        if(mkfifo(home, 0222) == -1) perror("Error al crear la tuberia");
        int fd = open(home, O_WRONLY);
        if(fd == -1) perror("Error al abrir la tuberia");

        // Tener en cuenta los caracteres '\0' y "\n" en la escritura, NO USAR sizeo$
        ssize_t escrito = write(fd, argv[1], strlen(buf));
        if(escrito == 0) printf("No se ha escrito nada\n");
        else if (escrito == -1) perror("Error al escribir en la tuberia");
        close(fd);
        return 0;
}
