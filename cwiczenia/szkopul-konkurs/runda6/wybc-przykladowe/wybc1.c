#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* wersja:
- bez globalnych zmiennych (w tym tablic maksymalnej dopuszczalnej wielkości)
- z tablicą booli zamiast "listy" wybranych liczb
- z malutką optymalizacją - pamiętamy indeks ostatniej liczby nieparzystej
  i nie przeszukujemy ciągów, jeśli nie ma szans dostać nieparzystej sumy
  (w praktyce to zmienia dużo wyłącznie dla ciągów samych liczb parzystych,
  dla pozostałych niewiele, bo puste przeszukiwanie działa dużo szybciej od
  wypisywania...)
*/

//#define DEBUG true

#ifdef DEBUG
int debug_ile = 0;
#endif

// wiedząc, że wybrany podciąg z A[0..i-1] jest zaznaczony w W[0..i-1]
// składa się z ile elementów i sumuje się do suma
// wypisz wszystkie dobre podciągi, będące przedłużeniami
// podciągu zaznaczonego w W[0..i-1] o wybrane liczby z A[i..N-1]
void wypisz(int N, int A[N], int ostniep, bool W[N], int i, int ile, int suma){
#ifdef DEBUG
  debug_ile++;
#endif
  // ostniep to indeks ostatniej liczby nieparzystej
  if (suma % 2 == 0 && i > ostniep) {
    // nie ma już szans na nieparzystą sumę
    return;
  }
  if (i == N){ // liczby w A się skończyły
    if (ile % 2 == 0 && suma % 2 == 1) {
      // jeśli wzięliśmy dobry podciąg, wypisujemy zaznaczone elementy
      for(int j=0; j<N; j++) {
        if (W[j]) printf("%d ",A[j]);
      }
      printf("\n");
    }
  } else {

    // ponieważ ciąg jest malejący, leksykograficznie większy będzie
    // podciąg, zawierający jak najwcześniejsze liczby

    // dlatego najpierw próbujemy podciągi z A[i]
    W[i] = true;
    wypisz(N, A, ostniep, W, i+1, ile+1, suma+A[i]);

    // a potem bez A[i]
    W[i] = false;
    wypisz(N, A, ostniep, W, i+1, ile, suma);
  }    
}
  
int main(){
  int N;
  scanf("%d", &N);
  int A[N];
  int ostniep = -1;
  for(int i = 0; i < N; i++) {
    scanf("%d", &A[i]);
    if (A[i]%2 == 1) ostniep = i;
  }
  
  bool W[N];
  
  wypisz(N, A, ostniep, W, 0, 0, 0);

#ifdef DEBUG
  fprintf(stderr, " %d zamiast %d\n", debug_ile, (1<<(N+1)) - 1);
  // bez optymalizacji (ostniep) liczba wywołań funkcji wypisz to:
  // wypisz(...i=0...) - 1 szt
  //     wypisz(...i=1...) - 2 szt
  //         wypisz(...i=2...) - 4 szt
  //             itd.
  //                   wypisz(...i=N-1...) - 2^N szt
  // RAZEM:
  // 1 + 2 + 4 + ... + 2^N   =   2^(N+1) - 1
#endif

  return 0;
}
