#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void wait_sem(int semid, int sem) {
    struct sembuf sop;
    sop.sem_num = sem;
    sop.sem_op = -1; // Décrémente le sémaphore
    sop.sem_flg = 0; // Pas d'options

    if (semop(semid, &sop, 1) == -1) {
        perror("Error waiting on semaphore");
        exit(1);
    }
}

void acq_sem(int semid, int sem) {
    struct sembuf sop;
    sop.sem_num = sem;
    sop.sem_op = 0; // Tente de tester le sémaphore
    sop.sem_flg = IPC_NOWAIT; // Ne bloque pas si le sémaphore n'est pas disponible

    if (semop(semid, &sop, 1) == -1) {
        if (errno == EAGAIN) {
            wait_sem(semid, sem); // Si le sémaphore est occupé, attendre
        } else {
            perror("Error acquiring semaphore");
            exit(1);
        }
    }
}

void lib_sem(int semid, int sem) {
    struct sembuf sop;
    sop.sem_num = sem;
    sop.sem_op = 1; // Incrémente le sémaphore
    sop.sem_flg = 0; // Pas d'options

    if (semop(semid, &sop, 1) == -1) {
        perror("Error releasing semaphore");
        exit(1);
    }
}

