#include <iostream>
#include <vector>
#include <unistd.h>
#include <stdio.h>
#include <string>

using namespace std;

int main(int argc, char * argv[])
{

  char *name;
  char hostname[1024];
  int host;
  bool exit = false;

//Get the users login name and checks for an error
  name = getlogin();
  if (name == '\0')
    perror("getlogin() error");
 
//Get the users hostname and checks for an error
  hostname[1023] = '\0';
  host = gethostname(hostname, 1023);
  if (host == -1)
    perror("gethotname() error");

  while (!exit)
  {
    string cmd;
    vector<string> parse_cmd;
    
    //Prints the user and hostname and gets input and assigns it to cmd
    cout << '[';
    printf(name, hostname);
    cout << ']';
    cout << "$ ";
    getline(cin, cmd); 
    
    //IF user types exit it will end the program
    if (cmd == "exit")
      exit = true;

  }

  return 0;
}

