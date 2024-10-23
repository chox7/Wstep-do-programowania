#include <stdio.h>
#include <stdlib.h>
void _zakres(int i, char* is, int M, char *funkcja){
    if (! (0 <= i && i < M)) {
        fprintf(stderr, "Przekroczenie zakresu w %s: argument %s to %d, miało być 0 <= %s < %d\n",
            funkcja, is, i, is, M); exit(1); } }

int _wartosc(int i, int t[], int N){
    _zakres(i, "i", 2*N, "Wartosc"); return t[i]; }

void _zamien(int i, int j, int t[], int N){
    _zakres(i, "i", 2*N, "Zamien"); _zakres(j, "j", 2*N, "Zamien");
    int tmp = t[i]; t[i] = t[j]; t[j] = tmp; }

int main(){
    int N; scanf("%d", &N);
    int t[2*N]; for(int i = 0; i < 2*N; i++) scanf("%d", &t[i]);
    #define Wartosc(i) _wartosc(i,t,N)
    #define Zamien(i,j) _zamien(i,j,t,N)
    // Mamy ustalone N i zawartość urn
    // -------------------------------------
    // Poniżej wpisz swój fragment programu:
    // -------------------------------------
    int a = 0;
    int b = 2 * N - 1;
    int c = 1;
     
    while (a < 2*N) {
        if (Wartosc(a) == 0) {
            Zamien(a, c);
            c += 2;
        }else if (Wartosc(a) > 0) {
            Zamien(a, b);
            b -= 2;
        }else {
            a += 2;
        }
    }
    while (b > c) {
        if (Wartosc(b) == 0) {
            Zamien(b,c);
            c += 2;
        } else {
            b -= 2;
        }
    }
    for(int i=0; i<2*N; i++) printf("%d ", t[i]);
    printf("\n");
    return 0;
}