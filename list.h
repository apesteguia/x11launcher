#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct Node {
    char *text;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct StringList {
    Node *start;
    Node *end;
    unsigned int n;
} StringList;

void initStringList(StringList *);
void clearStringList(StringList *);
void push(StringList *, const char *, size_t);
char *front(StringList *);
char *back(StringList *);
void deleteFront(StringList *);
bool isEmpty(StringList *);
void mostrarLista(StringList);
StringList obtenerPrimerosNconPrefijo(StringList *, int, const char *);
StringList obtenerPrimerosN(StringList *, int);

#endif // LIST_H
