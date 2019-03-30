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
    for (int i = 0; i < commandEntered.size(); i++)
    {
        if ((commandEntered[i] == ' ') && (commandEntered[i + 1] != ' '))
        {
            argc++;
        }
    }
    if (commandEntered[commandEntered.size() - 1] != ' ')
    {
        argc++;
    }
    char **test = (char **)calloc(4, sizeof(char *));
    int otherInc = 0;
    int lastInc = 0;
    for (int i = 0; i < commandEntered.size(); i++)
    {
        if ((commandEntered[i] == ' ') && (commandEntered[i + 1] != ' '))
        {
            // test[lastInc] = (char *)commandEntered.substr(otherInc, i - otherInc).c_str();
            otherInc = i + 1;
            lastInc++;
        }
    }
    if (commandEntered[commandEntered.size() - 1] != ' ')
    {
        // char *newTempStr = (char *)commandEntered.substr(otherInc, commandEntered.size() - 1 - otherInc).c_str();
        // test[lastInc] = newTempStr;
    }
    test[0] = "Help";
    test[1] = "me";
    test[2] = "please";
    test[3] = "guys";
    cout << "Testing: " << *test+1 << "\n"
         << flush;
    argv = test;
}

void CommandLine::printCommand()
{
    cout << "\n"
         << argc << "\n\n";
    // for (int i = 0; i < 1; i++)
    // {
    //     cout << argv[i] << "\n";
    // }

    cout << *argv[0] << "\n";
    cout << flush;
}