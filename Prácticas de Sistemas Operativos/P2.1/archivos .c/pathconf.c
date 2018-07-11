#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main() {
        printf("Num. Max. Enlaces: %i\n", pathconf("/", _PC_LINK_MAX));
        printf("Tam. Max. Ruta: %i\n", pathconf("/", _PC_PATH_MAX));
        printf("Tam. Max. Nombre Fichero: %i\n", pathconf("/", _PC_NAME_MAX));
        return 0;
}

