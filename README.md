# Rshell
### By: Queston Juarez & Mark Spencer

## What does this program do?
###### This program implements a shell terminal that is run with the `execvp` command. The program is desgined to handle any single command with any flags or expressions as well as multiple commands that are linked with the ';', '||', and '&&' operators. The program also has a decently functioning comment symbol '#'. The program can now check if any file/directory exists using test or [] with the flags -f, -d, or -e. Additionally, the program can also handle precedence by surrounding a set of commands in paranthesis. For example you can now run `[ -f test ] && (echo yay && echo Woohoo) || (echo boo && echo not a file)`

## Known Error's
1. The program can only execute files that are in the system bin files. For instance, `cd` will not work in this mock terminal.
2. None of the operators can be put inside of a command like such: `mkdir te||st`
3. Also, the character '|' and '&' by themselves are treated like ';'
4. The `echo` commmand cannot print out any of the operators or the word 'exit' or the comment symbol '#'.
5. The comment symbol '#' does not work as the very first character on the command line. It also causes unnesessary errors when put in the middle of a command. For example, `cp test1.cpp test#2.cpp` will produce a fatal error. The comment symbol also doesn't work when put right at the end of a command like this `ls# -a`.
6. The exit function exits no matter where it is in the command, here is an example of a command; `ls && echo hello || exit` even though the exit should be skipped it still exits the program.
7. Now that test and [] are implemented you can no longer use the word test or use the [] for anything else because that word and symbols think you are trying to test if something exists no matter what.
8. The [] operators do not return errors if there is an uneven amount of them, for instance `[[ src ]` would still run accordingly even though it does not have proper syntax.
9. The precedence operator produces a segmentation fault when the `(` operator is unevenly matched with the`)` operator. Also, the command `()` will produce a segmentation fault. For example, `(( echo hello )` would produce a seg fault but `( echo hello ))` does not which is still not good because it has bad syntax.
10. The precedence operators cannot be used in file names, echoes, etc.

## Design
###### The design of this project implements a strategy pattern as well as a basic  Composite pattern by implementing a common inheritance tree as well as encapsulating basic algorithms for the && and || operators in a seperate object so that other classes can call upon them. On the other hand, to improve this program we couldseperate the parse function into more algorithm classes instead of holding most of the logic inside of the parse function. Overall the program itself is still a little crowded and should be seperated to allow more diversability.

###### This concludes the program! There are probably more errors than specified above but these are all the ones that we have found so far.
