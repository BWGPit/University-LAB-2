#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa/numero exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni di confronto/copia/etc di stringhe
#include <errno.h>    // necessaria per usare errno

void termina(const char *msg);

int main(int argc, char *argv[]) {
    if (argc <= 2) termina("Inserire almeno il nome del file e un intero\n");
    FILE *f = fopen(argv[1], "rt");
    if (f==NULL) termina("Errore nell'apertura del file\n");

    int size = 2;
    int messi = 0;
    int *a = malloc(size*sizeof(int));
    if (a==NULL) termina("Malloc fallita");

    while (true) {
        int n;
        int e = fscanf(f, "%d", &n);
        if (e==EOF) break;
        if (size == messi) {
            size *= 2;
            a = realloc(a, size*sizeof(int));
            if (a==NULL) termina("Realloc fallita");
        }
        a[messi] = n;
        messi++;
    }

    for (int i = 2; i < argc; i++) {
        int N = atoi(argv[i]);
        // NOME DEL FILE: MANIPOLAZIONE DI STRINGHE
        char *nome;
        int e = asprintf(&nome, "%s.%d", argv[1], N);

        FILE *g = fopen(nome, "wt+");
        if (g==NULL) termina("Errore in apertura di file nuovo");

        for (int j = 0; j < messi; j++) {
            if (a[j] % N == 0) {
                fprintf(g, "%d\n", a[j]);
            }
        }

        free(nome);
        fclose(g);
    }

    fclose(f);
    free(a);
    return 0;
}

void termina(const char *msg) {
    perror(msg);
    exit(1);
}