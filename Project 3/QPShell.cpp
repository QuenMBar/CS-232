/** QPShell.cpp is a shell that allows the user to execute most of the commands that a regular shell would.  It recognizes cd,
 * pwd, and exit internaly and uses the function evecve for the other commands.  To do this it uses the command, path, 
 * and prompt classes.  
 * 
 * Written by: Quentin Barnes
 * Date: April 12, 2019
 */

#include "QPShell.h"

/**Creates the shell and initilizes its running variable to true
 * receives: N/a
 * passes: N/a
 */
QPShell::QPShell()
{
       notExit = true;
}

/**
 * Command is used to start the shell by putting it into a while loop until exit is called by the user
 * or the shell is terminated some other way.
 * receives: N/a
 * passes: N/a
 */
void QPShell::run()
{
       while (notExit)
       {
              Prompt myPrompt;
              cout << myPrompt.get() << "$ "; // Prints the path of the working directory
              CommandLine CMD(cin);           // Creates a CommandLine from an istream
              if (!CMD.noAmpersand())         // Checks to see if there is an "&"
              {
                     try
                     {
                            pid_t Spid, l;
                            int status2;
                            Spid = fork();  // Creates a seperate process for the command to run on
                            if (Spid == -1) //fork error
                            {
                                   perror("fork error");
                            }
                            else if (Spid == 0) //Child process
                            {
                                   cout << "\n"
                                        << flush;
                                   string command = CMD.getCommand(); // Gets given command and turns it into a string
                                   if (command == "exit")             //If exit, it runs the exit function
                                   {
                                          exitShell();
                                   }
                                   else if (command == "cd") // IF cd runs the change directory function
                                   {
                                          changeDir(CMD);
                                   }
                                   else if (command == "pwd") // If pwd, runs printWorkDir function
                                   {
                                          printWorkDir(myPrompt);
                                   }
                                   else // Else it treats it as a command to be run by execve
                                   {
                                          runCommand(CMD, command);
                                   }
                                   kill(getpid(), SIGKILL); //kills the process being used to run the command
                                   CMD.kill();              // Kills the instance of CommandLine, reclaiming memory
                            }
                            else // Parent Process
                            {
                                   // l = waitpid(Spid, &status2, WUNTRACED | WCONTINUED);        // If we wanted the prompt
                                   // to still happen after the output
                            }
                     }
                     catch (exception e)
                     {
                            cout << "Error with fork \n" // Fork error pt. 2
                                 << flush;
                     }
              }
              else
              {
                     string command = CMD.getCommand(); // Gets given command and turns it into a string
                     if (command == "exit")             //If exit, it runs the exit function
                     {
                            exitShell();
                     }
                     else if (command == "cd") // IF cd runs the change directory function
                     {
                            changeDir(CMD);
                     }
                     else if (command == "pwd") // If pwd, runs printWorkDir function
                     {
                            printWorkDir(myPrompt);
                     }
                     else // Else it treats it as a command to be run by execve
                     {
                            runCommand(CMD, command);
                     }
                     CMD.kill(); // Kills the instance of CommandLine, reclaiming memory
              }
       }
}

/**
 * Sets the value of notExit to false, ending the program
 * receives: N/a
 * passes: N/a
 */
void QPShell::exitShell()
{
       notExit = false;
}

/**
 * Prints the prompt that it is given
 * receives: A Prompt
 * passes: N/a
 */
void QPShell::printWorkDir(Prompt myPrompt)
{
       cout << myPrompt.get() << "\n";
}

/**
 * Changes the directory given arguments of a command
 * receives: A CommandLine
 * passes: N/a
 */
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
       chdir(const_cast<char *>(wholeDir.c_str()));
}

/**
 * Tries to run the command specified by the CommandLine.  If it cannot be run, prints that the command doesnt exist
 * receives: A CommandLine and a string
 * passes: N/a
 */
void QPShell::runCommand(CommandLine CMD, string command)
{
       try
       {
              pid_t pid, w;
              string commandArg = "";
              char *commandBit = CMD.getArgVector(0);         //gets the command from the CommandLine
              commandArg = commandArg + "/bin/" + commandBit; // turns it into a readable command for exevce
              int status;

              char *envp[] = {NULL}; // Enviormental variables
              char **argvCommand = CMD.getArgVector();
              argvCommand[0] = const_cast<char *>(commandArg.c_str()); // Turns the command at the begining of argv into something execve can read

              if ((pid = fork()) == -1) // Fork error
              {
                     perror("fork error");
              }
              else if (pid == 0) // Child process
              {
                     execve(argvCommand[0], argvCommand, envp); // runs the command
                     cout << "Couldn't execute command " << command << "\n"
                          << flush;
              }
              w = waitpid(pid, &status, WUNTRACED | WCONTINUED); // waits for the child process to finish executing the command
              if (pid == 0)                                      // Child process again
              {
                     kill(getpid(), SIGKILL); // Kills the child process
              }
       }
       catch (exception e) // if execve fails, tells the user it couldnt execute the command
       {
              cout << "Couldn't execute command " << command << "\n"
                   << flush;
       }
}

// Gave errors if used because variables were being deleated before they could be used
//
// void QPShell::parseCommand(CommandLine CMD, Prompt myPrompt)
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