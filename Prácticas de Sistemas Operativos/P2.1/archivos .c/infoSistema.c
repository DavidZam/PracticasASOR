#include <sys/types.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

int main() {
        struct utsname st;
	uname(&st);
	printf("Kernel name: %s\n", st.sysname);
	printf("Kernel network node hostname: %s\n", st.nodename);
	printf("Kernel release: %s\n", st.release);
	printf("Kernel version: %s\n", st.version);
	printf("Kernel machine: %s\n", st.machine);
	//printf("Kernel domain: %s\n", st.domainname);
        return 0;
}

