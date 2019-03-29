/*
 * ThreadProcess.cpp is a class that can create and time processes and threads and print the average times that they took to create.
 *
 *  Created on: Feb 13, 2019
 *      Author: Quentin Barnes
 * 		CS LAB
 */

#include "CommandLine.h"

CommandLine::CommandLine(istream &in)
{
    getline(in, commandEntered);
    argc = 0;
    int otherInc = 0;
    for (int i = 0; i < commandEntered.size(); i++)
    {
        if (commandEntered.find(" ", otherInc) == 0)
        {
            otherInc++;
        }
        else if (commandEntered.find(" ", otherInc) == i)
        {
            otherInc = i + 1;
            argc++;
        }
    }
    if (!(commandEntered.find(" ", commandEntered.size() - 1) == (commandEntered.size() - 1)))
    {
        argc++;
    }
}

void CommandLine::printCommand()
{
    cout << commandEntered << ": " << argc << "\n"
         << flush;
}