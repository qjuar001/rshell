# Rshell (a mock shell terminal)
### By: Queston Juarez & Mark Spencer

## What does this program do?
###### This program implements a shell terminal that is run with the '<execvp>' command. The program is desgined to handle any single command with any flags or expressions as well as multiple commands that are linked with the ';', '||', and '&&' operators. The program also has a decently functioning comment symbol '#'.

## Known Error's
1. The program can only execute files that are in the system bin files. For instance, '<cd>' will not work in this mock terminal.
2. None of the operators can be put inside of a command like such: '<mkdir te||st>'
3. Also, the character '|' and '&' by themselves are treated like ';'
4. The '<echo>' commmand cannot print out any of the operators or the word 'exit' or the comment symbol '#'.
5. The comment symbol '#' does not work as the very first character on the command line. It also causes unnesessary errors when put in the middle of a command. For example, '<cp test1.cpp test#2.cpp>' will produce a fatal error. The comment symbol also doesn't work when put right at the end of a command like this '<ls# -a>'.
6. The exit function exits no matter where it is in the command, here is an example of a command; '<ls && echo hello || exit>' even though the exit should be skipped it still exits the program.

###### This concludes the program! There are probably more errors than specified above but these are all the ones that we have found so far.
