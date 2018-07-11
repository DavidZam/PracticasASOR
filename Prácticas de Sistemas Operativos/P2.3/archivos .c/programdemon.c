#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
        if(argc < 2) {
                printf("Vuelva a ejecutar el programa especificando un comando a ejecutar\n");
                exit(EXIT_FAILURE);
        }
        char *cmd;
        int res;
        char *arguments[3];
        cmd = malloc(sizeof(char));
        strcpy(cmd, argv[1]);
        arguments[0] = argv[1];
        arguments[1] = argv[2];
        arguments[2] = NULL;

        int fd = open("/tmp/daemon.out", O_RDWR | O_CREAT | O_TRUNC, 0645);
        if(fd == -1) perror("Fallo en fd");
        int fd2 = open("/tmp/daemon.err", O_RDWR | O_CREAT | O_TRUNC, 0645);
        if(fd2 == -1) perror("Fallo en fd2");
        int fd3 = open("/dev/null", O_RDWR | O_CREAT | O_TRUNC, 0645);
        if(fd3 == -1) perror("Fallo en fd3");
        dup2(fd, 1); // Salida estandar (1)
        dup2(fd2, 2); // Salida de error (2)
        dup2(fd3, 0); // Entrada estandar (0)
        close(fd);
        close(fd2);
        close(fd3);

        // Si no ha habido errores (-1) fork() retorna dos veces:
        // una con un pid = 0 (ejecución proceso hijo)
        // otra con un pid > 0 (ejecución proceso padre)
        pid_t pid = fork();
        if(pid == -1) {
                perror("Error en el fork");
        } else if(pid == 0) { // Ejecucion del proceso hijo
                res = execvp(cmd, arguments);
                if(res == -1) {
                        perror("exec() falló");
                }
        } else if(pid > 0) { // Ejecución del proceso padre

        }
    return 0;
}
