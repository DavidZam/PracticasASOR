#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
        pid_t pid = atoi(argv[1]);
        char *cmd = "cat";
        char *arguments[3];
        arguments[0] = "cat";
        arguments[1] = "/proc/sys/fs/file-max";
        arguments[2] = NULL;

        printf("Id. de proceso: %i\n", pid);
        printf("Id. de proceso padre: %i\n", getppid());
        printf("Id. de grupo de procesos: %i\n", getpgrp());
        printf("Id. de sesión: %i\n", getsid(pid));
        printf("Directorio de trabajo: %s\n", getenv("HOME"));
        printf("Nº de archivos que puede abrir el proceso: %i\n", execvp(cmd, arguments);
        return 0;
}