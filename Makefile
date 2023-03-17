CC = gcc
CFLAGS = -g -Wall

default: shell

shell: main.o ls.o pwd.o cat.o
	$(CC) $(CFLAGS) -o shell main.o ls.o pwd.o cat.o -lm

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

ls.o: ls.c
	$(CC) $(CFLAGS) -c ls.c

pwd.o: pwd.c
	$(CC) $(CFLAGS) -c pwd.c

cat.o: cat.c 
	$(CC) $(CFLAGS) -c cat.c

clean:
	rm -f shell *.o
