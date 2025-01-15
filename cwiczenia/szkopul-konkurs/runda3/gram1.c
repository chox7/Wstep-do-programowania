#include <stdio.h>
#include <stdlib.h>
int main(){
    int N; scanf("%d", &N);
    int A[N]; for(int i = 0; i < N; i++) scanf("%d", &A[i]);
    int wynik = 1;
    // Mamy ustalone N, zawartość tablicy A oraz zadeklarowaną zmienną wynik
    // ---------------------------------------------------------------------
    // Poniżej wpisz swój fragment programu:
    int stan = 0; // 0 - S, 1 - B
    for (int i = 0; i < N; i++) {
        int val = A[i];
        if (stan == 0) {
            if (val == 1 || val == 2 || val == 3) {
                continue;
            } else if (val == 0) {
                stan = 1;
            } else {
                wynik = 0;
                break;
            }
        } else {
            if (val == 1) {
                stan = 0;
            } else if (val == 2 || val == 3) {
                continue;
            } else {
                wynik = 0;
            }
        }
    }
    if (stan == 1) {
        wynik = 0;
    }
    // ---------------------------------------------------------------------
    printf("%d\n", wynik);
    return 0;
}