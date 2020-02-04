#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h> 
#include <sched.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

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
	
  //the number of iterations used in the code
	long int numberIterations = 1000000;
	
  //timeval structure to record time
  struct timeval start, end;
  
  //communication byte between 
  int byte = 1;
  
  //three pipes. 1 & 2 for communicating byte between processes, 3 for keeping track of the end timeval between processes
  int pipe1[2];
  int pipe2[2];
  int timePipe[2];
  
  //pid integer for forking
	pid_t returnPid;
 
  //checks to make sure the pipes are open
  if(pipe(pipe1) == -1) {
    printf("Pipe1 failed");
    exit(1);  
  }
	if(pipe(pipe2) == -1) {
    printf("Pipe2 failed");
    exit(1);  
  }	
  if(pipe(timePipe) == -1) {
    printf("timePipe failed");
    exit(1);  
  }	  

  //forking
	returnPid = fork(); 
 
	if (returnPid < 0) {
		//fork failed; exit
		fprintf(stderr, "Forking failed\n");
		exit(1); 		
	} else if (returnPid == 0) {
		//the child goes down this path
    
    //closing the not used ends of the pipes prematurely
    close(pipe2[0]);
    close(pipe1[1]);
    
    //communication between the processes
    for (int i = 0; i < numberIterations; i++) {
      read(pipe1[0], &byte, sizeof(int));
      write(pipe2[1], &byte, sizeof(int));
    }
    
    //get time at the end of execution
    gettimeofday(&end, 0);
     
    //pass the end in to parent process for time calculation
    write(timePipe[1], &end, sizeof(struct timeval));
     
	} else {
		  //the parent goes down this path 
      double avgTime, t1Nanosec, t2Nanosec;
     
      //get the time in the beginning of the execution
      gettimeofday(&start, NULL);
      
      //closing the not used ends of the pipes prematurely
      close(pipe1[0]);
      close(pipe2[1]);
      
     //we are using pipe1 to pass the int to the child, initiating context switch, and child execution and read, then upon child writing, we then read the int from pipe2.
      for (int j = 0; j < numberIterations; j++) {
        write(pipe1[1], &byte, sizeof(int));
        read(pipe2[0], &byte, sizeof(int));
     }
     
    //closing the process switch pipes
    close(pipe1[0]);
    close(pipe1[1]);
    close(pipe2[0]);
    close(pipe2[1]);
    
    //getting the end of time from the child process
    read(timePipe[0],&end,sizeof(struct timeval));
    
    //closing down the timepipe
    close(timePipe[0]);
    close(timePipe[1]);
    
    //calculating average time for the the context switch and output 
    avgTime = ((((end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec))/1000.0)/(numberIterations * 2.0));
    printf("Average time for context switch in milliseconds over million iterations: %0.6lf ms\n",avgTime);
    
	}

return 0;
}


