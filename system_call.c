#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char** argv) {

    int pid; 
    struct timeval start, end; 
    long numberIterations = 1000000;
    float avgTime;

    gettimeofday(&start, NULL); 

    for (int i = 0; i < numberIterations; i++) {
        pid = getpid(); 
    }

    gettimeofday(&end, NULL); 

    long t1Nanosec, t2Nanosec;

    t1Nanosec = (start.tv_sec * 1000000 + start.tv_usec)*1000;
    t2Nanosec = (end.tv_sec * 1000000 + end.tv_usec)*1000;

    avgTime = (t2Nanosec-t1Nanosec) / (numberIterations * 1.0); 

    printf("Average time for system call in nanoseconds: %0.9f\n", avgTime);

    return 0;
}