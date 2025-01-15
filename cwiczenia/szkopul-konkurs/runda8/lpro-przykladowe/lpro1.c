#include<stdio.h>
#include<stdlib.h>
#include "lpro.h"

void printList(FILE* f, Tlista *l, Tlista *kursor);

Tlista *mkNode(int k, Tlista *l){
  Tlista *pom = malloc(sizeof(Tlista));
  pom->val = k;
  pom->next = l;
  return pom;
}

// Operujemy na typie Tlista ** czyli miejscu na wpisanie adresu listy
// cur to miejsce, w którym wpisany jest adres bieżącego elementu,
// czyli albo oryginalna zmienna, albo "pole next" poprzedniego węzła

void del(Tlista **l_ptr){     
  // czytamy adres węzła do skasowania
  Tlista *pom = *l_ptr;
  // w miejscu do wpisania adresu wpisujemy adres kolejnego węzła (lub NULL)
  *l_ptr = pom->next;
  // usuwamy
  free(pom);
}

// przestawienie kursora o k elementów w prawo
Tlista **next(Tlista **cur, int k){
  for(int i=1; i<=k; i++) {
    cur = &((*cur)->next);  // adres "pola next" węzła, którego adres jest w cur
    // cur = [n0]    n0: {val=... | next=n1}
    //         nowe cur to to miejsce z [n1]   :)
  }
  return cur;
}  

// przestawienie elementu o k w prawo
Tlista **move(Tlista **el_ptr, int k){
  if (k==0) return next(el_ptr, 1);
  Tlista *el = *el_ptr;    //*el_ptr == el -> nast_1 -> ... -> nast_k -> nx
  *el_ptr = el->next;      //      *el_ptr == nast_1 -> ... -> nast_k -> nx
                           //           el ->...
  Tlista **pom = el_ptr;
  pom = next(pom, k);
                          // *el_ptr == nast_1 -> ... -> nast_k -> nx
                                                 //   pom==&(nast_k->next)
                                                          //    el ->...
  el->next = (*pom);
  (*pom) = el;
                          // *el_ptr == nast_1 -> ... -> nast_k -> el -> nx

  return &(el->next);
}


// odwrócenie fragmentu listy dł k
Tlista **rev(Tlista **el1_ptr, int k){
  if (k==0) return el1_ptr;
  if (k==1) return &((*el1_ptr)->next);
  //*el1_ptr == el_1 -> ... -> el_k -> nx

  Tlista *l = *el1_ptr;
  Tlista *r = l->next;   // "zapominamy" na co wskazuje el_1->next
  // *el1_ptr == [ ?<- el_1]==l  r==el_2 -> el_3 ... -> el_k -> nx
  
  for(int i=1; i<k; i++){
    //*el1_ptr == [ ?<- el_1] <- ... <- el_i==l  r==el_i+1 -> el_i+2... -> el_k -> nx
    Tlista *pom = r->next;
    r->next = l;
    //*el1_ptr == [ ?<- el_1] <- ... <- el_i==l <- r==el_i+1  pom==el_i+2... -> el_k -> nx
    l = r;
    r = pom;
    //*el1_ptr == [ ?<- el_1] <- ... <- el_i <- el_i+1 ==l  r==el_i+2... -> el_k -> nx
  }
  //*el1_ptr == [ ?<- el_1] <- ... <- el_k==l  r==nx
  Tlista *el_1 = *el1_ptr;
  el_1->next = r;
  // l==el_k -> el_k-1 -> ... el_1 -> nx==r
  //              *el1_ptr == el_1
  *el1_ptr = l;
  // prev -> l==el_k -> el_k-1 -> ... el_1 -> nx==r
  return &(el_1->next);
}

  
void przetworz(char* program, Tlista** lista_ptr){

  Tlista **cur = lista_ptr;

  printList(stderr, *lista_ptr, *cur);
  
  for(int i = 0; program[i] != 0; i += 2){
    int k = program[i+1] - '0';
    fprintf(stderr, "%c%d\n", program[i], k);
    switch (program[i]) {
    case 'I':
      // wstawianie elementu k
      *cur = mkNode(k, *cur);
      cur = next(cur, 1);
      break;

    case 'D':
      // usuwanie k elementów
      for(int j = 0; j < k; j++)
        del(cur);
      break;

    case 'F': // forward
      // przesuwanie kursora o k elementów
      cur = next(cur, k);
      break;

    case 'R':
      // odwracanie k elementów
      cur = rev(cur, k);
      break;

    case 'M':
      // przesuwanie elementu o k w prawo
      cur = move(cur, k);
      break;
      
    case 'H': // home
      // ustawianie kursora na k-tym elemencie od początku
      cur = next(lista_ptr, k);
      break;
    }
    printList(stderr, *lista_ptr, *cur);
  }
}
