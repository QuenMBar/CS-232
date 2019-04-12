/** CommandLine.cpp is a class that can parse an istream to get a command for a shell to use.  It creates argc and argv
 * along with noting if the command had an "&" in it.  It then can return those things to the shell if requested.
 * 
 * Written by: Quentin Barnes
 * Date: April 12, 2019
 */

#include "CommandLine.h"

/**Constructor for the CommandLine class.  Uses an istream to create argc and argv
 * along with noting if the command had an "&" in it. 
 * receives: A istream
 * passes: N/a
 */
CommandLine::CommandLine(istream &in)
{
    getline(in, commandEntered);
    vector<string> myStringVec;
    int otherInc = 0;
    noAndFlag = true;
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
    argv = (char **)calloc(myStringVec.size() + 1, sizeof(char *) + 1);

    for (int i = 0; i < myStringVec.size(); i++)
    {
        if (myStringVec[i] == "&")
        {
            noAndFlag = false;
            argc--;
        }
        else
        {
            argv[i] = const_cast<char *>(myStringVec[i].c_str());
        }
    }
    argv[argc] = NULL;
}

/** Default constructor
 * receives: N/a
 * passes: N/a
 */
CommandLine::CommandLine()
{
    noAndFlag = true;
    argc = 0;
    argv = NULL;
}

/** Frees up the space that calloc() used for argv
 * receives: N/a
 * passes: N/a
 */
void CommandLine::kill()
{
    free(argv);
}

/** return a pointer to the command portion of the command line
 * receives: N/a
 * passes: a char * pointer
 */
char *CommandLine::getCommand() const
{
    return argv[0];
}

/** return the number of command line arguments on the command line
 * receives: N/a
 * passes: An int
 */
int CommandLine::getArgCount() const
{
    return argc;
}

/** return a pointer to a char* array, each entry of which points to one 'word' of the command line
 * receives: N/a
 * passes: a char ** pointer 
 */
char **CommandLine::getArgVector() const
{
    return argv;
}

/** return a pointer to the ith command line 'word'
 * receives: An int
 * passes: a char * pointer
 */
char *CommandLine::getArgVector(int i) const
{
    return argv[i];
}

/** returns true if and only if no ampersand was given on the command line
 * receives: N/a
 * passes: A bool
 */
bool CommandLine::noAmpersand() const // returns true if and only if no ampersand was given on the command//line
{
    return noAndFlag;
}