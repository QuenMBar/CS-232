/*
 * ThreadProcess.cpp is a class that can create and time processes and threads and print the average times that they took to create.
 *
 *  Created on: Feb 13, 2019
 *      Author: Quentin Barnes
 * 		CS LAB
 */

#include "ThreadProcess.h"

/**
 * Create Processes and Time Them
 * recives: times, amount of processes to be creates
 */
void ThreadProcess::createProcesses(int times){
	runTimes = times;
	int i;//#include <iostream>
	for (i = 0; i < times; i++) {
		ntp.reset();  //resets the timer for the new run
		ntp.start();
		int pid = fork();  //creates a new fork
		ntp.stop();
		totalTimeProcess += ntp.getTotalTime();
		if (pid < 0) { fprintf(stderr, "Fork failed!\n"); exit(1);}
		else if (pid > 0) {
			//Does nothing because the parent process doesnt print anything out.
		}
		else{
			printf("Hello from the child process (PID = %d)\n", getpid());
			kill(getpid(), SIGKILL); //kills the process so it doesnt run everything twice
			}
	}
}

/**
 * Function for the child thread to call
 * Used so that the child function can call it and write out its ID number
 * recives: input, NULL
 * 
 */
void* threadFun(void* input) {
	pthread_t thId = pthread_self();
	printf("Hello from the child thread (TID = %lu) \n", thId);
	pthread_exit(NULL);
}

/**
 * Function that creates the thread processes and times them
 * recives: times, amount of threads to be creates
 */
void ThreadProcess::createThreads(int times){
	runTimes = times;
	int j;
	for (j = 0; j < times; j++) {
		ntt.reset();  //resets the timer for the new run
		pthread_t newThread;
		ntt.start();
		pthread_create(&newThread, NULL, threadFun, NULL);  //Creates a new thread
		ntt.stop();
		totalTimeThread += ntt.getTotalTime();
		pthread_join(newThread, NULL); //Joins the new thread with the main thread, essentially killing it
	}
}

/**
 * Prints the average for how long the threads took to create
 */
void ThreadProcess::printTimesT(){
	double averageTimeThread = totalTimeThread / runTimes;
	printf("The average time for creating a thread is: %f\n", averageTimeThread);
}

/**
 * Prints the average for how long the processes took to create
 */
void ThreadProcess::printTimesP(){
	double averageTimeProcess = totalTimeProcess / runTimes;
	printf("The average time for creating a process is: %f\n", averageTimeProcess);
}
