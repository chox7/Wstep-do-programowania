#include <stdio.h>
#include <stdlib.h>

// oblicza pierwszy indeks elementu niezerowego lub N 
int pierwsza_cyfra(int N, int C[N]){
  int i = 0;
  while (i < N && C[i] == 0) i++;
  return i;
}


int main(){
  int N;
  scanf("%d", &N);

  int A[N];
  int B[N];
  // wczytujemy od końca, ale w sumie to bez znaczenia
  for(int i = N-1; i >= 0; i--) scanf("%d", &A[i]);
  for(int i = N-1; i >= 0; i--) scanf("%d", &B[i]);

  int ap = pierwsza_cyfra(N, A);
  int bp = pierwsza_cyfra(N, B);

  // od pierwszego niezerowego do końca musi być to samo
  while (ap < N && bp < N && A[ap] == B[bp]){
    ap++;
    bp++;
  }

  // jak znaleźliśmy różnicę przed końcem - to źle
  if (ap < N && bp < N) {
    printf("0\n");
  } else {
    // w tym jednym, który < N do końca muszą być same zera
    while (ap < N && A[ap] == 0) {
      ap++;
    }
    while (bp < N && B[bp] == 0) {
      bp++;
    }
    // jak nie są to źle
    if (ap < N || bp < N) {
      printf("0\n");
    } else {
      printf("1\n");
    }
  }
  return 0;
}
