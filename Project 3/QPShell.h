#ifndef QPSHELL_H_
#define QPSHELL_H_

#include "CommandLine.h"
#include "Prompt.h"
#include "Path.h"

#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
using namespace std;

class QPShell
{
public:
  QPShell();
  void run();

private:
  bool notExit;
  int childArgc;
  char **childArgv;
};

#endif /* QPSHELL_H_ */