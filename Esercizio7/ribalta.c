#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa/numero exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni di confronto/copia/etc di stringhe
#include <errno.h>    // necessaria per usare errno

void termina(const char *msg);

int main(int argc, char *argv[]) {
    // Controllo gli argomenti
    if (argc != 3) {
        termina("Fornire esattamente due argomenti\n");
    }

    // Lettura del file
    FILE *infile = fopen(argv[1], "rt");
    if (infile==NULL) {
        termina("Impossibile aprire il file 1");
    }
    FILE *outfile = fopen(argv[2], "wt");
    if (outfile==NULL) {
        termina("Impossibile aprire il file 2");
    }

    int capacita = 10;
    char **trovati = malloc(capacita*sizeof(char *));
    if (trovati==NULL) termina("Malloc fallita\n");
    int messi = 0;

    while(true)
    {
        char *questo;
        int e = fscanf(infile, "%ms", &questo); // fscanf separa tanto gli \n quanto gli spazi
        if (e==EOF) break;
        // fprintf(stdout, "%s\n", questo);

        if (messi == capacita) {
            capacita *= 2;
            trovati = realloc(trovati, capacita*sizeof(char *));
            if (trovati==NULL) termina("Realloc fallita\n");
        }
        trovati[messi] = questo;
        messi++;
        fprintf(stdout, "%s\n", questo);
    }

    trovati = realloc(trovati, messi*sizeof(char *)); // scarto le celle vuote
    if (trovati==NULL) termina("Realloc fallita\n");

    for(int i = messi-1; i >= 0; i--) {
        fprintf(outfile, "%s\n", trovati[i]);
    }

    // Devo liberare prima tutte le stringhe di trovati e poi trovati stesso
    for (int i = 0; i < messi; i++) {
        free(trovati[i]);
    }
    free(trovati);
    int ci = fclose(infile);
    int co = fclose(outfile);
    return 0;
}

void termina(const char *msg) {
    perror(msg);
    exit(1);
}