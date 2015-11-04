#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
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

void  execute(char **argv)
{
     pid_t  pid;
     int    status;

     if ((pid = fork()) < 0) {     /* fork a child process           */
          printf("*** ERROR: forking child process failed\n");
          exit(1);
     }
     else if (pid == 0) {          /* for the child process:         */
          if (execvp(*argv, argv) < 0) {     /* execute the command  */
               printf("*** ERROR: exec failed\n");
               exit(1);
          }
     }
     else {                                  /* for the parent:      */
          while (wait(&status) != pid)       /* wait for completion  */
               ;
     }
}

int  main()
{

  char  line[1024];             // the input line
  char  *argv[64];              // the command line argument      
  char *parse;
  char *name;                   // char string to hold login name
  char hostname[1024];          // char array to hold hostname
  int host;                     // variable to deterimine if successful
  string cmd;                   // string that holds command line

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

//Print out the command line
    cout << '[';
    printf(name, hostname);
    cout << ']';
    cout << "$ ";

//Read in the command line
    getline(cin, cmd);

//Convert command into a c string then store into array
    strncpy(line, cmd.c_str(), sizeof(line));
    line[sizeof(line) - 1] = 0;
    printf("\n");

//Parse the string into sperate commands
    parse = strtok (line,";|&");
    int i = 0;
    while (parse != NULL)
    {
       printf ("%s\n", parse);
       parse = strtok (NULL, ";|&");
       argv[i] = parse;
       i++;
       execute(argv);
    }
    *argv = '\0';
    char *s = parse;

//Test to see if input is exit
   // if (strcmp(argv[0], "exit") == 0)
   //   exit(0);            /*   exit if it is                */
   // execute(argv);           /* otherwise, execute the command */
  }

  return 0;
}
