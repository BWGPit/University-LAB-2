#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa/numero exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni di confronto/copia/etc di stringhe
#include <errno.h>    // necessaria per usare errno

void termina(const char *msg);

// COPPIA

typedef struct
{
    int x;
    int y;
} coppia;

coppia *coppia_crea(int x, int y) {
    coppia *c = malloc(sizeof(*c));
    if (c==NULL) termina("Malloc fallita");
    c->x = x;
    c->y = y;
    return c;
}

void coppia_distruggi(coppia *c) {
    free(c);
}

void coppia_stampa(const coppia *c, FILE *f) {
    fprintf(f, "(%d, %d)", c->x, c->y);
}

// ARRAY DI PUNTATORI A COPPIE

coppia **arraydicoppie(const int dimensione) {
    coppia **a = malloc(dimensione*sizeof(coppia *));
    if(a==NULL) termina("Malloc fallita");
    return a;
}

void distruggiarraydicoppie(coppia **a, const int dimensione) {
    for (int i = 0; i < dimensione; i++) {
        coppia_distruggi(a[i]);
    }
    free(a);
}

void merge(coppia **a, int na, coppia **c, int nc, coppia **b) {
    int i = 0;
    int j = 0;
    int k = 0;

    while (i < na && j < nc) {
        if (a[i]->x - a[i]->y < c[j]->x - c[j]->y) {
            b[k] = a[i];
            i++;
        } else {
            b[k] = c[j];
            j++;
        }
        k++;
    }

    while (i < na) {
        b[k] = a[i];
        i++;
        k++;
    }
    while (j < nc) {
        b[k] = c[j];
        j++;
        k++;
    }
}

void mergesort(coppia **a, int n) {
    if (n==1) return;
    int n1 = n/2;
    int n2 = n - n1;

    mergesort(a, n1);
    mergesort(&a[n1], n2);

    coppia **b = malloc(n*sizeof(coppia *));
    if (b==NULL) termina("Malloc fallita nel merge");
    merge(a, n1, &a[n1], n2, b);
    for (int i = 0; i < n; i++) {a[i] = b[i];}
    free(b);
}

void stampa_array(coppia **a, int n) {
    for(int i = 0; i < n; i++) {
        coppia_stampa(a[i], stdout);
        printf(", ");
    }
}

int main(int argc, char *argv[]) {
    if(argc%2 == 0 || argc == 1) {
        termina("Inserire coppie, non valori singoli\n");
    }

    int dimensione = ((argc-1)/2); // So che è un intero dal controllo precedente
    int messi = 0;
    coppia **a = arraydicoppie(dimensione);
    for (int i = 0; i < dimensione; i++) {
        int indicex = atoi(argv[(i+1)*2-1]);
        int indicey = atoi(argv[(i+1)*2]);
        coppia *c = coppia_crea(indicex, indicey);
        a[i] = c;
        printf("\n");
        messi++;
    }
    assert(messi==dimensione);

    mergesort(a, messi);
    stampa_array(a, messi);

    distruggiarraydicoppie(a, messi);
}

void termina(const char *msg) {
    perror(msg);
    exit(1);
}