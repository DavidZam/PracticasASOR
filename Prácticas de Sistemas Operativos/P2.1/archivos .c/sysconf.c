#include <sys/types.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

int main() {
	printf("Long. Max. Argumentos: %i\n", sysconf(_SC_ARG_MAX));
        //perror("Error:");
 	printf("Num. Max. Hijos: %i\n", sysconf(_SC_CHILD_MAX));
	printf("Num. Max. Ficheros: %i\n", sysconf(_SC_OPEN_MAX));
  	return 0;
}

