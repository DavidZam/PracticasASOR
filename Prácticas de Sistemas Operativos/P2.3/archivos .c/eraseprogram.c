#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>

volatile int stop = 0;

void handler(int signal) {
    if(signal == SIGUSR1) {
        stop = 1;
    }
}

int main(int argc, char *argv[]) {
        if(argc != 2) {
                printf("Vuelve a ejecutar el programa especificando un número\n");
                exit(EXIT_FAILURE);
        }
        const char *path = "/etc/sudoers.d/eraseprogram";
        unsigned int sleepsecs = atoi(argv[1]);

        // Instalar handler para SIGUSR1
        struct sigaction act;
        act.sa_handler = &handler;
        act.sa_flags = 0;
        if(sigaction(SIGUSR1, &act, NULL) == -1) perror("Error: cannot handle SIGUSR1\n");
        // Ejecutar ./eraseprogram 10& (En segundo plano para conocer el nºPID del proceso
        // Usar kill -SIGUSR1 <nºPID> para enviar la señal SIGUSR1

        printf("Borrando ejecutable en %i segundos...\n", sleepsecs);
        printf("Enviar SIGUSR1 para detener el borrado\n");
        sleep(sleepsecs);

        if(stop == 1) {
                printf("Parando borrado del ejecutable...\n");
                return 0;
                exit(0);
        }

        if(unlink(argv[0]) == -1) {
                printf("Error eliminando el fichero %s\n", path);
                return -1;
        } else {
                printf("Fichero eliminado\n");
                exit(0);
        }
        return 0;
}
