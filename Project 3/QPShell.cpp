
#include "QPShell.h"

QPShell::QPShell()
{
       notExit = true;
}

void QPShell::run()
{
       pid_t Spid = -1;
       while (notExit)
       {
              Prompt myPrompt;
              cout << myPrompt.get() << "$ ";
              CommandLine CMD(cin);
              // if (!CMD.noAmpersand())
              // {
              //        Spid = fork();
              //        if (Spid == -1)
              //        {
              //               perror("fork error");
              //        }
              // }
              // else
              // {
              string command = CMD.getCommand();
              if (command == "exit")
              {
                     notExit = false;
              }
              else if (command == "cd")
              {
                     string wholeDir = "";
                     for (int i = 1; i < CMD.getArgCount(); i++)
                     {
                            char *newDir = CMD.getArgVector(i);
                            if (wholeDir.size() != 0)
                            {
                                   wholeDir += " ";
                            }
                            wholeDir += newDir;
                     }
                     cout << "Moving to dir: " << wholeDir << "\n"
                          << flush;
                     chdir(const_cast<char *>(wholeDir.c_str()));
              }
              else if (command == "pwd")
              {
                     cout << myPrompt.get() << "\n";
              }
              else
              {
                     try
                     {
                            pid_t pid, w;
                            string commandArg = "";
                            char *commandBit = CMD.getArgVector(0);
                            commandArg = commandArg + "/bin/" + commandBit;
                            int status;

                            char *envp[] = {NULL};
                            char **argvCommand = CMD.getArgVector();
                            argvCommand[0] = const_cast<char *>(commandArg.c_str());

                            if ((pid = fork()) == -1)
                            {
                                   perror("fork error");
                            }
                            else if (pid == 0)
                            {
                                   execve(argvCommand[0], argvCommand, envp);
                                   cout << "Couldn't execute command " << command << "\n"
                                        << flush;
                            }
                            w = waitpid(pid, &status, WUNTRACED | WCONTINUED);
                     }
                     catch (exception e)
                     {
                            cout << "Couldn't execute command " << command << "\n"
                                 << flush;
                     }
              }
       }
       //        if (Spid == 0)
       //        {
       //               // kill(getpid(), SIGKILL);
       //        }
       // }
       // }
}