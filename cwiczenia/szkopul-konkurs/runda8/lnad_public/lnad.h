#ifndef _lnad_h
#define _lnad_h

struct lista {
  int val;
  struct lista *next;
};

typedef struct lista Tlista;

void nadlista(int n, int A[n], int B[n], Tlista** lista_ptr);

#endif
