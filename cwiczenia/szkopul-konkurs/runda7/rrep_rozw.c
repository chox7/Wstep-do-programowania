#include <stdio.h>
#include <stdlib.h>

// oblicza pierwszy indeks elementu niezerowego lub N 
int pierwsza_cyfra(int N, int C[N]){
  int i = 0;
  while (i < N && C[i] == 0) i++;
  return i;
}

// sprawdza czy ac + roznica == bc
// różnica to liczba z zakresu -1000..1000, więc nie ma sensu używać do tego
// tablicy bitów.
int sprawdz_roznice_cech(int C, int Ac[C], int Bc[C], int roznica){
  int* skladnik;
  int* suma;
  if (roznica < 0) {
    skladnik = Bc;
    suma = Ac;
    roznica = -roznica;
  } else {
    skladnik = Ac;
    suma = Bc;
  }
  // sprawdzamy czy skladnik + roznica = suma, roznica >= 0

  int ok = 1;
  
  int p = 0;    // przeniesienie
  for(int i=0; i<C && ok; i++){
    // dodajemy skladnik[i] do i-tego bitu różnicy
    // i sprawdzamy czy równy suma[i], uwzględniamy przeniesienie p
    int bitr;   // to będzie i-ty bit z różnicy
    if (roznica != 0) {
      bitr = ((roznica & 1<<i) != 0);
      // <<  to przesunięcie bitowe w lewo (w stronę bardziej znaczących bitów)
      // 1 << i  to 2^i (i-ty bit zapalony, reszta nie)
      // &  to AND bitowy
      // roznica & 1<<i == 1<<i  o ile i-ty bit różnicy to 1, wpp 0
      roznica -= (roznica & 1<<i);
      // gasimy i-ty bit różnicy, po jakimś czasie już wszystkie są 0
    } else {
      // w szczególności jak i będzie większe niż liczba bitów w różnicy
      // to już na pewno różnica == 0
      bitr = 0; 
    }
    int s = skladnik[i] + p + bitr;
    p = (s / 2);
    if (suma[i] != s%2) { ok = 0; }
  }
  return ok;
}


int main(){
  int C, M;
  scanf("%d%d", &C, &M);

  // Cecha:
  // c[i] to i-ty bit, warty 2^i (Z wyjątkiem bitu znaku C-1)
  int Ac[C];
  // Mantysa:
  // m[i] to bit warty 2^(-i) (z wyjątkiem m[0], który powinien być ==0)
  // np. 0 1 0 1 --> 0*1/1 + 1*1/2 + 0*1/4 + 1*1/8 = 5/8
  int Am[M];

  int Bc[C];
  int Bm[M];

  // wczytujemy cechę od końca, mantysę od początku 
  for(int i = C-1; i >= 0; i--) scanf("%d", &Ac[i]);
  for(int i = 0; i < M; i++) scanf("%d", &Am[i]);

  for(int i = C-1; i >= 0; i--) scanf("%d", &Bc[i]);
  for(int i = 0; i < M; i++) scanf("%d", &Bm[i]);

  int wynik = 1;
  
  int ap = pierwsza_cyfra(M, Am);
  int bp = pierwsza_cyfra(M, Bm);

  // różnica w pozycjach
  int bam = bp - ap;

  // od pierwszego niezerowego do końca musi być to samo
  while (ap < M && bp < M && Am[ap] == Bm[bp]){
    ap++;
    bp++;
  }

  // jak znaleźliśmy różnicę przed końcem jakiejkolwiek liczby- to źle
  if (ap < M && bp < M) {
    wynik = 0;
  } else {
    // w tym jednym, który < M do końca muszą być same zera
    while (ap < M && Am[ap] == 0) {
      ap++;
    }
    while (bp < M && Bm[bp] == 0) {
      bp++;
    }
    // jak nie są to źle
    if (ap < M || bp < M) {
      wynik = 0;
    }
  }

  if (wynik == 1) {
    // mantysy są takie same, tylko przesunięte o bam
    // sprawdzamy czy cechy spełniają (Ac + bam == Bc);
    wynik = sprawdz_roznice_cech(C, Ac, Bc, bam);
  }

  printf("%d\n", wynik);

  return 0;
}
