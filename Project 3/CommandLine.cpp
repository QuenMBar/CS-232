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
    vector<string> myStringVec;
    int otherInc = 0;
    for (int i = 0; i < commandEntered.size(); i++)
    {
        if ((commandEntered[i] == ' ') && (commandEntered[i + 1] != ' '))
        {
            myStringVec.push_back(commandEntered.substr(otherInc, i - otherInc));
            otherInc = i + 1;
        }
    }
    if (commandEntered[commandEntered.size() - 1] != ' ')
    {
        myStringVec.push_back(commandEntered.substr(otherInc, commandEntered.size() - otherInc));
    }

    argc = myStringVec.size();
    argv = (char **)calloc(myStringVec.size(), sizeof(char *));

    for (int i = 0; i < myStringVec.size(); i++)
    {
        argv[i] = const_cast<char *>(myStringVec[i].c_str());
    }
}

void CommandLine::printCommand()
{
    cout << "\n"
         << argc << "\n\n";
    cout << "Chars2: \n";
    for (int i = 0; i < argc; i++)
    {
        cout << "For " << i << ": " << argv[i] << "|\n"
             << flush;
    }
}