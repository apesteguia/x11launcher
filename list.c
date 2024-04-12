#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
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
*/

void initStringList(StringList *s) {
    s->n = 0;
    s->end = NULL;
    s->start = NULL;
}

void clearStringList(StringList *s) {
    while (!isEmpty(s)) {
        deleteFront(s);
    }
}

void push(StringList *s, const char *str, size_t size) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (!n) {
        fprintf(stderr, "Error: No se pudo asignar memoria para el nodo.\n");
        exit(EXIT_FAILURE);
    }

    n->text = (char *)malloc((size + 1) * sizeof(char));
    if (!n->text) {
        fprintf(stderr, "Error: No se pudo asignar memoria para el texto.\n");
        free(n);
        exit(EXIT_FAILURE);
    }

    snprintf(n->text, size + 1, "%s", str);
    n->next = NULL;
    n->prev = NULL;

    if (isEmpty(s)) {
        s->start = n;
        s->end = n;
    } else {
        Node *current = s->start;
        Node *prev = NULL;

        while (current && strcmp(n->text, current->text) > 0) {
            prev = current;
            current = current->next;
        }

        if (!prev) {
            n->next = s->start;
            s->start->prev = n;
            s->start = n;
        } else {
            prev->next = n;
            n->prev = prev;
            if (!current) {
                s->end = n;
            } else {
                n->next = current;
                current->prev = n;
            }
        }
    }

    s->n++;
}

void deleteFront(StringList *s) {
    if (isEmpty(s))
        return;

    Node *aux = s->start;
    s->start = s->start->next;
    if (s->start)
        s->start->prev = NULL;
    else
        s->end = NULL;

    free(aux->text);
    free(aux);
    s->n--;
}

void deleteBack(StringList *s) {
    if (isEmpty(s))
        return;

    Node *aux = s->end;
    s->end = s->end->prev;
    if (s->end)
        s->end->next = NULL;
    else
        s->start = NULL;

    free(aux->text);
    free(aux);
    s->n--;
}

char *front(StringList *s) {
    if (isEmpty(s))
        return NULL;
    return s->start->text;
}

char *back(StringList *s) {
    if (isEmpty(s))
        return NULL;
    return s->end->text;
}

bool isEmpty(StringList *s) { return (s->start == NULL && s->end == NULL); }

void mostrarLista(StringList s) {
    Node *aux = s.start;
    while (aux != NULL) {
        printf("%s\n", aux->text);
        aux = aux->next;
    }
}

StringList obtenerPrimerosNconPrefijo(StringList *s, int n,
                                      const char *prefijo) {
    StringList result;
    initStringList(&result);

    if (n <= 0 || isEmpty(s) || prefijo == NULL || strlen(prefijo) == 0) {
        return result;
    }

    Node *current = s->start;
    int count = 0;

    while (current && count < n) {
        if (strncmp(current->text, prefijo, strlen(prefijo)) == 0) {
            push(&result, current->text, strlen(current->text));
            count++;
        }
        current = current->next;
    }

    return result;
}

StringList obtenerPrimerosN(StringList *s, int n) {
    StringList result;
    initStringList(&result);

    if (n <= 0 || isEmpty(s)) {
        return result;
    }

    Node *current = s->start;
    int count = 0;

    while (current && count < n) {
        push(&result, current->text, strlen(current->text));
        current = current->next;
        count++;
    }

    return result;
}
