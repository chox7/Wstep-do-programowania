#include <stdio.h>
#include <stdlib.h>
int main(){
    int N; scanf("%d", &N);
    int A[N]; for(int i = 0; i < N; i++) scanf("%d", &A[i]);
    int wynik = 0;
    // Mamy ustalone N, zawartość tablicy A oraz zadeklarowaną zmienną wynik
    // ---------------------------------------------------------------------
    int nieujemne = 0;
    for (int i = 0; i < N; i ++) {
        if (A[i] >= 0) {
            nieujemne++;
        }
    }

    for (int i = 0; i < N; i++) {
        if (A[i] < 0) {
            wynik += nieujemne;
        } else {
            nieujemne--;
        }
    }
    // ---------------------------------------------------------------------
    printf("%d\n", wynik);
    return 0;
}