CC=gcc
CFLAGS=-I.
DEPS = hellomake.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
run1:20050111074.c hellofunc.c
	gcc -o out1 20050111074.c hellofunc.c -I.

run2:20050111074.c hellofunc.c
	$(CC) -o out2 20050111074.c hellofunc.c $(CFLAGS)



run3: 20050111074.o hellofunc.o 
	$(CC) -o out3 20050111074.o hellofunc.o 