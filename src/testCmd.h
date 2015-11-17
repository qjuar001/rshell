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
 
      bool getWorked()
      {
         return worked;
      }

      void execute(char** argv)
      {
         struct stat sb;

         if (argv[0] == '\0')
         {
            worked = false;
            fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
         }
         if (stat(argv[1], &sb) == -1)
         {
            worked = false;
            perror("stat");
         }
         else
         {
            if(strcmp(argv[0], "-f") == 0)
            {
               if(S_ISREG(sb.st_mode))
                  worked = true;
               else
                  worked = false;
            }
            else if(strcmp(argv[0], "-d"))
            {
               if(S_ISDIR(sb.st_mode))
                  worked = true;
               else
                  worked = false;
            }
            else if(strcmp(argv[0], "-e"))
            {
               if(S_ISREG(sb.st_mode))
                  worked = true;
               else if(S_ISDIR(sb.st_mode))
                  worked = true;
               else
                  worked = false;
            }
            else
            {
               worked = false;
            }
         }
      }
};



#endif
