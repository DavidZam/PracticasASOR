#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char *argv[]) {
        if(argc != 2) {
                printf("Vuelve a ejecutar el programa especificando un PID\n");
                exit(EXIT_FAILURE);
        }
        pid_t pid = atoi(argv[1]);

        // Bloqueo de las señales SIGINT y SIGTSTP:
        sigset_t set, pending;
        sigemptyset(&set);
        sigaddset(&set, SIGINT);
        sigaddset(&set, SIGTSTP);
        sigprocmask(SIG_BLOCK, &set, NULL);

        printf("Señales SIGINT y SIGTSTOP bloqueadas, a dormir...\n");
        //char *str = malloc(sizeof(char));
        //strcpy(str, getenv("SLEEP_SECS"));
        //sleep(getenv("SLEEP_SECS"));

        sleep(10);
        // Usar Ctrl + C para enviar la señal SIGINT y comprobar el bloqueo...
        // Usar Ctrl + Z para enviar la señal SIGTSTP y comprobar el bloqueo...

        sigpending(&pending);
        if(sigismember(&pending, SIGINT)) {
                printf("Se recibió la llamada SIGINT\n");
        }
        if(sigismember(&pending, SIGTSTP)) {
                printf("Se recibió la llamada SIGTSTOP, desbloqueando la llamada...\n");
                sigdelset(&pending, SIGINT);
                sigprocmask(SIG_UNBLOCK, &pending, NULL); // Desbloqueamos la señal SIGTSTP
                printf("Proceso reanudado correctamente");
        }
        return 0;
}
