#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>

/*void handler(int signal) {
    if(signal == SIGINT) {
        printf("Se recibió la llamada SIGINT, desbloqueando la llamada...\n");
        //signal(SIGINT, SIG_DFL); // Desbloqueamos la llamada SIGINT
        printf("Sigo vivo1\n");
    }
    if(signal == SIGSTOP) {
        printf("Se recibió la llamada SIGSTOP\n");
    }
}*/

int main(int argc, char *argv[]) {
        if(argc != 2) {
                printf("Vuelve a ejecutar el programa especificando un PID\n");
                exit(EXIT_FAILURE);
        }
        pid_t pid = atoi(argv[1]);

        // Bloqueo de las señales SIGINT y SIGSTP:
        sigset_t set, pending;
        sigemptyset(&set);
        sigaddset(&set, SIGINT);
        sigaddset(&set, SIGTSTP);
        sigprocmask(SIG_BLOCK, &set, NULL);

        printf("Señales SIGINT y SIGSTOP bloqueadas, a dormir...\n");
        sleep(10);
        // Usar Ctrl + C para enviar la señal SIGINT y comprobar el bloqueo...

        sigpending(&pending);
        if(sigismember(&pending, SIGINT)) {
                printf("Se recibió la llamada SIGINT\n");
        } else if(sigismember(&pending, SIGTSTP)) {
                printf("Se recibió la llamada SIGSTOP, desbloqueando la llamada...\n");
                sigdelset(&set, SIGINT);
                sigprocmask(SIG_UNBLOCK, &set, NULL);
                //signal(SIGSTOP, SIG_DFL); // Desbloqueamos la llamada SIGSTOP
                printf("Hola");
        }
        //printf("Sigo vivo\n");
        // Instalar handler para SIGINT y SIGSTP
        /*struct sigaction act;
        act.sa_handler = handler;
        act.sa_flags = 0;
        sigaction(SIGINT, &act, NULL);
        sigaction(SIGSTOP, &act, NULL);*/

        //signal(SIGINT, SIG_IGN); // Comprobar el bloqueo con Ctrl+C
        //signal(SIGSTOP, SIG_IGN);

        //sleepsecs = getenv("SLEEP_SECS");
        //printf("%s", sleepsecs);
        //int secs = (int)sleepsecs;
        //printf("%i", secs);
        return 0;
}

