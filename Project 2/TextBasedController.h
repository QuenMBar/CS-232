/*
 * TextBasedController.h is a class that controls the text based UI for callTimer.cpp.  It calls and mannages 
 * the UI (TextBasedUi.h) and the model (ThreadProcess.h).  
 * 
 *  Created on: Feb 26, 2019
 *      Author: Quentin Barnes
 * 		CS LAB
 */

#ifndef TEXT_BASED_CONTROLLER_H_
#define TEXT_BASED_CONTROLLER_H_

#include "ThreadProcess.h"
#include "TextBasedUi.h"

#include <iostream>
using namespace std;

class TextBasedController {
public:
	void run();
    bool thread = false;  	        // Flag for if we run threads
    bool process = false;  	        // Flag for if we run processes
    bool threadPrint = false;  	    // Flag for reprinting thread
    bool processPrint = false;      // Flag for reprinting process
    bool error = false;	            // Flag if there is an invalid input
    int timesToRun = 1;		        // How many repitions the program is set to do
    int commandEntered;             
private:
    ThreadProcess tp;               // Model
    TextBasedUi textUI;             // UI
};

/**
 * Run() is what controls the TextBasedUI and ThreadProcess class.  It will run until 
 * the user quits out of it
 * 
 * It isn't passed any values and doesnt return any values
 * 
 */
void TextBasedController::run(){

    //This allows the program to run until the user tells it to quit
    while (true) {          
        textUI.run(thread, process, timesToRun, error);  // Runs the UI passing it any info it needs
        cin >> commandEntered;   // Grabs the number entered
        cout << "\n";
        switch (commandEntered)  // Uses the number entered to do what function it specified
        {
            //Lets the user change the amount of times the threads or processes should be created
            case 1:
                textUI.getRunTimes();
                cin >> timesToRun;
                if(timesToRun <= 0) {
                    timesToRun = 1;
                    cout << "Please enter a postive number";
                }
                error = false;
                break;
            //Sets the threads to either run or not
            case 2:
                thread = !thread;
                error = false;
                break;
            //Sets the processes to either run or not
            case 3:
                process = !process;
                error = false;
                break;
            //Runs the program with the paramaters given
            case 4:
                if (!process && !thread) {  //Makes sure either processes or threads are set to run
                    cout << "Please select to run processes or threads or both.\n";
                }
                
                //Creates processes or threads depending on the parameters
                if (process) {
                    tp.createProcesses(timesToRun);
                }

                if (thread) {
                    tp.createThreads(timesToRun);
                }

                //Sleeps so that processes and threads can finish creating
                sleep(.2);

                //Prints how long it took to create processes or threads depending on the parameters
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
                error = false;
                break;
            // Reprints the average times for treads
            case 5:
                try {
                    tp.printTimesT();
                } catch (...) {
                    cout << "Couldnt Print Thread Average\n";
                }
                error = false;
                break;
            // Reprints the average times for processes
            case 6:
                try {
                    tp.printTimesP();
                } catch (...) {
                    cout << "Couldnt Print Process Average\n";
                }
                error = false;
                break;
            //Quits the program
            case 7:
                exit(1);
                break;

            //If no case was called, throws an error
            default:
                error = true;
                break;
        }
    }
}


#endif /* TEXT_BASED_CONTROLLER_H_ */