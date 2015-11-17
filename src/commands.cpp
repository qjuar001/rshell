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

#include "commands.h"
#include <boost/tokenizer.hpp>
#include <boost/token_iterator.hpp>
#include <iostream>
#include <algorithm>
#include "connecters.h"
#include "testCmd.h"
#include <vector>

using namespace std;

bool commands::parse()
{  
   int size = cmd.length();		  //Gets the size fo the cmd entered
   int check = 0;                         //Holds position of cmd in line
   int conCnt = 0;                        //Holds number of commands passed
   int preCnt = 0;
   bool precedence[1024];
   bool preWorked = false;
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
      bool preExists = false;

      //A loop that moves a single command into the temp array
      while(line[check] != ';' && line[check] != '|' && 
            line[check] != '&' && line[check] != '#' && line[check] != '\0')
      {
         //If there is a precedence operator then seperate it and execute
         //seperately in another command.
         if(line[check] == '(' && cmd.length() >= 2)
         {
            string tmp; //Holds the new command to be executed in precedence
            int numStartParen = 1; //Holds num of ( found
            int numEndParen = 0; //Holds num of ) found
            int strSegment = 0; //Holds the size of the string

            check++; //Move the check of the ( character

            int strSegBegin = check; //Holds the beginning of the string
           
            //Keeps track of paired parenthasis and grabs a segment of string
            while(line[check] != ')' || numStartParen != numEndParen)
            {
               if (line[check] == '(')
                  numStartParen++; //Keeps track of starting parenthesis
               else if (line[check] == ')')
                  numEndParen++;  //Keeps track of ending parenthesis

               if (line[check] == ')' && numStartParen == numEndParen)
               {} //If the last ) is found then don't increment array or string
               else
               {
                  check++;
                  strSegment++;
               }
            }
 
            //If run is true then create a new string command and then create a new command object
            //with that string and parse it. worked recieves value returned by parse.
            if (run[conCnt] == true)
            {
               tmp.assign(cmd, strSegBegin, strSegment); //Creates a new string cmd
               commands tmpCmd(tmp); //Creates a new command object
               worked = tmpCmd.parse();
               preExists = true; //Determines if the commands have been executed already
            }
            else
               check++;
         }
         else
         {
            tmp[restart] = line[check];      //Transfer command from line to tmp
            check++;			  //Moves through orginal string
            restart++;                       //Move through tmp array
         }
      }
      
      if(preExists) //If commands have been executed in precedence then skip the process below
      {}
      else
      { 
         tmp[sizeof(tmp) - 1] = 0; //Makes sure tmp array ends with a NULL
         char def[10] = "-e";      //Hold the default flag -e
         bool flag = false;        //Determines if a flag exists
         bool bracket = false;     //Determines if there is a bracket
         bool runTestExe = false;
         //int posBrack = 0;       //Holds the position of the bracket
         //int j = 0;
         string brackStr(tmp);   //Makes a copy of tmp array and makes it a string
         testCmd checkDef;
         checkDef.checkFlag(tmp, brackStr, flag, bracket); 
         int i = 0; //Keeps track of position in argv
         
         char *token; //Token that parses the string

         if (bracket)
            token = strtok(tmp, ";|&#[] ");
         else
            token = strtok(tmp, ";|&# ");  

         //Seperated the string into segments that are then stored in argv
         while(token != NULL)
         {
            //If the string is exit then stop the program
            if (strcmp(token, "exit") == 0)
            {
               stop = true; 
               exit(0);
            }
            //If there wasn't a flag declared and there is a bracket or test detected then act
            //accordingly
            if (strcmp(token, "test") == 0 || bracket)
            {
               //If there is a bracket..
               if(!bracket && !flag)
               {
                  argv[i] = def; //then point argv to the default -e flag
                  i++;  //then increment the argv value
               }
               else if (strcmp(token, "test") != 0)
               {
                  argv[i] = strdup(token);
                  i++;
               }
               token = strtok(NULL, ";|&#[] "); //Go back to get another token
               runTestExe = true;
            }
            else
            {
               argv[i] = strdup(token);	//Copies token into argv
               token = strtok(NULL, ";|&# ");  //Gets another token
               i++;				//Move location of argv
            }
         }
         argv[i] = NULL; //Makes last position a NULL character
      
         //If the position in run is true then execute the current cmd     
         if (run[conCnt] == true)
         {
            if(runTestExe)
            {
              checkDef.execute(argv);
              worked = checkDef.getWorked(); //FIX ME
            }
            else
               execute(argv); //executes the commands
            precedence[preCnt] = worked;
            conCnt++;
         }
         else //If false, then dont run the command
         {
            conCnt++;
         }
      }
      //A check to see if a comment was entered, if so then ignore whats next
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

      preCnt++;  
    
      //If check is the size of the string then stop function and get another cmd
      if (check >= size)
         done = true;
   }

   //A for loop that checks if at least one command succeeded, if so then set preWorked to true
   for( int i = 0; i < preCnt; i++)
   {
      if(precedence[i] == true)
      {
         preWorked = true;
         break;
      }
   }
   return preWorked; //Return a bool for precedence check
}



