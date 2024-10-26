// random_utils.c
#include <stdlib.h>
#include <time.h>

void init_rand() {
    srand(time(NULL)); // Initialisation de la graine de nombres aléatoires
}

long getrand() {  // Changer ici pour correspondre à la déclaration
    return rand() % 100; // Retourne un nombre aléatoire entre 0 et 99
}

