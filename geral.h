#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAM 256

void lerString(char vet[TAM]){
    int i;
    fflush(stdin);
    scanf("%c", &vet[0]);
    for(i=1; vet[i-1]!='\n'; i++){
        scanf("%c", &vet[i]);
    }
    vet[i-1]='\0';
}

void imprimeString(char vet[TAM]){
    int i;
    for(i=0; vet[i]!='\0'; i++){
        printf("%c", vet[i]);
    }
}
