#include <stdio.h>
#include <stdlib.h>

#define Nmax 30
int N;
int A[Nmax];

int T[Nmax];
int ileT=0;

// wiedząc, że wybrany podciąg z A[0..i-1] znajduje się w T[0..ileT-1]
// i sumuje się do suma
// wypisz wszystkie dobre podciągi, będące przedłużeniami T[0..ileT-1]
// o wybrane liczby z A[i..N-1]
void wypisz(int i, int suma){
  if (i == N){ // liczby w A się skończyły
    if (ileT % 2 == 0 && suma % 2 == 1) {
      // jeśli wzięliśmy dobry podciąg, wypisujemy
      for(int j=0; j<ileT; j++)
        printf("%d ",T[j]);
      printf("\n");
    }
  } else {

    // ponieważ ciąg jest malejący, leksykograficznie większy będzie
    // podciąg, zawierający jak najwcześniejsze liczby

    // dlatego najpierw próbujemy podciągi zawierające A[i]
    T[ileT++] = A[i];
    wypisz(i+1, suma+A[i]);
    ileT--;

    // a potem niezawierające A[i]
    wypisz(i+1, suma);
  }    
}
  
int main(){
  scanf("%d", &N);
  for(int i = 0; i < N; i++) scanf("%d", &A[i]);

  wypisz(0, 0);

  return 0;
}
