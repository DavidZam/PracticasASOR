#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sched.h>

int main(int argc, char *argv[]) {

        pid_t pid = atoi(argv[1]);
        struct sched_param ms;
        sched_getparam(pid, &ms);
        int polplanification = sched_getscheduler(pid);
        if(polplanification == 1) {
                printf("Política de planificación: %s\n", "SCHED_FIFO");
        } else if(polplanification == 3) {
                printf("Política de planificación: %s\n", "SCHED_BATCH");
        } else if(polplanification == 5) {
                printf("Política de planificación: %s\n", "SCHED_IDLE");
        } else if(polplanification == 0) {
                printf("Política de planificación: %s\n", "SCHED_OTHER");
        } else if(polplanification == 2) {
                printf("Política de planificación: %s\n", "SCHED_RR");
        }
        printf("Prioridad: %i\n", ms.sched_priority);
        int maxprio = sched_get_priority_max(polplanification);
        int minprio = sched_get_priority_min(polplanification);
        printf("Valores mínimo y máximo de politica de prioridad: %i-%i\n", minprio,$
        return 0;
}
