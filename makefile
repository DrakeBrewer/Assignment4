#
# Makefile for Chapter 09
#
# Type  make    to compile all the programs
# in the chapter 
#

all: envchange showenv smsh4

clean:
	rm -f envchange showenv smsh4


changeenv: envchange.c
	gcc -o envchange envchange.c

showenv: showenv.c
	gcc -o showenv showenv.c

smsh4: smsh4.c splitline.c execute2.c process2.c controlflow.c \
		builtin.c varlib.c queue.c
	gcc -o smsh4 smsh4.c splitline.c execute2.c process2.c controlflow.c \
		builtin.c varlib.c queue.c

