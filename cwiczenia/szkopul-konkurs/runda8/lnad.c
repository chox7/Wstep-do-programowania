#include<stdlib.h>
#include<stdio.h>
#include "lnad.h"

Tlista* create_node(int x) {
    Tlista* pom = malloc(sizeof(Tlista));
    pom->val = x;
    pom->next = NULL;
    return pom;
}

void nadlista(int N, int A[N], int B[N], Tlista **lista_ptr) {
    int a = 0;
    int b = 0;

    Tlista* atrapa = malloc(sizeof(Tlista));
    Tlista* koniec = atrapa; 

    while (a < N && b < N) {
        if (A[a] == B[b]) {
            koniec->next = create_node(A[a]);
            a++;
            b++;
        } else if (A[a] < B[b]) {
            koniec->next = create_node(A[a]);
            a++;
        } else {
            koniec->next = create_node(B[b]);
            b++;
        }
        koniec = koniec->next;
    }

    while (a < N) {
        koniec->next = create_node(A[a]);
        a++;
        koniec = koniec->next;
    }

    while (b < N) {
        koniec->next = create_node(B[b]);
        b++;
        koniec = koniec->next;
    }

    *lista_ptr = atrapa->next;
    free(atrapa);
}