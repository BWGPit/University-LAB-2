#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
FILE *pari;
FILE *dispari;

int main(int argc, char *argv[]) {
    // Con array:
    int pariArray[argc-1];
    int indicePari = 0;
    int dispariArray[argc-1];
    int indiceDispari = 0;
    if(argc>1) {    // Si honta da 1 perché l'argomento 0 è sé stesso
        for(int i=1; i<argc; i++) { // Sto scorrendo tutto l'array in input
            int questo = strtol(argv[i], NULL, 10);
            
            if(questo%2==0) {
                pari = fopen("pari.txt", "a+");
                fprintf(pari, "\n%d", questo);
                fclose(pari);
                pariArray[indicePari] = questo;
                indicePari++;
            } else {
                dispari = fopen("dispari.txt", "a+");
                fprintf(dispari, "\n%d", questo);
                fclose(dispari);
                dispariArray[indiceDispari] = questo;
                indiceDispari++;
            }
        }
    }
    
    int sommaPari = 0, sommaDispari = 0;
    for(int i=0;i<indicePari;i++) {sommaPari += pariArray[i];}
    for(int i=0;i<indiceDispari;i++) {sommaDispari += dispariArray[i];}
    printf("%d\n%d", sommaPari, sommaDispari);

    return 0;
}