/*
 * TextBasedUi.h is the class that mannages the UI for the controller (TextBasedController.h).  Based on 
 * the parameters it's given, it will display them and the users options for inputs.
 * 
 *  Created on: Feb 26, 2019
 *      Author: Quentin Barnes
 * 		CS LAB
 */

#ifndef TEXT_BASED_UI_H_
#define TEXT_BASED_UI_H_

#include <iostream>
using namespace std;

class TextBasedUi {
public:
	void run(bool threadNew, bool processNew, int timeToRunNew, bool errorNew);
    void getRunTimes();
    bool error = false;             // Flag for an input error
    bool thread = false;  	        // Flag for if the threads run
    bool process = false;  	        // Flag for if the process run
    int timesToRun = 1;		        // How many repitions the program is set to do
private:
};

/**
 * run() is used to create the UI with the given parameters that are updated everytime 
 * the function is called.  It is a simple text based UI that prints the users options 
 * then allows them to enter their input.
 * recives: bool threadNew - If the threads are being run
 *          bool processNew - If the processes are being run
 *          int timeToRunNew - How many times the program will run
 *          bool errorNew - If there was an error last time
 * returns: nothing
 */
void TextBasedUi::run(bool threadNew, bool processNew, int timeToRunNew, bool errorNew){
    //Saves the values locally
    thread = threadNew;
    process = processNew;
    timesToRun = timeToRunNew;
    error = errorNew;

    //Writes out the UI
    cout << "\n-------------------------\n\n-------------------------\n\nTimes to run: \t\t" << timesToRun << "\nRun Threads: \t\t";
    if(thread) {
        cout << "Yes";
    } else {
        cout << "No";
    }
    cout << "\nRun Processes: \t\t";
    if(process) {
        cout << "Yes";
    } else {
        cout << "No";
    }

    cout << "\n\n-------------------------\n\n" <<
    "1:\tChange amount of run times\n" <<
    "2:\tChange if threads are run\n" <<
    "3:\tChange if processes are run\n" <<
    "4:\tRUN with the given parameters\n" <<
    "5:\tRe-print the average time for threads to be created during the last run\n" <<
    "6:\tRe-print the average time for processes to be created during the last run\n" <<
    "7:\tQUIT\n\n-------------------------\n\n";

    //Displays error if needed
    if(error) {  
        cout << "Please enter a valid input of a number from 1-6\n";
    }

    cout << "Enter a number to continue: ";

}

/**
 * getRunTimes() is used to allow the user to update how many times they want processes 
 * and threads to be created
 * It is passed and returns nothing
 */
void TextBasedUi::getRunTimes() {
    cout << "\n\n-------------------------\n\n"
    << "Enter amount of times to run: ";
}


#endif /* TEXT_BASED_UI_H_ */