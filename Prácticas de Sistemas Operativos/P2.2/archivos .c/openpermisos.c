#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	int filedesc = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0645);
	if(filedesc == -1) {
		printf("Error:%s\n", strerror(errno));
		return EXIT_FAILURE;
	} else {
		return EXIT_SUCCESS;
	}
}
