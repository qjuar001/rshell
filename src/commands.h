#ifndef COMMANDS_H
#define COMMANDS_H

#include <algorithm>
#include <string>
#include <iostream>
#include "cmdWorked.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

class commands: public cmdWorked
{ 
   protected:
      char line[1024];
      char *argv[64];
      bool stop;
      std::string cmd;
  
   public:
      commands (std::string c)
      {
         cmd = c;
         strncpy(line, cmd.c_str(), sizeof(line));
         line[sizeof(line) - 1] = 0;
         printf("\n");
      };

      ~commands()
     {};
 
      void execute (char **argv)
      {
     
         pid_t  pid;
         int    status;

         if ((pid = fork()) < 0) 
         {     /* fork a child process           */
            printf("*** ERROR: forking child process failed\n");
            exit(1);
         }
         else if (pid == 0) 
         {          /* for the child process:         */
            if (execvp(argv[0], argv) < 0) /* Executes the command       */
            {     
               worked = false;   //If cmd failed, set variable to false
               printf("*** ERROR: exec failed\n");
               //exit(1);
            }
            else
               worked = true;       //If cmd succeeded, set variable to true
         }
         else 
         {                                  /* for the parent:      */
            while (wait(&status) != pid)       /* wait for completion  */
            ;
         }
      };

      void parse ();

      bool getExit()
      {
         return stop;
      };
    
};

#endif
