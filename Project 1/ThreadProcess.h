/*
 * ThreadProcess.h is the header class for ThreadProcess.cpp.  It defines all the needed includes, functions, and variables for the class.
 *
 *  Created on: Feb 13, 2019
 *      Author: Quentin Barnes
 * 		CS LAB
 */

#ifndef THREADPROCESS_H_
#define THREADPROCESS_H_

#include "NanoTimer.h"

#include <stdio.h>
#include <unistd.h>
#include <cstdlib>
#include <csignal>
#include <stdlib.h>
#include <pthread.h>
using namespace std;

class ThreadProcess {
public:
	void createThreads(int times);
	void createProcesses(int times);
	void printTimesT();
	void printTimesP();
private:
	NanoTimer ntp; //Timer for processes
	NanoTimer ntt; //Timer for threads
	double totalTimeThread = 0;
	double totalTimeProcess = 0;
	double runTimes = 1;
};

#endif /* THREADPROCESS_H_ */
