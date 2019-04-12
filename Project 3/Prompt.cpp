/** Prompt.cpp represents the command-line prompt.
 * 
 * Written by: Paul Jeon
 * Date: April 12, 2019
 */

#include "Prompt.h"

#include <unistd.h>
#include <limits.h>

using namespace std;


/** A constructor that builds a Prompt as the full path to the working directory
 * Receives: N/a
 * Passes: N/a
 */
Prompt::Prompt()
{

	//  getcwd() function copies an absolute pathname of the current
	// working directory to the array pointed to by buf, which is of length size.
	myDir = getcwd(myPath, PATH_MAX + 1);
}

/** An accessor that returns the current value of the Prompt.
 * Receives: N/a
 * Passes: myDir
 */
string Prompt::get() const
{
	return myDir;
}
