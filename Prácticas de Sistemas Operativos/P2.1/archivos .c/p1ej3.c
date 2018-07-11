#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

int main() {
        int i;
	for(i = 0; i < 132; i++) {
		printf("Error: %s\nCode: %d\n", strerror(i), i);
	}
        return -1;
}

