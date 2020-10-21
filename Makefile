# ifndef CC
# 	CC=gcc
# endif
# CFLAGS=-std=c99 -Werror -Wall -Wpedantic -Wextra
# SRCS=bdsm.c
# OBJS=$(subst .c,.o,$(SRCS))
# RM=rm -f
#
# all: bdsm
#
# #foo: main.o
# #	$(CC) $(CFLAGS) -o main main.c
#
# clean:
# 	$(RM) $(OBJS) bdsm

CC = g++
CFLAGS = -Wall -g

main: main.o State.o
	$(CC) $(CFLAGS) -o main main.o State.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

State.o: State.cpp
	$(CC) $(CFLAGS) -c State.cpp

clean:
	rm -f core *.o
