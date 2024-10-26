#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <errno.h>
#include "segdef.h"
#include "random_utils.h"

void initialize(int *semid, int *shmid, segment **segptr) {
    
    if ((*semid = semget(cle, 3, 0666)) == -1) {
        perror("Error retrieving semid");
        exit(1);
    }
    
    if ((*shmid = shmget(cle, segsize, 0666)) == -1) {
        perror("Error retrieving shmid");
        exit(1);
    }
    
    if ((*segptr = (segment *)shmat(*shmid, NULL, 0)) == (void *)-1) {
        perror("Error attaching the segment");
        exit(1);
    }

 
    init_rand();
}

int main() {
    int semid, shmid;
    segment *segptr;
    int req_count = 10;

    initialize(&semid, &shmid, &segptr);


    for (int i = 0; i < req_count; i++) {

        acq_sem(semid, seg_dispo);

        
        segptr->pid = getpid();
        segptr->req = i + 1;
        long sum = 0;

        
        for (int j = 0; j < maxval; j++) {
            segptr->tab[j] = getrand();
            sum += segptr->tab[j];
        }
        long local_avg = sum / maxval;

        
        acq_sem(semid, seg_init);

      
        wait_sem(semid, res_ok);

        
        if (segptr->result == local_avg) {
            printf("Request %d: success, correct average (%ld)\n", segptr->req, segptr->result);
        } else {
            printf("Request %d: failure, incorrect average (%ld instead of %ld)\n", segptr->req, segptr->result, local_avg);
        }

     
        lib_sem(semid, seg_init);
        lib_sem(semid, seg_dispo);
    }

  
    if (shmdt(segptr) == -1) {
        perror("Error detaching the segment");
        exit(1);
    }

    return 0;
}
