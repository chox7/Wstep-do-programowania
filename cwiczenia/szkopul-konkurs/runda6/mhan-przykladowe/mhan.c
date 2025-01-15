#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define Nmax 50
int S[3][Nmax];  // trzy słupki - miejsce na maksymalną możliwą liczbę krążków
int ile[3] = {0};

void mhan(int n, int z, int na, int pom){
  // Przenosi n krążków ze słupka "z" na słupek "na" używając "pom"
  // Zakładamy, że zarowno na "na" jak i na "pom" są krążki większe,
  // niż nasze n (lub puste)
  
  // Krążki na słupku a są reprezentowane w tablicy S[a] pod indeksami
  // od 0 (największy) do ile[a]-1 (najmniejszy)

  // Czyli przenosimy krążki od ile[z]-1 do ile[z]-n z tablicy S[z]
  
  if (n == 0) return;

  // |-------ile[z]-----|
  // ZZDDDDddddddmmmxxxxx  <- wierzchołek słupka "z"
  //       |-----n------|
  // PPP
  // NNNN
  
  // ustalamy liczbę jednakowych krążków na dole n przenoszonych
  // krążków na słupku "z"
  int in = n-1;
  while (in > 0 && S[z][ile[z]-in] == S[z][ile[z]-n]) {
    in--;
  }
  int ts = n - in;

  // na wierzchołku słupka jest "in" innych krążków
  // oraz "ts" takich samych
  // ZZDDDDddddddmmmxxxxx  <- wierzchołek słupka "z"
  //       |-ts-||--in--|
  
  
  // przenosimy rekurencyjnie inne krążki na słupek pomocniczy
  // założenia spełnione
  mhan(in, z, pom, na); 

  // ZZDDDDdddddd      <- wierzchołek słupka "z"
  //       |-ts-|
  // PPPmmmxxxxx
  // NNNN
  
  // przenosimy "ts" takich samych krążków z dołu n-tki ze słupka "z" na "na"
  // krążki na "na" są większe, że nasze
  for(int i = 1; i <= ts; i++) {
    int krazek = S[z][ile[z]-1];
    S[na][ile[na]] = krazek;
    ile[na]++;
    ile[z]--;
    printf("%d %d %d\n", z+1, na+1, krazek);
  }
  // ZZDDDD           <- wierzchołek słupka "z"
  // PPPmmmxxxxx
  // NNNNdddddd

  // przenosimy rekurencyjnie inne krążki ze słupka pomocniczego na "na"
  // założenia spełnione
  mhan(in, pom, na, z); 
  // ZZDDDD           <- wierzchołek słupka "z"
  // PPP
  // NNNNddddddmmmxxxxx
}
  
int main(){
  int N;
  scanf("%d", &N);

  // wewnętrznie używamy numerów słupków 0..2, wypisujemy 1..3
  ile[0] = N;
  for(int i = 0; i < N; i++) scanf("%d", &S[0][i]);

  mhan(N, 0, 2, 1);
  
  return 0;
}
