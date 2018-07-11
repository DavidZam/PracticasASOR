#include <sys/types.h>
#include <sys/utsname.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
        if(argc != 2) {
                printf("Vuelve a ejecutar el programa especificando la salida estandar\n");
                exit(EXIT_FAILURE);
        }

	int filed = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0645);

	dup2(filed, 1); // Salida estandar (1)
	dup2(filed, 2); // Salida de error (2)

	printf("Mensajes salida estandar: prueba1 prueba2\n");
	printf("otralinea\n");

	perror("Mensajes salida error: perror");

	close(filed);

    return 0;
}

