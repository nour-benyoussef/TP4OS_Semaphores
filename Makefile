CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -L. -lsem

client: client.o random_utils.o
	$(CC) $(CFLAGS) -o client client.o random_utils.o $(LDFLAGS)

client.o: client.c segdef.h random_utils.h
	$(CC) $(CFLAGS) -c client.c

random_utils.o: random_utils.c random_utils.h
	$(CC) $(CFLAGS) -c random_utils.c

libsem.a: semaphore.o

semaphore.o: semaphore.c
	$(CC) $(CFLAGS) -c semaphore.c

clean:
	rm -f *.o client libsem.a

