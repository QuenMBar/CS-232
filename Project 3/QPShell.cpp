
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
              cout << myPrompt.get() << "$ ";
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
              else if (command == "cd")
              {
                     const char *newDir = CMD.getArgVector(1);
                     chdir(newDir);
              }
              else if (command == "pwd")
              {
                     cout << myPrompt.get() << "\n";
              }
              else
              {
                     // Path myPath;
                     // char *env_args[] = {"PATH=/bin", (char *)0};
                     // execve(, CMD.getArgVector(), env_args);
                     try
                     {
                            string wholeCommand = "";
                            for (int i = 0; i < CMD.getArgCount(); i++)
                            {
                                   char *commandBit = CMD.getArgVector(i);
                                   wholeCommand = wholeCommand + commandBit + " ";
                            }
                            system(const_cast<char *>(wholeCommand.c_str()));
                     }
                     catch (exception e)
                     {
                            cout << "Couldn't execute command " << command << "\n"
                                 << flush;
                     }
              }
       }
}