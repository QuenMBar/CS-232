/*
 * callTimer.cpp is a C++ OS utility for creating and timing new threads and processes.  This main function handles the rest 
 * of the program and the other classes.
 *
 *  Created on: Feb 13, 2019
 *      Author: Quentin Barnes
 * 		CS Lab
 * 
 * Can be compiled uning the command g++ -pthread -o callTimer callTimer.cpp ThreadProcess.cpp
 * Can be run using the command ./callTimer 
 */

#include "ThreadProcess.h"

#include <string>
#include <vector>
using namespace std;


bool thread = false;  	// Flag for the thread command line switch
bool process = false;  	// Flag for the process command line switch
int runTime = 1;		// How many repitions the program is set to do

int main(int argc,char* argv[]) 
{   
	//Loops through all the command line args and tests to see which ones are present
	vector<string> args(argv, argv+argc);
	for (size_t i = 1; i < args.size(); ++i) {
		if (args[i] == "-p" || args[i] == "-process") {
			process = true;
		} else if (args[i] == "-t" || args[i] == "-thread") {
			thread = true;
		} else if (args[i] == "-r") {
			runTime = atoi(args[i+1].c_str());
		}
	}

	//If neither of the flags were triggered, then the program returns an error and kills itself
    if (!(process || thread)) {
        fprintf(stderr, "Parse failed!\n NEEDS TO INCLUDE -process, -p, -thread, OR -t\n");
        exit(1);
    }

    ThreadProcess tp;  // Creates the ThreadProcess class instance

	//Depending on whether process or thread were triped, it calls thier respective commands from the ThreadProcess class
    if (process) {
    	tp.createProcesses(runTime);
    }

    if (thread) {
    	tp.createThreads(runTime);
    }

    if (process) {
    	tp.printTimesP();
    }

    if (thread) {
    	tp.printTimesT();
    }
    
}
