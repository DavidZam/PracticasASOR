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

int main(int argc, char *argv[]) {
	if(argc != 2)
		exit(EXIT_FAILURE);

	const char* filename = argv[1];
	struct stat buf;
	int res;
	char buffer [80];
	struct tm* timeinfo;
	char string [24] = "Fichero";
	res = lstat(filename, &buf);

	if(res == -1) {
		printf("Error:", strerror(errno));
	}

        printf("Major number: %i Minor number: %i\n", major(buf.st_rdev), minor(buf.st_rdev));
        printf("Numero de i-nodo: %i\n", buf.st_ino);
	if(S_ISBLK(buf.st_mode) != 0) strcpy(string, "Fichero de bloques");
	if(S_ISCHR(buf.st_mode) != 0) strcpy(string, "Fichero de caracteres");
	if(S_ISDIR(buf.st_mode) != 0) strcpy(string, "Directorio");
	if(S_ISFIFO(buf.st_mode) != 0) strcpy(string, "Fichero FIFO");
	if(S_ISLNK(buf.st_mode) != 0) strcpy(string, "Enlace simbolico");
        if(S_ISREG(buf.st_mode) != 0) strcpy(string, "Fichero regular");
        printf("Tipo archivo: %s\n", string);

	timeinfo = localtime(&buf.st_atime);
	strftime(buffer, sizeof(buffer), "Ultima hora acceso: %T", timeinfo);
	puts(buffer);
        return 0;
}

