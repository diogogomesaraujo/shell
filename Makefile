CC = gcc
CFLAGS = -Wall -pthread -g

OBJS = main.o parse.o calc.o execute.o redirects.o socp.o threads.o isspeg.o sos.o setx.o

soshell: $(OBJS)
	$(CC) $(CFLAGS) -o soshell $(OBJS)

main.o: main.c shell.h
	$(CC) $(CFLAGS) -c main.c

parse.o: parse.c shell.h
	$(CC) $(CFLAGS) -c parse.c

calc.o: calc.c shell.h
	$(CC) $(CFLAGS) -c calc.c

execute.o: execute.c shell.h
	$(CC) $(CFLAGS) -c execute.c

redirects.o: redirects.c shell.h
	$(CC) $(CFLAGS) -c redirects.c

socp.o: socp.c shell.h
	$(CC) $(CFLAGS) -c socp.c

threads.o: threads.c shell.h
	$(CC) $(CFLAGS) -c threads.c

isspeg.o: isspeg.c shell.h
	$(CC) $(CFLAGS) -c isspeg.c

sos.o: sos.c shell.h
	$(CC) $(CFLAGS) -c sos.c

setx.o: setx.c shell.h
	$(CC) $(CFLAGS) -c setx.c

clean:
	rm -f *.o soshell
