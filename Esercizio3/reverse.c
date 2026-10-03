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

    for(int i=1;i<argc;i++)
    {
        char *toprint = strdup(argv[i]);
        int k = 0;
        for(int j=strlen(argv[i])-1;j>=0;j--)
        {
            toprint[j] = argv[i][k];
            k++;
        }
        printf("%s\n", toprint);
        free(toprint);
    }

    return 0;
}

void exception(char *msg)
{
    perror(msg);
    exit(1);
}