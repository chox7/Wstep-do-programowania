#include<stdio.h>
#include<stdlib.h>
#include "lnad.h"

Tlista *mkNode(int x, Tlista *n){
  Tlista* pom = malloc(sizeof(Tlista));
  pom->val = x;
  pom->next = n;
  return pom;
}
  
void nadlista(int n, int A[n], int B[n], Tlista** lista_ptr){
  int ai=0;
  int bi=0;

  Tlista *atrapa = mkNode(-1,NULL);
  Tlista *ost = atrapa;

  while (ai < n && bi < n) {
    // na liście od atrapa->next do ost włącznie są wszystkie elementy z
    // A[0..ai-1] oraz B[0..bi-1]
    // bierzemy mniejszy z pozostałych części dwóch tablic
    if (A[ai] < B[bi]){
      ost->next = mkNode(A[ai], NULL);
      ai++;
      ost = ost->next;
    } else if (A[ai] > B[bi]) {
      ost->next = mkNode(B[bi], NULL);
      bi++;
      ost = ost->next;
    } else { // A[ai] == B[ai]
      // lub wspólny
      ost->next = mkNode(A[ai], NULL);
      ai++;
      bi++;
      ost = ost->next;
    }
  }

  // co najmniej jedna tablica się skończyła (ai == n || bi == n)
  // jeśli jakaś część którejś tablicy jeszcze została, to trzeba ją dołączyć
  
  while (ai < n) {
    ost->next = mkNode(A[ai], NULL);
    ai++;
    ost = ost->next;
  } 
  
  while (bi < n) {
    ost->next = mkNode(B[bi], NULL);
    bi++;
    ost = ost->next;
  }

  *lista_ptr = atrapa->next;
  free(atrapa);
}




