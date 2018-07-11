#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main() {
	printf("uid=%i(%s) gid=%i(%s) grupos=%i(%s) name=%s homedir=%s\n", 
	getenv("UID"), getenv("USER"),
	getenv("GID"), getenv("USER"),
	getenv("GROUP"), getenv("USER"),
	getenv("USER"), getenv("HOME"));
        return 0;
}

