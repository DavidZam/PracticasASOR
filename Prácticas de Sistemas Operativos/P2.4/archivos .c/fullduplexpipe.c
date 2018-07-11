#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <stdlib.h>

// Probar el programa con ./shell echo holaa | wc -c
int main(int argc, char *argv[]) {
        int p_h[2]; //p_h[0] -> lectura, p_h[1] -> escritura
        int h_p[2];

        // Creamos las tuberias sin nombre
        if(pipe(p_h) == -1) perror("Fallo en pipe()");
        if(pipe(h_p) == -1) perror("Fallo en pipe()");

        // Si no ha habido errores (-1) fork() retorna dos veces, una con un pid = 0 (ejecución proceso hijo) y otra con un pid > 0 (ejecución proceso padre)
        pid_t pid = fork();
        if(pid == -1) {
                perror("Error en el fork()");
       } else if(pid > 0) { // Ejecución del padre:
                // Cerramos los extremos opuestos a los que vamos a utilizar
                close(p_h[0]);
                close(h_p[1]);
                char parentbuf[256];
                char childmsg[1] = {'l'};
                while(childmsg[0] != 'q') {
                        printf("Padre, Mensaje a enviar:\n");
                        // Lee de la entrada estandar
                        // Al ser la primera vez que leemos el size es 256 y hay que poner el '\0'
                        ssize_t size = read(0, parentbuf, 256);
                        if(size == -1) perror("Padre, error leyendo");
                        parentbuf[size] = '\0';
                        // Envía el mensaje al hijo escribiendo en p_h
                        size = write(p_h[1], parentbuf, size+1);
                        if(size == -1) perror("Padre, error escribiendo");
                        // Permanece bloqueado esperando la confirmación por parte del hijo en la tuberia h_p
                        while(childmsg[0] != 'l' && childmsg[0] != 'q') {
                                ssize_t size = read(h_p[0], childmsg, 1);
                                if(size == -1) perror("Padre, error leyendo");
                        }
                }
                // Cerramos los otros extremos de los pipes
                close(p_h[1]);
                close(h_p[0]);
        } else if(pid == 0) { // Ejecución del hijo
                // Cerramos los extremos opuestos a los que vamos a utilizar
                close(p_h[1]);
                close(h_p[0]);

                char bufmsgs[257];
                char parentmsg[1] = {'l'};
                int i;

                for(i = 0; i < 10; i++) {
                        ssize_t size = read(p_h[0], bufmsgs, 256); // Lee de la tuberia p_h
                        if(size == -1) perror("Hijo: error leyendo");
                        bufmsgs[size] = '\0';
                        // Escribe por la salida estandar y espera un segundo
                        printf("Hijo, Mensaje recibido: %s:", bufmsgs);
                        sleep(1);

                        // Tras 10 mensajes envía 'q' para indicar que el padre finalice
                        if(i == 9) parentmsg[0] = 'q';
                        // Si i < 9 escribimos 'l' en la tuberia para notificar que el hijo esta listo
                        size = write(h_p[1], parentmsg, 1);
                        if(size == -1) perror("Hijo: error escribiendo");
                }
                // Cerramos los otros extremos de los pipes
                close(p_h[0]);
                close(h_p[1]);
        }
        return 0;
}
