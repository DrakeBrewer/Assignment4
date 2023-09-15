#
# Makefile for Chapter 09
#
# Type  make    to compile all the programs
# in the chapter 
#

all: smsh4

clean:
	rm -f smsh4


smsh4: smsh4.c splitline.c execute2.c process2.c controlflow.c builtin.c varlib.c queue.c
	gcc -o -w -Wall smsh4.c splitline.c execute2.c process2.c controlflow.c builtin.c varlib.c queue.c