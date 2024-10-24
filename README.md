# TP 4 Semaphores
## Makefile Explanation
The Makefile is used to automate the compilation of the client program. It consists of the following parts:
1. Variables:
* CC = gcc: Defines the compiler to be used (in this case, gcc).
* CFLAGS = -Wall -g: Enables warnings (-Wall) and includes debugging information (-g).
* LDFLAGS = -L. -lseg: Specifies where to find the libraries (-L.) and links with the libseg.a library (-lseg).
2. Compilation Rules:
* client: client.o: Generates the client executable from client.o.
* client.o: client.c segdef.h: Compiles client.c into an object file client.o, including segdef.h for declarations.
3. Cleaning:
* clean:: Removes object files (*.o) and the executable (client) to prepare for a recompilation.



## Client.c "One client"
The client program communicates with a server using shared memory and semaphores. It sends requests, generates arrays of random values, calculates a local average, and compares the result with the one returned by the server.
### General Structure of the Program
1. Initialization:
   
  * The initialize() function retrieves the IDs for the shared memory segment and semaphores.
  * It uses semget() to access the set of semaphores (here, 3 semaphores) and shmget() to access the shared memory segment.
  * The segment is then attached to the client process with shmat(), which returns a pointer to the shared segment. This segment is a structure defined in the segdef.h header file.
  * init_rand() initializes the random number generator, which will be used to create random values that the client sends to the server.

2. Request Loop: The client makes a specified number of requests (here, 10) inside a loop. For each request:

  * Acquire seg_dispo Semaphore: The client acquires this semaphore to ensure safe access to the shared memory segment, preventing other processes from using it simultaneously.
  * Initialize Shared Segment: The client fills the shared memory segment with its PID, the request number, and an array of random values. It also calculates the sum of the array and determines the local average (local_avg).
  * Acquire seg_init Semaphore: The client acquires this semaphore to signal to the server that the segment has been initialized and the data is ready to be processed.
  * Wait for the Result: The client uses wait_sem() to wait for the server to finish processing and release the res_ok semaphore, indicating that the result is ready in the shared memory.
  * Compare Results: The client compares its local average with the one calculated by the server. If they match, it prints a success message; otherwise, it prints an error message with the incorrect values.
  * Release Semaphores: The client releases the seg_init and seg_dispo semaphores to allow other processes to access the shared memory segment.

3. Detach the Segment:
  * After completing all the requests, the shared memory segment is detached from the client process using shmdt(). This frees the resources associated with accessing the shared memory.
