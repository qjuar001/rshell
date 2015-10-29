#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

using namespace std;

void  parse(char *line, char **argv)
{
     while (*line != '\0') {       /* if not the end of line ....... */ 
          while (*line == ' ' || *line == '\t' || *line == '\n')
               *line++ = '\0';     /* replace white spaces with 0    */
          *argv++ = line;          /* save the argument position     */
          while (*line != '\0' && *line != ' ' && 
                 *line != '\t' && *line != '\n') 
               line++;             /* skip the argument until ...    */
     }
     *argv = '\0';                 /* mark the end of argument list  */
}

void  execute(char **argv, bool &cmdWorked)
{
     pid_t  pid;
     int    status;

     if ((pid = fork()) < 0) {     /* fork a child process           */
          printf("*** ERROR: forking child process failed\n");
          exit(1);
     }
     else if (pid == 0) {          /* for the child process:         */
          if (execvp(*argv, argv) < 0) {     /* execute the command  */
               cmdWorked = false;    //If cmd failed, set variable to false
               printf("*** ERROR: exec failed\n");
               exit(1);
          }
          else
             cmdWorked = true;       //If cmd succeeded, set variable to true
     }
     else {                                  /* for the parent:      */
          while (wait(&status) != pid)       /* wait for completion  */
               ;
     }
}

int  main()
{
  char *cmds;
  char  line[1024];             // the input line
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

    string cmd = "";                  // string that holds command line
    bool cmdWorked = true;
//Print out the command line
    while (cmd == "")
    {
      cout << '[';
      printf(name, hostname);
      cout << ']';
      cout << "$ ";

//Read in the command line
      getline(cin, cmd);
    }

//Convert command into a c string then store into array
    strncpy(line, cmd.c_str(), sizeof(line));
    line[sizeof(line) - 1] = 0;
    printf("\n");
     
    int arrLength = cmd.length();         //Variabel to hold length of string
    //Variable to keep track of placement in the command line
    int check = 0;
    bool cmdDone = false;                 //Bool to determine when to stop
    bool commandchain = true;
    //While loop that seperates commands and executes them
    while (!cmdDone)
    {
      char  *argv[64] = {0};              // the command line argument  
      char tmp[1024] = {0};               // Temp array to hold a command
      int restart = 0;                    // Restarts temp array from beginning
      string op = "";			  // Variable to keep track of operation
      //A loop that moves a single command into the temp array
      while(line[check] != ';' && line[check] != '|' && 
            line[check] != '&' && line[check] != '\0')
      {
         //Check to see if the last character in cmd is a space, if so
         //then break out of loop
         if(line[check] == ' ' && (line[check + 1] == '|' ||
            line[check + 1] == '&' || line[check + 1] == '\0') && restart != 0)
            break;
         tmp[restart] = line[check];      //Transfer command from line to tmp
         check++;
         restart++;                       //Move through tmp array
      }
      
      //Three checks to see if there is a OR or AND operator 
      if (line[check] == '|' && line[check + 1] == '|')
      {
         check+=2;
         op = "||";
      }
      else if (line[check] == '&' && line[check + 1] == '&')
      {
         check+=2;
         op = "&&";
      }
      else 
        check++;      
      
      tmp[sizeof(tmp) - 1] = 0;           //Makes sure tmp ends with NULL
      parse(tmp, argv);                   //Call parse function on tmp

      if (argv[0] == '\0')                //If array is empty then do nothing
      {}
      else if (strcmp(argv[0], "exit") == 0)   //Sees if exit was entered
         exit(0);            /*   exit if it is                */

      //Checks if the command should be run based on previous operator and cmd
      if (commandchain == true)
         execute(argv, cmdWorked);
      
      //A variety of checks to see if the next command should be executed
      //based on the operator that is passed in
      if (op == "||" && cmdWorked == false)
         commandchain = true;
      else if (op == "||" && cmdWorked == true)
         commandchain = false;
      else if (op == "&&" && cmdWorked == true)
         commandchain = true;
      else if (op == "&&" && cmdWorked == false)
         commandchain = false;
      else
         commandchain = true;
      
      //Checks to see if all commands have been taken care of
      if (arrLength <= check)
        cmdDone = true;  
    }
  }  

  return 0;
}
