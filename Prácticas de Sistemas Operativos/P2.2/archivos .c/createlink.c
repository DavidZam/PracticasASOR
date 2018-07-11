#include <sys/types.h>
#include <sys/utsname.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>

#define MAX_SIZE 100

int main(int argc, char *argv[]) {
        if(argc != 2) {
		printf("Vuelve a ejecutar el programa especificando una ruta\n");
                exit(EXIT_FAILURE);
	}

        char *path = argv[1];
	char *tmppath = strdup(path);
	char *tmppath2 = strdup(path);

	const char *newpath = strcat(tmppath, ".hard");
	const char *newpath2 = strcat(tmppath2, ".sym");

        struct stat buf;
        int res;
        res = lstat(path, &buf);

        if(res == -1) {
                printf("Error:\n", strerror(errno));
        } else {
	   if(S_ISREG(buf.st_mode) != 0) { // Si es un fichero regular
	      int res2 = link(path, newpath);
		if(res2 == -1)	{
			printf("error:%s\n", strerror(errno));
		} else {
			printf("Enlace rígido creado\n");
		}

	      int res3 = symlink(path, newpath2);
		if(res3 == -1) {
			 printf("error:%s\n", strerror(errno));
		} else {
			printf("Enlace simbólico creado\n");
		}
	   }
    	}
    return 0;
}

