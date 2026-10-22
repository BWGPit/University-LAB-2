#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa/numero exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni di confronto/copia/etc di stringhe

int *somme_distinte(int a[], int n, int *size);
bool find(int x, int a[], int n);
void stampa_array(int a[], int n);
void errore(char *msg);

int main(int argc, char *argv[]) {
    int s;
    if (argc <= 1) {
        errore("Inserire almeno un argomento\n");
    }
    int *a = malloc((argc-1)*sizeof(int));
    int messi_in_a = 0;

    for (int i = 1; i < argc; i++) {
        a[messi_in_a] = atoi(argv[i]);
        messi_in_a++;
    }

    int *b = somme_distinte(a, messi_in_a, &s);
    stampa_array(b, s);

    int somma = 0;
    for (int i = 0; i < s; i++) {
        somma += b[i];
    }
    fprintf(stdout, "%d\n", somma);
    free(a);
    free(b);
    return 0;
}

int *somme_distinte(int a[], int n, int *size) {
    int *b = malloc(n * sizeof(int));
    int maxsize = n;
    int messi = 0;
    if (b==NULL) {errore("Malloc fallita");}
    
    for(int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int valore = a[i] + a[j];
            // Se valore NON è già presente, lo inserisce in b e incrementa size
            if (!find(valore, b, messi)) {
                if (messi == maxsize) {
                    maxsize = (messi)*2;
                    b = realloc(b, maxsize*sizeof(int));
                    if (b==NULL) {errore("Realloc fallita");}
                }
                b[messi] = valore;
                messi++;
            }
        }
    }

    *size = messi;
    return b;
}

bool find(int x, int a[], int n) {
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (a[i] == x) {
            found = true;
        }
    }
    return found;
}

void stampa_array(int a[], int n) {
    for(int i = 0; i < n; i++) {
        fprintf(stderr, "%d, ", a[i]);
    }
}

void errore(char *msg) {
    perror(msg);
    exit(1);
}