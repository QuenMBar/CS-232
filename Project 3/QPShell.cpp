

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
              if (!CMD.noAmpersand())
              {
                     try
                     {
                            pid_t Spid, l;
                            int status2;
                            Spid = fork();
                            if (Spid == -1) //fork error
                            {
                                   perror("fork error");
                            }
                            else if (Spid == 0) //Child process
                            {
                                   cout << "\n"
                                        << flush;
                                   string command = CMD.getCommand();
                                   if (command == "exit")
                                   {
                                          exitShell();
                                   }
                                   else if (command == "cd")
                                   {
                                          changeDir(CMD);
                                   }
                                   else if (command == "pwd")
                                   {
                                          printWorkDir(myPrompt);
                                   }
                                   else
                                   {
                                          runCommand(CMD, command);
                                   }
                                   kill(getpid(), SIGKILL);
                            }
                            else // Parent Process
                            {
                                   // l = waitpid(Spid, &status2, WUNTRACED | WCONTINUED);        // If we wanted the prompt
                                   // to still happen after the output
                            }
                     }
                     catch (exception e)
                     {
                            cout << "Error with fork \n"
                                 << flush;
                     }
              }
              else
              {
                     string command = CMD.getCommand();
                     if (command == "exit")
                     {
                            exitShell();
                     }
                     else if (command == "cd")
                     {
                            changeDir(CMD);
                     }
                     else if (command == "pwd")
                     {
                            printWorkDir(myPrompt);
                     }
                     else
                     {
                            runCommand(CMD, command);
                     }
              }
       }
}

void QPShell::exitShell()
{
       notExit = false;
}

void QPShell::printWorkDir(Prompt myPrompt)
{
       cout << myPrompt.get() << "\n";
}

void QPShell::changeDir(CommandLine CMD)
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
       // cout << "Moving to dir: " << wholeDir << "\n"
       //      << flush;
       chdir(const_cast<char *>(wholeDir.c_str()));
       // cout << "Moving to dir: " << wholeDir << "\n"
       //      << flush;
}

void QPShell::runCommand(CommandLine CMD, string command)
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
              if (pid == 0)
              {
                     kill(getpid(), SIGKILL);
              }
       }
       catch (exception e)
       {
              cout << "Couldn't execute command " << command << "\n"
                   << flush;
       }
}

// void QPShell::parseCommand(CommandLine CMD, Prompt myPrompt)  // Gave errors if used and didnt feel like fixing
// {
//        string command = CMD.getCommand();
//        if (command == "exit")
//        {
//               exitShell();
//        }
//        else if (command == "cd")
//        {
//               changeDir(CMD);
//        }
//        else if (command == "pwd")
//        {
//               printWorkDir(myPrompt);
//        }
//        else
//        {
//               runCommand(CMD, command);
//        }
// }