#makefile that compiles command shell

all: main.cpp commands.o 
	g++ -W -Wall -Werror -ansi -pedantic main.cpp commands.o
	mkdir bin; mv a.out bin
rshell: main.cpp commands.o
	g++ -W -Wall -Werror -ansi -pedantic main.cpp commands.o
	mkdir bin; mv a.out bin
cmds: commands.cpp
	g++ -c -W -Wall -Werror -ansi -pedantic commands.cpp

