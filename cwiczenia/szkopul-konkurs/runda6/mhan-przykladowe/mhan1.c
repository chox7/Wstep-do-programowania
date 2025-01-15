#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int *S[3];   // tablica wskaźników
int pocz[3]; // tablica początków

// #define DEBUG true

#ifdef DEBUG
#define DEBUG_PRINT(...) do{ fflush(stdout); fprintf( stderr, __VA_ARGS__ ); } while(0)
#else
#define DEBUG_PRINT(...) do{ if(0) fprintf( stderr, __VA_ARGS__ ); } while(0)
#endif
// do ... while żeby to na pewno była instrukcja
// to w else jest po to, żeby kompilator zawsze sprawdził zawartość,
// nawet przy wyłączonym DEBUG
// Na podstawie https://stackoverflow.com/questions/1644868/define-macro-for-debug-printing-in-c

void __DEBUG_SLUPKI(int n, int z, int na){
  fflush(stdout);
  if (n==0) return;
  int ileN = (pocz[0] + pocz[1] + pocz[2]) / 2;
  for(int i=0; i<3; i++){
    fprintf(stderr, " [%d]", ileN-pocz[i]);
    for(int j = ileN-1; j >= pocz[i]; j--)
      fprintf(stderr, "%3d", S[i][j]);
    if (i == z) fprintf(stderr, "  --> %d\n", n);
    else if (i == na) fprintf(stderr, "  <-- %d\n", n);
    else fprintf(stderr, "\n");
  }
}

#ifdef DEBUG
#define DEBUG_SLUPKI(n,z,na) __DEBUG_SLUPKI(n,z,na)
#else
#define DEBUG_SLUPKI(n,z,na)
#endif

// krążki zajmują miejsca od pocz (najmniejszy) do N-1 (największy)
// przenosimy n - są w tablicy od pocz do pocz+n-1
void mhan(int n, int z, int na, int pom){
  DEBUG_PRINT(" %d --%d--> %d\n", z+1, n, na+1); 
  if (n == 0) { return; }
  DEBUG_SLUPKI(n, z, na);
  int * zTab;
  zTab = S[z];
  int zPocz = pocz[z];

  // szukamy ile jednakowych krążków jest na dole n-tki
  int ileInnych = n-2;
  while (ileInnych >= 0 && zTab[zPocz+ileInnych] == zTab[zPocz+n-1]) {
    ileInnych--;
  }
  // aktualnie ileInnych to numer ostatiego krążka innej wielkości
  ileInnych++; // ale numery liczymy od 0
  int ileTakich = n - ileInnych;

  DEBUG_PRINT(" ileInnych = %d, ileTakich = %d\n", ileInnych, ileTakich);
  
  mhan(ileInnych, z, pom, na); 

  DEBUG_PRINT(" %d ==[%d]==> %d\n", z+1, ileTakich, na+1); 
  DEBUG_SLUPKI(ileTakich, z, na);
  for(int i = 1; i <= ileTakich; i++) {
    int krazek = S[z][pocz[z]++];
    S[na][--pocz[na]] = krazek;
    printf("%d %d %d\n", z+1, na+1, krazek);
  }

  mhan(ileInnych, pom, na, z); 
}
  
int main(){
  int N;
  scanf("%d", &N);

  int A[N]; // zakładamy taką tablicę jak potrzeba
  for(int i = 1; i <= N; i++) scanf("%d", &A[N-i]);
  S[0] = A; // ustawiamy wskaźnik nr 0 na tablicę A
            // to nie jest kopiowanie tablicy !!
  pocz[0] = 0;

  // pozostałe dwie "puste"
  int B[N];  S[1] = B;  pocz[1] = N;
  
  int C[N];  S[2] = C;  pocz[2] = N;

  mhan(N, 0, 2, 1);

  DEBUG_SLUPKI(N,-1,-1);
  
  return 0;
}
