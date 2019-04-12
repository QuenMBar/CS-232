/**Path.cpp represents the directories in which QPShell searches for the executable
 * programs.
 * 
 * Written by: Paul Jeon
 * Date: April 12, 2019
 */

#include "Path.h"

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>

using namespace std;

/**
 * Constructs a Path from PATH environment variable
 * Receives: N/a
 * Passes: N/a
 */
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

/**
 * Returns the index of the directory containing program.
 * Receives: string &program
 * Passes: index of dirVec containing the desired program
 */
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

/**
 * Returns the name of the directory whose index is i.
 * Receives: i, an int
 * Passes: myDir (string path at index i)
 */
string Path::getDirectory(int i) const
{
    string myDir = dirVec[i];
    return myDir;
}
