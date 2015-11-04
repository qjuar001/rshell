#include "commands.h"
#include <boost/tokenizer.hpp>
#include <boost/token_iterator.hpp>
#include <iostream>
#include <algorithm>

using namespace std;

void commands::parse()
{  
   int size = cmd.length();
   int check = 0;
   bool done = false;
   stop = false;

   while (!done)
   {
      char tmp[1024] = {0};
      memset(argv, 0, sizeof(argv));
      int restart = 0;                    // Restarts temp array from beginning
      //A loop that moves a single command into the temp array
      while(line[check] != ';' && line[check] != '|' && 
            line[check] != '&' && line[check] != '#' && line[check] != '\0')
      {
         //Check to see if the last character in cmd is a space, if so
         //then break out of loop
         //if(line[check] == ' ' && (line[check + 1] == '|' ||
         //   line[check + 1] == '&' || line[check + 1] == '#' || 
         //   line[check + 1] == '\0') && restart != 0)
         //   break;
         tmp[restart] = line[check];      //Transfer command from line to tmp
         check++;
         restart++;                       //Move through tmp array
      }
      check++;

      tmp[sizeof(tmp) - 1] = 0; 
      if (strcmp(tmp, "exit") == 0)
      {
         stop = true;
         exit(0); 
      }

      int i = 0; //Keeps track of position in argv
      char *token = strtok(tmp, ";|& "); //Token that parses the string
   
      //Takes every part of string and assigns to the array
      while(token != NULL)
      {
         argv[i] = strdup(token);
         token = strtok(NULL, ";|& ");
         i++;
      }
      argv[i] = NULL; //Makes last position a NULL character
      execute(argv); //executes the commands
      if(worked == true)
         cout << "Good" << endl;
      else
         cout << "bad" << endl;
      if (check >= size)
         done = true;
   }
}



