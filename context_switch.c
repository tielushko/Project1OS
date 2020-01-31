#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>

int main (int argc, char *argv[]) {

        //creating the core id and getting the pid
        const int core = 0;
        const pid_t pid = getpid();

        //bitset representing a CPU
        cpu_set_t cpuSet;

        //initialize CPU to the empty set and add the CPU core to the SET
        CPU_ZERO(&cpuSet);
        CPU_SET(core, &cpuSet);

        //set the CPU to work on one core
        const int setAffinity = sched_setaffinity(pid, sizeof(cpu_set_t), &cpuSet);

        if (CPU_ISSET(core, &cpuSet)) {
                printf("Successfully set the process %d to CPU core %d\n", pid, core);
                exit(0);
        } else {
                printf("Unsuccessfully set the process %d to CPU core %d\n", pid, core);
        }

        int pipe1[2];
        int pipe2[2];

return 0;
}
