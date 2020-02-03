#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h> 
#include <sched.h>
#include <unistd.h>
#include <sys/time.h>


void readPipe(int file);
void writePipe(int file);

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
	
	int pipe1[2];
	pid_t returnPid;
	long int numberIterations = 1000000;
	struct timeval start, end;
	double avgTime;
	float t1Nanosec, t2Nanosec;
	pipe(pipe1); 
	//pipe(pipe2);	

	returnPid = fork(); 
	gettimeofday(&start, 0); 
for (int j = 0; j < numberIterations; j++) {
	if (returnPid < 0) {
		//fork failed; exit
		fprintf(stderr, "Forking failed\n");
		exit(1); 		
	} else if (returnPid == 0) {
		//the child goes down this path
		wait(NULL);
		close(pipe1[1]); 
		readPipe(pipe1[0]);

	} else {
//		//the parent goes down this path 
		close(pipe1[0]);
		writePipe(pipe1[1]);
	//	return EXIT_SUCCESS;
/*		double avgTime; 
		gettimeofday(&start, 0); 	
		//wait(NULL); 	
		for (int j = 0; j < numberIterations; j++) { 
		dup2(pipe2[1], STDOUT_FILENO); 
		close(pipe2[1]);
		close(pipe2[0]); 
		dup2(pipe1[0], STDIN_FILENO); 
		close(pipe1[1]);
		close(pipe1[0]);
		}
		
		wait(NULL);
		long t1Nanosec, t2Nanosec; 
		t1Nanosec = (start.tv_sec * 1000000 + start.tv_usec)*1000;
		t2Nanosec = (end.tv_sec * 1000000 + end.tv_usec)*1000;

		avgTime = (t2Nanosec - t1Nanosec) / (numberIterations * 1.0 * 2); 
		printf("Averagetime spent in context switch in nanoseconds: %0.9f\n", avgTime);
*/
	}
}
	gettimeofday(&end, 0);

	t1Nanosec = (start.tv_sec * 1000000 + start.tv_usec)*1000;
	t2Nanosec = (end.tv_sec * 1000000 + start.tv_usec)*1000;

	avgTime = (t2Nanosec - t1Nanosec)/(numberIterations * 1.0);
	
	printf("Average time for the context switch %0.9f\n", avgTime); 
	
return 0;
}

/*
void readPipe(int file) {
	FILE* stream;
	int ch;
	stream = fdopen(file, "r");
	while ((ch = fgetc(stream)) != EOF)
		putchar(ch);
	fclose(stream); 
}



void writePipe(int file) {
	FILE* stream; 
	stream = fdopen(file, "w"); 
	fprintf(stream, "hello\n");
	fprintf(stream, "goodbye\n");
	fclose(stream);
}
*/
//		gettimeofday(&end, 0); 

		
	//	return EXIT_SUCCESS;
/*		
//		for (int i = 0; i < numberIterations; i++) {	
		dup2(pipe1[1], STDOUT_FILENO);
		close(pipe1[1]);
		close(pipe1[0]);
		dup2(pipe2[0], STDIN_FILENO); 
		close(pipe2[1]); 
		close(pipe2[0]);
*/
//		}
//		gettimeofday(&end, 0); 
