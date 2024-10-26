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


## Client.c "multiple client"
This program was modified to enable the simultaneous execution of multiple clients, with each client making requests and sharing a memory segment with the server through semaphores. The key changes and adjustments made to achieve this functionality are as follows:

### Function client_function(int client_id)
   * The client_function was introduced to manage each client's requests within separate processes.
   * The function receives a client_id argument, which helps in tracking individual clients and allows for more efficient management when displaying debugging messages.

### Creating Client Processes in main
   * In main, a loop is set up to create multiple client processes. The number of clients is defined by the num_clients variable, set here to 100.
   * Each call to fork() creates a separate client process. If the process is a child (pid == 0), it executes client_function and then exits with exit(0).
   * The parent process waits for each client to finish using wait(NULL), preventing any zombie processes.

### Synchronization Control with Semaphores
   * Semaphores are used to ensure coordinated access to the shared memory.
   * Each client uses acq_sem and lib_sem calls to acquire and release semaphores, thus protecting the critical section where each client reads and writes to the shared memory.
   * The server responds with res_ok to signal that a request has been processed, allowing the client to validate the result and release the resources.





