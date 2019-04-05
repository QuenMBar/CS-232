#ifndef QPSHELL_H_
#define QPSHELL_H_

#include "CommandLine.h"
#include "Prompt.h"
#include "Path.h"

#include <iostream>
#include <string>
#include <unistd.h>
using namespace std;

class QPShell
{
  public:
    QPShell();
    void run();

  private:
    bool notExit;
};

#endif /* QPSHELL_H_ */