#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

int main() {
	int res;
	res = setuid(0);
	if(res == -1) {
		printf("Error: %s\n", strerror(errno));
		perror("Explicacion: ");
	} else {
		printf("Ejecutado con exito \n");
		perror("Explicacion");
	}
	return 0;
}
