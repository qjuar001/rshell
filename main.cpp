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
#include <sstream>

using namespace std;

void exec( char **ptrArr );
void parse( char * arr, char ** ptArr );

int main(int argc, char * argv[])
{

  char input_cmd[1024];
  char * args[64];
  char *name;
  char hostname[1024];
  int host;
  bool exit = false;
  string cmd;

//Get the users login name and checks for an error
  name = getlogin();
  if (name == '\0')
    perror("getlogin() error");
 
//Get the users hostname and checks for an error
  hostname[1023] = '\0';
  host = gethostname(hostname, 1023);
  if (host == -1)
    perror("gethostname() error");

  while (!exit)
  {
    
    //Prints the user and hostname and gets input and assigns it to cmd
    cout << '[';
    printf(name, hostname);
    cout << ']';
    cout << "$ ";
    getline(cin, cmd); 
    strncpy(input_cmd, cmd.c_str(), sizeof(input_cmd)); 
    input_cmd[sizeof(input_cmd) - 1] = 0;
    printf("\n");
    parse( input_cmd, args);
    
    //IF user types exit it will end the program
    if (cmd == "exit")
      exit = true;
    
    exec(args);
  }
  
  return 0;
}

void parse( char *arr, char** ptArr )
{
  while ( *arr != '\0' )
  {
    while( *arr == ' ' || *arr == '\t' || *arr == '\n')
      *arr++ = '\0';
    *ptArr++ = arr;
    while( *arr == ' ' && *arr == '\t' && *arr == '\n')
      *arr++;   
  }
  *ptArr = '\0';
}

void exec( char** ptrArr )
{
  pid_t c_pid, pid;
  int status;

  c_pid = fork();
  
  if( c_pid < 0)
  {
    perror("fork failed");
    exit(1);
  }

  else if (c_pid == 0)
  {
    printf("Child: executing ls\n");
    execvp(*ptrArr, ptrArr);
    perror("execve failed");
  }

  else if (c_pid > 0)
  {
    if( (pid = wait(&status)) < 0)
    {
      perror("wait");
      exit(1);
    }
    printf("Parent: finished\n");
  }
}
