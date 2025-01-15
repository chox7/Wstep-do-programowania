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

// wszystkie procedury przyjmują wskaźnik na węzeł _przed_ kursorem
// jeśli coś zwracają, to wskaźnik na węzeł _przed_ nową pozycją kursora

// usuwanie
void del(Tlista *prev){     
  Tlista *pom = prev->next;   //prev -> pom -> nast
  prev->next = pom->next;     //prev  ------>  nast
  free(pom);                  //     [*]pom[*]    
  // poprzednik kursora bez zmian
}

// przesuwanie następnego elementu o k w prawo 
Tlista *move(Tlista *prev, int k){
  if (k==0) return prev->next;
  Tlista *el = prev->next;    //prev -> el -> nast_1 -> ... -> nast_k -> nx
  prev->next = el->next;      //prev  ----->  nast_1 -> ... -> nast_k -> nx
                              //        el ->...
  Tlista *pom = prev;
  for(int i=0; i<k; i++){
    pom = pom->next;
  }                //prev -> nast_1 -> ... -> pom==nast_k -> nx
                                                //        el ->...
  el->next = pom->next;
  pom->next = el;  //prev -> nast_1 -> ... -> pom==nast_k -> el -> nx

  return el;
}


// odwrócenie fragmentu listy dł k
Tlista *rev(Tlista *prev, int k){
  if (k==0) return prev;
  if (k==1) return prev->next;

  //prev -> el_1 -> ... -> el_k -> nx

  Tlista *l = prev->next;
  Tlista *r = l->next;   // "zapominamy" na co wskazuje el_1->next
  //prev -> [ ?<- el_1]==l  r==el_2 -> el_3 ... -> el_k -> nx
  
  for(int i=1; i<k; i++){
    //prev -> [ ?<- el_1] <- ... <- el_i ==l     r== el_i+1 -> el_i+2... -> el_k -> nx
    Tlista *pom = r->next;
    r->next = l;
    //prev -> [ ?<- el_1] <- ... <- el_i <- el_i+1 ==r   pom== el_i+2... -> el_k -> nx
    l = r;
    r = pom;
    //prev -> [ ?<- el_1] <- ... <- el_i <- el_i+1 ==l     r== el_i+2... -> el_k -> nx
  }

  //prev -> [ ?<- el_1] <- ... <- el_k ==l    r== nx
  Tlista *el_1 = prev->next;
  el_1->next = r;
  // l== el_k -> el_k-1 -> ... el_1 -> nx==r
  //                      prev -> ?
  prev->next = l;
  // prev -> l==el_k -> el_k-1 -> ... el_1 -> nx==r
  return el_1;
}

  
void przetworz(char* program, Tlista** lista_ptr){

  // atrapa wskazuje na węzeł _przed_ pierwszym węzłem listy
  Tlista *atr = mkNode(-1, *lista_ptr);
  // prCur wskazuje na węzeł _przed_ kursorem
  Tlista *prCur = atr;

  printList(stderr, atr->next, prCur->next);
  
  for(int i = 0; program[i] != 0; i += 2){
    int k = program[i+1] - '0';
    fprintf(stderr, "%c%d\n", program[i], k);
    switch (program[i]) {
    case 'I': //insert
      // wstawianie elementu k
      prCur->next = mkNode(k, prCur->next);
      prCur=prCur->next;
      break;

    case 'D': //delete
      // usuwanie k elementów
      for(int j = 0; j < k; j++)
        del(prCur);
      break;

    case 'F': //forward
      // przesuwanie kursora o k elementów
      for(int j = 0; j < k; j++)
        prCur = prCur->next;
      break;

    case 'R': //reverse
      // odwracanie k elementów
      prCur = rev(prCur, k);
      break;

    case 'M': //move
      // przesuwanie elementu o k w prawo
      prCur = move(prCur, k);
      break;
      
    case 'H': //home
      // ustawianie kursora na k-tym elemencie od początku
      prCur = atr;
      for(int j = 0; j < k; j++)
        prCur = prCur->next;
      break;
    }
    printList(stderr, atr->next, prCur->next);
  }
  
  *lista_ptr = atr->next; // ustawianie wskaźnika do pierwszego elementu
  free(atr); // usuwanie atrapy
}
