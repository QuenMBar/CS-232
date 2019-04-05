// CS-232
// Paul Jeon

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