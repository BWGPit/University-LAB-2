#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa/numero exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni di confronto/copia/etc di stringhe

void exception(char *msg){
    perror(msg);
    exit(1);
}

void stampaArray(int **arr, int length){
    printf("[");
    for(int i=0;i<length;i++){
        printf("%d, ", (*arr)[i]);
    }
    printf("]\n");
}

int somma(int arr[], int size){
    int s = 0;
    for(int i=0;i<size;i++){
        s = s + arr[i];
    }
    return s;
}

void push(int **arr, int element, int *size, int *cap){
    if(*cap==*size){
        *cap =* cap*2;
        *arr = realloc(*arr,*cap*sizeof(int));
        if(*arr==NULL){
            exception("Realloc fallita");
        }
    }
    int pos = *size;
    (*arr)[pos] = element;    // Per accedere all'array, si usa (*arr)[pos] e non *arr[pos]
    *size = *size + 1;
}

int main(int argc, char *argv[]){
    if(argc!=2){
        exception("Devi fornire esattamente un argomento");
    }
    int n = atoi(argv[1]);
    if(n<0){
        exception("L'argomento deve essere positivo");
    }

    int *a, *b;
    int capA = 5, capB = 5;
    int sizeA = 0, sizeB = 0;
    a = malloc(capA*sizeof(int));
    b = malloc(capB*sizeof(int));

    if(a==NULL||b==NULL){
        exception("Allocazione di memoria fallita");
    }

    for(int i=1;i<=n;i++){
        if(i%3==0&&i%5!=0){
            push(&a, i, &sizeA, &capA);
        }
        if(i%5==0&&i%3!=0){
            push(&b, i, &sizeB, &capB);
        }
    }

    printf("lunghezza a[] = %d, somma a[] = %d\n", sizeA, somma(a, sizeA));
    printf("lunghezza b[] = %d, somma b[] = %d\n", sizeB, somma(b, sizeB));

    free(a);
    free(b);
    return 0;
}