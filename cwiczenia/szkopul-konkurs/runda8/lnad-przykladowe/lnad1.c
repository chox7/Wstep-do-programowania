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
  int ai=n-1;
  int bi=n-1;

  Tlista *ogon = NULL;

  // działamy od końca
  
  while (ai >= 0 || bi >= 0) {
    // w liście ost->...->NULL są wszystkie elementy
    // z A[ai+1..n-1] oraz B[bi+1..n-1]

    // bierzemy większą z końcówek obu tablic
    // tablica niepusta (i>=0) "wygrywa" z pustą (i<0)
    if (ai < 0 || (bi >= 0 && A[ai] < B[bi])){
      ogon = mkNode(B[bi--], ogon);
    } else if (bi < 0 || (/* ai >= 0 && */ A[ai] > B[bi])) {
      ogon = mkNode(A[ai--], ogon);
    } else { // ai >= 0 && bi >= 0 && A[ai] == B[ai]
      // lub wspólny
      ogon = mkNode(A[ai--], ogon);
      bi--;
    }
  }

  *lista_ptr = ogon;
}
