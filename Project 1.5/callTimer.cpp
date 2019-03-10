/*
 * callTimer.cpp is a C++ driver for reading the command line input and either launching the command line controller or
 * or the text interface controller.
 *
 *  Created on: Feb 13, 2019
 * 	Edited on:	Feb 26, 2019
 *      Author: Quentin Barnes
 * 		CS Lab
 * 
 * Can be compiled uning the command g++ -pthread -o callTimer callTimer.cpp ThreadProcess.cpp
 * Can be run using the command ./callTimer 
 */

#include "CommandLineController.h"
#include "TextBasedController.h"

int main(int argc,char* argv[]) 
{   
	if(argc > 1){
		CommandLineController CLC;
		CLC.run(argc, argv);
	} else {
		TextBasedController TBC;
		TBC.run();
	}
}
