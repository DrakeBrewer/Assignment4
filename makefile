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
	gcc -o -w -Wall envchange envchange.c

showenv: showenv.c
	gcc -o -w -Wall showenv showenv.c

smsh4: smsh4.c splitline.c execute2.c process2.c controlflow.c \
		builtin.c varlib.c queue.c
	gcc -o -w -Wall smsh4 smsh4.c splitline.c execute2.c process2.c controlflow.c \
		builtin.c varlib.c queue.c

