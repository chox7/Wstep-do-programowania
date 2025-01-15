#include<stdio.h>
#include<stdlib.h>
#include "lpro.h"

Tlista* mkNode(int val, Tlista* next) {
    Tlista* pom = malloc(sizof(Tlista));
    pom->val = n;
    pom->next = next;
    return pom;
}

void delNone(Tlista* prev) {
    Tlista* pom = prev->next;
    prev->next = pom->next;
    free(pom);
}

Tlista* reverse(Tlista* prev, int n) {
    if (n == 0) {
        return prev;
    }
    if (n == 1) {
        return prev->next
    }

    Tlista *l = prev->next;
    Tlista *r = l->next;

    for (int i = 1; i < n; i++) {
        Tlist* pom = r->next;
        r->next = l;
        l = r;
        r = pom;
    }
    Tlista* pom = prev->next;
    prev->next = l;
    pom->next = r; 
    return pom;

}

void przetworz(char* program, Tlista** lista_ptr) {
    Tlista* atrapa = mkNode(-1, *lista_ptr);
    Tlista* poprzedni = atrapa;
    // kursor - to na co wskazuje poprzedni->next
    for (int i = 0; program[i] != 0; i++0) {
        int k = program[i+1] - '0';
        switch (program[i]) {
            case 'I':
                poprzedni->next = mkNode(k, poprzedni->next);
                poprzedni = poprzedni->next;
            
            case 'D':
                for (int j = 0; j < k; j++) {
                    delNone(poprzedni);
                }
            
            case 'F':
                for (int j = 0; j < k; j++) {
                    poprzedni = poprzedni->next;
                }
            
            case 'R':
                poprzedni = reverse(poprzedni, k);

            case 'M':
        }
    }
}