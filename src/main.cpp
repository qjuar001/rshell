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

#include <iostream>
#include <string>
#include <sys/unistd.h>
#include <stdio.h>
#include <unistd.h>
#include "commands.h"

using namespace std;

int  main()
{
   // Prints out license at start of terminal
   cout << endl << "rshell Copyright (C) 2015 Queston Juarez & Mark Spencer\n"
        << "This program comes with ABSOLUTELY NO WARRANTY.\n"
        << "This is free software, and you are welcome to redistribute it\n"
        << "under certain conditions.\n" << endl;

   char *name;                   // char string to hold login name
   char hostname[1024];          // char array to hold hostname
   int host;                     // variable to deterimine if successful

   //Get the users login name and checks for an error
   name = getlogin();
   if (name == '\0')
      perror("getlogin() error");
 
   //Get the users hostname and checks for an error
   hostname[1023] = '\0';
   host = gethostname(hostname, 1023);
   if (host == -1)
      perror("gethostname() error");

   //Loop through shell until exit is typed
   while (1) 
   {
      string cmd = "";
      //Print out the command line
      while (cmd == "")
      {
         cout << '[';
         printf(name);
         cout << "@";
         printf("%s", hostname);
         cout << ']';
         cout << "$ ";

//Read in the command line
         getline(cin, cmd);
      }
      
      commands newCmd(cmd);
      newCmd.parse();
      if (newCmd.getExit() == true)
         break;
   }  

   return 0;

}
