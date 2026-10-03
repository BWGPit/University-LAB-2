#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

void exception(char *msg);

int main(int argc, char *argv[])
{
    if(argc==1)
    {
        exception("Fornire almeno un argomento");
    }

    // Calcolo della lunghezza totale
    int lun = 0;
    for(int i=1;i<argc;i++)
    {
        lun += strlen(argv[i]);
    }

    // Allocazione del blocco di lun+1 byte
    char *unito = malloc(lun+1);

    // Copia dei singoli caratteri
    int c = 0;
    for(int i=1;i<argc;i++)
    {
        for(int j=0;j<strlen(argv[i]);j++)
        {
            unito[c] = argv[i][j];
            c++;
        }
    }

    // Stampa e deallocazione
    printf("%s\n", unito);
    free(unito);

    return 0;
}

void exception(char *msg)
{
    perror(msg);
    exit(1);
}