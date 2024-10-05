#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXNUMBER 256
#define MAXCHARACTER 256

typedef struct {
    int numbers[MAXNUMBER];
    int topo;
} PilhaNumero;

typedef struct {
    char characters[MAXCHARACTER];
    int topo;
} PilhaChar;

typedef struct {
    char *strings[50];
    int topo;
} PilhaString;

void pushNumber(PilhaNumero *pilha, int number) 
{
    if (pilha->topo == MAXNUMBER) 
    {
        printf("STACK OVERFLOW\n");
    } else 
    {
        pilha->numbers[pilha->topo++] = number;
    }
}

int popNumber(PilhaNumero *pilha) 
{
    if (pilha->topo >= 0) 
    {
        return pilha->numbers[--pilha->topo];
    } else 
    {
        printf("Pilha de numeros vazia!\n");
        return '\0';
    }
}

void pushChar(PilhaChar *pilha, char value) 
{
    if (pilha->topo == MAXCHARACTER) 
    {
        printf("STACK OVERFLOW\n");
    } else 
    {
        pilha->characters[pilha->topo++] = value;
    }
}

char popChar(PilhaChar *pilha) 
{
    if (pilha->topo >= 0) 
    {
        return pilha->characters[--pilha->topo];
    } else 
    {
        printf("Pilha de caracteres vazia!\n");
        return '\0';
    }
}

void pushString(PilhaString *pilha, char *str) 
{
    if (pilha->topo < 49) 
    {
        pilha->strings[++pilha->topo] = (char *)malloc(strlen(str) + 1);
        strcpy(pilha->strings[pilha->topo], str);
    } else 
    {
        printf("Pilha cheia! Não é possível empilhar mais strings.\n");
    }
}

char *popString(PilhaString *pilha) 
{
    if (pilha->topo >= 0) 
    {
        return pilha->strings[pilha->topo--];
    } else 
    {
        printf("Pilha vazia! Não é possível desempilhar.\n");
        return NULL;
    }
}