#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

int main(int argc, char** argv) {

  //initiate processID, timeval structure, number of iterations and average time 	
	int pid;
	struct timeval start, end;
	long numberIterations = 1000000000;
	float avgTime;

  //get the time before the system call execution
	gettimeofday(&start, NULL);

  //system call for the number of iteration. in this case, we use getpid();
	for (int i = 0; i < numberIterations; i++) {
		pid = getpid();	
	}

  //end the timer
	gettimeofday(&end, NULL); 
	
 
  //perform the calculation to get the result in nanoseconds.
	long t1Nanosec, t2Nanosec;

	t1Nanosec = (start.tv_sec * 1000000 + start.tv_usec)*1000; 
	t2Nanosec = (end.tv_sec * 1000000 + end.tv_usec)*1000;
	
	avgTime = (t2Nanosec-t1Nanosec) / (numberIterations * 1.0);

	printf("Average time for system call in nanoseconds over million iterations: %0.9f\n", avgTime);

	return 0;
}

