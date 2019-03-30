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
        if (commandEntered.find(" ", otherInc) == i)
        {
            otherInc = i + 1;
            argc++;
        }
        else if (commandEntered.find(" ", otherInc) == otherInc + 1)
        {
            otherInc++;
        }
    }
    if (commandEntered.find(" ", commandEntered.size() - 1) != (commandEntered.size() - 1))
    {
        argc++;
    }

    argv = (char *)calloc(argc, 10);
    otherInc = 0;
    int otherOtherInc = 0;
    for (int i = 0; i < commandEntered.size(); i++)
    {
        cout << "For " << i << ": ";
        if (commandEntered.find(" ", otherInc) == 0)
        {
            otherInc++;
        }
        else if (commandEntered.find(" ", otherInc) == i)
        {
            cout << otherInc << ": " << i << "\n"
                 << flush;
            strcpy(&argv[otherOtherInc], commandEntered.substr(otherInc, i - otherInc).c_str());
            cout << "Substrings: " << commandEntered.substr(otherInc, i - otherInc) << "\n"
                 << flush;
            otherInc = i + 1;
            otherOtherInc++;
        }
    }
    if (commandEntered.find(" ", commandEntered.size() - 1) != (commandEntered.size() - 1))
    {
        strcpy(&argv[otherOtherInc], commandEntered.substr(otherInc, commandEntered.size() - 1).c_str());
        cout << "Substrings: " << commandEntered.substr(otherInc, commandEntered.size() - 1) << "\n"
             << flush;
    }
}

void CommandLine::printCommand()
{
    cout << "\n"
         << argc << "\n\n";
    for (int i = 0; i < argc; i++)
    {
        cout << argv[i] << "\n";
    }
    cout << flush;
}