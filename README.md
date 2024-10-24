# TP 4 Semaphores
## Makefile Explanation
The Makefile is used to automate the compilation of the client program. It consists of the following parts:
### Variables:
* CC = gcc: Defines the compiler to be used (in this case, gcc).
* CFLAGS = -Wall -g: Enables warnings (-Wall) and includes debugging information (-g).
* LDFLAGS = -L. -lseg: Specifies where to find the libraries (-L.) and links with the libseg.a library (-lseg).
### Compilation Rules:
* client: client.o: Generates the client executable from client.o.
* client.o: client.c segdef.h: Compiles client.c into an object file client.o, including segdef.h for declarations.
### Cleaning:
* clean:: Removes object files (*.o) and the executable (client) to prepare for a recompilation.
