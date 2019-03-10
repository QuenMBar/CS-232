/*
 * CommandLineController.h is a class that will parse command line switches if present and use 
 * the Model ThreadProcess.h effectively.  
 * 
 *  Created on: Feb 26, 2019
 *      Author: Quentin Barnes
 * 		CS LAB
 */

#ifndef COMMAND_LINE_CONTROLLER_H_
#define COMMAND_LINE_CONTROLLER_H_

#include "ThreadProcess.h"

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class CommandLineController {
public:
	void run(int argc,char* argv[]);
private:
    bool thread = false;  	// Flag for the thread command line switch
    bool process = false;  	// Flag for the process command line switch
    int timesToRun = 1;		// How many repitions the program is set to do
    ThreadProcess tp;       // Makes an instance of the Model Class
};


void CommandLineController::run(int argc,char* argv[]){

    //Loops through all the command line args and tests to see which ones are present
    vector<string> args(argv, argv+argc);
    for (size_t i = 1; i < args.size(); ++i) {
		if (args[i] == "-p" || args[i] == "-process") {
			process = true;
		} else if (args[i] == "-t" || args[i] == "-thread") {
			thread = true;
		} else if (args[i] == "-r") {
			timesToRun = atoi(args[i+1].c_str());
		}
	}

    //If neither of the flags were triggered, then the program returns an error and kills itself
    if (!(process || thread)) {
        fprintf(stderr, "Parse failed!\n NEEDS TO INCLUDE -process, -p, -thread, OR -t\n");
        exit(1);
    }

    //Creates processes or threads depending on the switches
    if (process) {
    	tp.createProcesses(timesToRun);
    }

    if (thread) {
    	tp.createThreads(timesToRun);
    }

    //Sleeps so that processes and threads can finish creating
    sleep(.2);

    //Prints the times to create processes or threads depending on the switches
    if (process) {
    	try {
            tp.printTimesP();
        } catch (...) {
            cout << "Couldnt Print Process Average";
        }
    }

    if (thread) {
        try {
            tp.printTimesT();
        } catch (...) {
            cout << "Couldnt Print Thread Average";
        }
    }
}


#endif /* COMMAND_LINE_CONTROLLER_H_ */