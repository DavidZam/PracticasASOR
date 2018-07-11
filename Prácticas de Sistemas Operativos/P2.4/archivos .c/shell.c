#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <stdlib.h>

#define READ_END 0
#define WRITE_END 1

// Probar el programa con ./shell echo 12345 | wc -c
int main(int argc, char *argv[]) {
        if(argc < 6) {
                printf("Uso: comando1 argumento1 | comando2 argumento2\n");
                exit(EXIT_FAILURE);
        }
        int descf[2]; //descf[0] -> lectura, descf[1] -> escritura
        int res1, res2;
        char *cmd1[] = {argv[1], argv[2], NULL};
        char *cmd2[] = {argv[4], argv[5], NULL};

        // Creamos la tuberia sin nombre
        pipe(descf);
        // Abrimos el pipe
        //int fdread = open(descf[0], O_RDONLY, 0645);
        //int fdwrite = open(descf[1], O_WRONLY, 0645);
        // Si no ha habido errores (-1) fork() retorna dos veces, una con un pid = 0 (ejecución proceso hijo) y otra con un pid > 0 (ejecución proceso padre)
        pid_t pid = fork();
        if(pid == -1) {
                perror("Error en el fork()");
        } else if(pid > 0) { // Ejecución del padre:
                close(descf[WRITE_END]); // Cerramos el extremo de escritura del pipe
                dup2(descf[READ_END], STDOUT_FILENO); // Redirecciona salida estandar al extremo de escritura del pipe
                close(descf[READ_END]);
                res1 = execvp(cmd1[0], cmd1); //Ejecuta comando1 argumento 1
                if(res1 == -1) perror("Fallo en execvp1()");
        } else if(pid == 0) { // Ejecución del hijo
                close(descf[READ_END]); // Cerramos el extremo de lectura del pipe
                dup2(descf[WRITE_END], STDIN_FILENO); // Duplica la entrada estandar con el extremo de lectura del pipe
                close(descf[WRITE_END]);
                res2 = execv(cmd2[0], cmd2); // Ejecuta comando2 argumento 2
                if(res2 == -1) perror("Fallo en execvp2()");
        }
        close(descf[WRITE_END]);
        close(descf[READ_END]);
        return 0;
}
