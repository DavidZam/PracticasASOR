#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main (int argc, char* argv[]) {
 	char* file = argv[1];
 	int fd;
 	struct flock lock;

 	printf("Trying to open and lock %s...\n", file);
 	fd = open(file, O_WRONLY);
	memset(&lock, 0, sizeof(lock));
	lock.l_type = F_WRLCK; // Write lock type
	fcntl(fd, F_SETLKW, &lock); // Place the lock on the file

	printf("File opened and locked! hit enter to unlock... "); // Until enter is pressed the file is locked
 	getchar();

 	printf("Unlocking...\n");
 	lock.l_type = F_UNLCK; // Unlock type
 	fcntl(fd, F_SETLKW, &lock); // Unlock the file

 	close(fd);
 	return 0;
}
