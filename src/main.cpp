#include <iostream>
#include <string>
#include <sys/unistd.h>
#include <stdio.h>
#include <unistd.h>
//#include "connectors.h"
#include "commands.h"

using namespace std;

int  main()
{
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
