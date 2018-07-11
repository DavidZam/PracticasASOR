#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
        if(argc < 2) {
                printf("Vuelva a ejecutar el programa especificando un comando a ejecutar\n");
                exit(EXIT_FAILURE);
        }

        char *cmd;
        cmd = malloc(sizeof(char));
        strcpy(cmd, argv[1]);
        strcat(cmd, " ");
        strcat(cmd, argv[2]);
        int res = system(cmd);
        if(res == -1) perror("system() falló");
        printf("El comando terminó de ejecutarse\n");
        return 0;
}

