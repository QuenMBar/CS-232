// CS-232
// Paul Jeon

#include "Path.h"

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>

using namespace std;

// Path()
// Path class constructor

Path::Path()
{
    char *token;
    // getenv() function searches the environment list to find the
    // environment variable name, and returns a pointer to the corresponding
    // value string.
    char *myPath = getenv("PATH");

    // strtok = split string into tokens
    // if token is found, returns a pointer to the beginning of the token.
    token = strtok(myPath, ":");
    while (token != NULL)
    {
        dirVec.push_back(token);
        token = strtok(NULL, ":");
    }
}

// find function
// searches dirVec for a given program
// string program - name of desired program
// return: index of dirVec containing the desired program

int Path::find(const string &program) const
{
    int index = 0;
    DIR *curDir;
    struct dirent *myEnt;

    for (unsigned i = 0; i < dirVec.size(); i++)
    {
        if ((curDir = opendir(dirVec[i])) != NULL)
        {
            while ((myEnt = readdir(curDir)) != NULL)
            {
                if (myEnt->d_name == program)
                {
                    index = i;
                }
                readdir_r(curDir, myEnt, &myEnt);
            }
        }
        closedir(curDir);
    }
    return index;
}

// getDirectory(int i)
// getter for dirVec
// parameter: int i
// returns: string path at index

string Path::getDirectory(int i) const
{
    string myDir = dirVec[i];
    return myDir;
}
