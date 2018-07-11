#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>

// CUIDADO con las variables globales
int sigintcount = 0;
int sigtstopcount = 0;

void handler(int signal) {
    if(signal == SIGINT) {
        sigintcount++;
    }
    if(signal == SIGTSTP) {
        sigtstopcount++;
    }
}

int main(int argc, char *argv[]) {
        if(argc != 2) {
                printf("Vuelve a ejecutar el programa especificando un PID\n");
                exit(EXIT_FAILURE);
        }
        pid_t pid = atoi(argv[1]);

        // Instalar handler para SIGINT y SIGSTP
        struct sigaction act;
        act.sa_handler = &handler;
        act.sa_flags = 0;
        if(sigaction(SIGINT, &act, NULL) == -1) perror("Error: cannot handle SIGINT\n");
        if(sigaction(SIGTSTP, &act, NULL) == -1) perror("Error: cannot handle SIGTSTP\n");;

        while(sigintcount < 10 && sigtstopcount < 10) ;

        printf("Se ha recibido la señal SIGINT %i veces\n", sigintcount);
        printf("Se ha recibido la señal SIGTSTP %i veces\n", sigtstopcount);
        return 0;
}
