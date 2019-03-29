/*
 * ThreadProcess.h is the header class for ThreadProcess.cpp.  It defines all the needed includes, functions, 
 * and variables for the class.  This is the Model class that the interfaces use.
 *
 *  Created on: Feb 13, 2019
 *      Author: Quentin Barnes
 * 		CS LAB
 */

#ifndef COMMANDLINE_H_
#define COMMANDLINE_H_

#include <stdio.h>
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

class CommandLine
{
  public:
	CommandLine(istream &in);		 // construct a CommandLine by reading a command//line from in, parsing it, and building instance variables for argc and argv (you may find the calloc() and free() system calls to be of use here).
	char *getCommand() const;		 // return a pointer to the command portion of the command//line (i.e., argv[0]).
	int getArgCount() const;		 // return the number of command//line arguments on the command//line (i.e., argc).
	char **getArgVector() const;	 // return a pointer to a char* array, each entry of which points to one 'word' of the command//line (i.e., argv).
	char *getArgVector(int i) const; // return a pointer to the ith (zero//relative) command//line 'word' (i.e., argv[i]).
	bool noAmpersand() const;		 // returns true if and only if no ampersand was given on the command//line
	void printCommand();

  private:
	int argc;
	char *argv[];
	string commandEntered;
};

#endif /* COMMANDLINE_H_ */