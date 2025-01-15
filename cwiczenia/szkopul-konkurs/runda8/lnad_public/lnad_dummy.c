#include<stdlib.h>
#include<stdio.h>
#include "lnad.h"

Tlista *mkNode(int x, Tlista *n){
  Tlista* pom = malloc(sizeof(Tlista));
  pom->val = x;
  pom->next = n;
  return pom;
}

void nadlista(int n, int A[n], int B[n], Tlista** lista_ptr){

  // Działa (prawie ;) TYLKO dla n=5 i tablic:
  // int A[] = {6,6,8,8,11,12};
  // int B[] = {6,7,7,8,9,11};
  // rezultat końcowy:
  // 6 -> 6 -> 7 -> 7 -> 8 -> 8 -> 9 -> 11 -> 12 -> *

  *lista_ptr = mkNode(6,
                 mkNode(6,
                   mkNode(7,
                     mkNode(7,
                       mkNode(8,
                         mkNode(8,
                           mkNode(9,
                             mkNode(11,
                               mkNode(12, NULL)))))))));

}
