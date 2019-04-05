
#include "QPShell.h"

QPShell::QPShell()
{
       notExit = true;
}

void QPShell::run()
{
       while (notExit)
       {
              Prompt myPrompt;
              cout << myPrompt.get() << " ";
              CommandLine CMD(cin);
              // cout << CMD.getCommand() << "\n"
              //      << CMD.getArgVector(3) << "\n"
              //      << CMD.getArgCount() << "\n"
              //      << CMD.noAmpersand() << "\n"
              //      << CMD.getArgVector() << "\n"
              //      << flush;
              string command = CMD.getCommand();
              if (command == "exit")
              {
                     notExit = false;
              }
              else
              {
                     // Path myPath;
                     // char *env_args[] = {"PATH=/bin", (char *)0};
                     // execve(, CMD.getArgVector(), env_args);
                     cout << "Couldn't execute command " << command << "\n"
                          << flush;
              }
       }
}