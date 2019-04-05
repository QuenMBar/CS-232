// CS-232
// Paul Jeon

#include "Prompt.h"

#include <unistd.h>
#include <limits.h>

using namespace std;

// Prompt()
// constructor

Prompt::Prompt()
{

	//  getcwd() function copies an absolute pathname of the current
	// working directory to the array pointed to by buf, which is of length size.
	myDir = getcwd(myPath, PATH_MAX + 1);
}

// get() function
// Return the current directory as string

string Prompt::get() const
{
	return myDir;
}