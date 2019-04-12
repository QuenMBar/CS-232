/**Run.cpp is the executable file that calls the QPShell to init it, and then gives it the command to run.
 * This program can be run by g++ -o run run.cpp QPShell.cpp CommandLine.cpp Prompt.cpp Path.cpp
 * 
 * Date: April 12, 2019
 */

#include "QPShell.h"
using namespace std;

int main()
{
    QPShell myShell;
    myShell.run();
}
