#include <sys/types.h>
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

        int res;
        char *arguments[3];

        arguments[0] = argv[1];
        arguments[1] = argv[2];
        arguments[2] = NULL;

        res = execvp(cmd, arguments);
        if(res == -1) perror("exec() falló");
        printf("El comando terminó de ejecutarse\n");
        return 0;
}
