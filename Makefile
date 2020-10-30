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
