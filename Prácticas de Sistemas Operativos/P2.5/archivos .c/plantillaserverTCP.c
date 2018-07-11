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
    char buf[81];
    // Rellenar info hints struct
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM;
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
    // Llamada a listen para esperar conexiones en el socket sd, 5 conexiones máximas pendientes
    listen(sd, 5);

    // Bucle de escucha del servidor:
    while(1) {
        // socklen_t clen almacena el tamaño de la dirección cliente, que será modificado cuando
        // la llamada a recvfrom() regrese para indicar el tamaño real de la direccion.
        socklen_t clen = sizeof(cli);
        // Guardamos el desciptor del socket conectado en cli_sd devuelto por la llamada a accept(),
        // que extrae la 1a peticion de conexión y la asocia un nuevo socket.
        int cli_sd = accept(sd, (struct sockaddr*) &cli, &clen);
        // guardamos en c el número de bytes recibidos, devueltos por la llamada a recv(), a la cual 
        // le pasamos el descriptor del socket, un buffer y su tamaño y los flags.
        int c = recv(cli_sd, buf, 80, 0);
        // Transmitimos su mismo mensaje al cliente (echo), para ello se usa la llamada a send() le pasamos
        // el descriptor dek socket, el buffer con el msg y tu tamaño, así como los flags.
        send(cli_sd, buf, c, 0);
        // Por ultimo cerramos el descriptor del socket
        close(cli_sd);
    }
}
