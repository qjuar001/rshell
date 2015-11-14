// <This program essetially mocks a common shell terminal.>
// Copyright (C) <2015>  <Queston Juarez & Mark Spencer>

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>

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
      char line[1024];   //Array to hold c string of command line
      char *argv[64];    //Holds each individual command after parse
      bool stop;         //Bool to determine if program should terminate
      std::string cmd;   //String that holds original command
  
   public:

      //Constructor to create command object
      commands (std::string c)
      {
         cmd = c;   //Sets cmd to the string entered to console
         
         //Converts cmd to a c string then stores it into the line array
         strncpy(line, cmd.c_str(), sizeof(line));
         line[sizeof(line) - 1] = 0;
      };

      //Destructor for class commands
      ~commands()
     {};
 
      //Function that executes a command
      void execute (char **argv)
      {
     
         pid_t c_pid, pid;		//Values to hold fork and wait
         int status;

         if ((c_pid = fork()) < 0) 
         {     // fork a child process 
            printf("*** ERROR: forking child process failed\n");
            exit(1);
         }
         else if (c_pid == 0) 
         {          // for the child process:
            if (execvp(argv[0], argv) < 0) // Executes the command
            {
               worked = false;     
               printf("*** ERROR: exec failed\n");
               _exit(1);
            }
         }
         else if (c_pid > 0) 
         {                                  
            if ( (pid = waitpid(c_pid, &status,0)) < 0) //Wait for child to finish
            {
               worked = false;
               perror("wait");
               _exit(1);
            } 
            
            if(status > 0) //If status is returned bigger than 0, command failed
               worked = false;
            else if(status == 0) //If status returned 0, everything worked fine
               worked = true;
         }
      };

      bool parse ();    //Function to parse the command entered

      bool getExit()    //Function to see value of stop
      {
         return stop;
      };
    
};

#endif
