/** Prompt.h is the header file for Prompt.cpp
 * 
 * Written by: Paul Jeon
 * Date: April 12, 2019
 */

#ifndef PROMPT_H_
#define PROMPT_H_

#include <string>
#include <linux/limits.h>

using namespace std;

class Prompt
{

public:
  Prompt();
  string get() const;

private:
  string myDir;
  char myPath[PATH_MAX];
};

#endif
