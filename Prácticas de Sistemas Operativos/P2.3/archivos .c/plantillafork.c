#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

		// Si no ha habido errores (-1) fork() retorna dos veces, una con un pid = 0 (ejecución proceso hijo) y otra con un pid > 0 (ejecución proceso padre)
        pid_t pid = fork();    
        if(pid == -1) {
                perror("Error en el fork");
        } else if(pid == 0) { // Ejecucion del proceso hijo

        } else if(pid > 0) { // Ejecución del proceso padre...

        }
        return 0;
}
