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

#ifndef TEST_H
#define TEST_H

#include <sys/types.h>
#include <sys/stat.h>
#include "cmdWorked.h"

class testCmd : public cmdWorked
{
   protected:
       
   
   public:
      
      void checkFlag(char *tmp, string &brackStr, bool &flag, bool &bracket)
      {
         unsigned j = 0;
         int posBrack = 0;

         //Traverse the array and look for any flags
         for ( j = 0; j  < brackStr.size() - 1; j++)
         {
            //If a flag is found then make flag true then break from the loop
            if (brackStr[j] == '-' && (brackStr[j+1] == 'e' || brackStr[j+1] == 'f' 
                || brackStr[j+1] == 'd') && j < brackStr.size() - 1)
            {
               flag = true;
               break;
            }
            //If a bracket is located and hasn't been located before then make it true and
            //keep the postion.
            if (brackStr[j] == '[' && !bracket)
            {
               bracket = true;
               posBrack = j;  
            }
               
         }

         //If bracket does exists and it doesn't have a flag then insert the default -e
         if (bracket && !flag)
         {
            brackStr.insert(posBrack+1, " -e"); //inserts the -e into the string
            int length = brackStr.copy(tmp, brackStr.size()); //copies new string into array
            tmp[length] = '\0'; //end array with a null char
         }
      }
      
      //Function that returns the value of worked
      bool getWorked()
      {
         return worked;
      }
      
      //Function that takes in an array of chars and determines if a file/directory exists
      void execute(char** argv)
      {
         
         struct stat sb; //Creates the stat struct that holds types of files

         if (argv[0] == '\0') //If the char array is empty then print an error
         {
            worked = false;
            fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
         }

         if (stat(argv[1], &sb) == -1) //If the second argument didn't work then make worked false
         {
            worked = false;
            perror("stat");
         }
         else
         {
            //If the flag -f is entered then check if the file/directory is a file
            if (strcmp(argv[0], "-f") == 0)
            {                         
               if(S_ISREG(sb.st_mode)) //If it's a file then make worked true
                  worked = true;
               else
                  worked = false;      //If not a file then make it false
            }
            else if(strcmp(argv[0], "-d") == 0)  //If the flag entered is -d then check if file/directory is a directory
            {
               if(S_ISDIR(sb.st_mode)) //If it's a directory then make worked true
                  worked = true;
               else
                  worked = false;      //If not a directory then make worked false
            }
            else if(strcmp(argv[0], "-e") == 0) //If no flag was specified or the -e flag was entered then check if
            {
               if(S_ISREG(sb.st_mode)) //Check if it's a file
                  worked = true;
               else if(S_ISDIR(sb.st_mode)) //Check if it'a a directory
                  worked = true;
               else
                  worked = false;      //If it's not a file or directory then make worked false
            }
            else
            {
               worked = false;  //If none of those conditions are met then make worked false
            }
         }
      }
};



#endif
