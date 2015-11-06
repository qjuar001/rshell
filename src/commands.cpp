#include "commands.h"
#include <boost/tokenizer.hpp>
#include <boost/token_iterator.hpp>
#include <iostream>
#include <algorithm>
#include "connecters.h"
#include <vector>

using namespace std;

void commands::parse()
{  
   int size = cmd.length();		  //Gets the size fo the cmd entered
   int check = 0;                         //Holds position of cmd in line
   int conCnt = 0;                        //Holds number of commands passed
   bool done = false;			  //Bool to determine if execution is done
   stop = false;			  //Bool to determine if exit was entered
   bool run[1024];                        //Array to determine if next cmd runs
   OR theOR;				  //Object that holds the || operator
   AND theAND;				  //Object that holds the && operator

   run[0] = true;			  //Makes sure the first cmd runs

   while (!done)
   {
      char tmp[1024] = {0};		  //Sets all values in tmp to NULL
      memset(argv, 0, sizeof(argv));	  //Sets all values in argv to NULL
      int restart = 0;                    // Restarts temp array from beginning

      //A loop that moves a single command into the temp array
      while(line[check] != ';' && line[check] != '|' && 
            line[check] != '&' && line[check] != '#' && line[check] != '\0')
      {
         tmp[restart] = line[check];      //Transfer command from line to tmp
         check++;			  //Moves through orginal string
         restart++;                       //Move through tmp array
      }
       
      tmp[sizeof(tmp) - 1] = 0; //Makes sure tmp array ends with a NULL

      int i = 0; //Keeps track of position in argv
      char *token = strtok(tmp, ";|&# "); //Token that parses the string
   
      //Seperated the string into segments that are then stored in argv
      while(token != NULL)
      {
         //If the string is exit then stop the program
         if (strcmp(token, "exit") == 0)
         {
            stop = true; 
            exit(0);
         }
         argv[i] = strdup(token);	//Copies token into argv
         token = strtok(NULL, ";|&# ");  //Gets another token
         i++;				//Move location of argv
      }
      argv[i] = NULL; //Makes last position a NULL character
      
      //IF the position in run is true then execute the current cmd     
      if (run[conCnt] == true)
      {
         execute(argv); //executes the commands
         conCnt++;
      }
      else //IF flase, then dont run the command
      {
         this->worked = false;
         conCnt++;
      }
       
      //A checck to see if a comment was entered, if so then ignore whats next
      if(line[check] == '#' && (line[check - 1] == ' ' || line[check -1] == ';'
         || line[check - 1] == '|' || line[check - 1] == '&'))
         break;
      
      //Determines if the OR operator is present
      else if (line[check] == '|' && line[check + 1] == '|')
      {  
         //calls the compare function to determine if next cmd should run
         run[conCnt] = theOR.compare(this->worked);
         check+=2;
      }

      //Determines if the AND operator is present
      else if (line[check] == '&' && line[check + 1] == '&')
      {
         //Calls the AND compare function to determine if next cmd should run
         run[conCnt] = theAND.compare(this->worked);
         check+=2;
      }
      else
      {
         //If neither OR or AND are present then always run next command
         check++;  
         run[conCnt] = true;
      } 
      
      //If check is the size of the string then stop function and get another cmd
      if (check >= size)
         done = true;
   }
}



