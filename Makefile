CFLAGS = -Wall -g

all: search

search: sorted-list.o parse.o hashadd.o main.o
	gcc $(CFLAGS) sorted-list.o parse.o hashadd.o main.o -o search

main.o: main.c
	gcc $(CFLAGS) -c main.c -o main.o

sorted-list.o: sorted-list.c
	gcc $(CFLAGS) -c sorted-list.c -o sorted-list.o

parse.o: parse.c
	gcc $(CFLAGS) -c parse.c -o parse.o

hashadd.o: hashadd.c
	gcc $(CFLAGS) -c hashadd.c -o hashadd.o

clean:
	rm -f search
	rm -f *.o
