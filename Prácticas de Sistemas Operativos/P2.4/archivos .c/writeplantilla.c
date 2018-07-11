#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
        char buf[256];
        ssize_t size = write(fd1, buf, sizeof(buf));
        buf[size] = '\0';
        printf("Se ha escrito %s\n", buf);

    return 0;
}