#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

void main(int argc, char *argv[]) {
    struct addrinfo hints;
    struct addrinfo *res;
    struct sockaddr_storage cli;
    char buf[81], host[NI_MAXHOST], serv[NI_MAXSERV];
    // Rellenar info hints struct
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    hints.ai_protocol = 0;          /* Any protocol */

    // Llamada a getaddrinfo para obtener la info en la la struct res
    getaddrinfo(argv[1], argv[2], &hints, &res);
    // Creación del socket con la información almacenada en la struct res
    int sd = socket(res->ai_family, res->ai_socktype, 0);
    // Llamada a bind para enlazar el socket con la dirección de la struct res
    bind(sd, (struct sockaddr *)res->ai_addr, res->ai_addrlen);
    // Llamada a freeaddrinfo para liberar la memoria asignada a la struct res
    freeaddrinfo(res);

    // Bucle de escucha del servidor:
    while(1) {
        // socklen_t clen almacena el tamaño de la dirección cliente, que será modificado cuando
        // la llamada a recvfrom() regrese para indicar el tamaño real de la direccion.
        socklen_t clen = sizeof(cli);
        // guardamos en c el número de bytes recibidos, devueltos por la llamada a recvfrom(), a la cual 
        // le pasamos el socket, un buffer y su tamaño, los flags y punteros a la dirección y a su tamaño.
        int c = recvfrom(sd, buf, 80, 0, (struct sockaddr*) &cli, &clen);
        buf[c] = '\0';
        // Tras llenarse la dirección cli y su tamaño traducimos la direccion al nombre con getnameinfo(), 
        // para ello le pasamos un puntero a la direccion, su tamaño, buffers y tamaños para el host y el
        // servidor, así como el flag NI_NUMERICHOST para que devuelva el host en forma numérica.
        getnameinfo((struct sockaddr*) &cli, clen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST);
        pid_t pid = getpid();
        // Imprimimos por pantalla la dirección, puerto y mensaje del cliente
        printf("%s %s %i %s\n", host, serv, pid, buf);
        // Transmitimos su mismo mensaje al cliente (echo), para ello se usa la llamada a sendto(), le pasamos
        // el socket, el buffer con el msg y tu tamaño, así como un puntero al destinatario y su tamaño.
        sendto(sd, buf, c, 0, (struct sockaddr *)&cli, clen);
    }
}
