#include <stdio.h>
#include <stdlib.h>

int main(){
    int N; scanf("%d", &N);
    int A[N]; for(int i = 0; i < N; i++) scanf("%d", &A[i]);
    int wynik = 1; // Zakładamy, że ciąg jest bitoniczny

    int i = 0;

    // Jeżeli N = 0 to ciąg nie jest bitoniczny
    if (N == 0) {
        wynik = 0;
    }

    // Przechodzimy przez ciąg rosnący
    while (i < N-1 && A[i] < A[i+1]) {
        i++;
    }

    // Przechodzimy przez ciąg malejący
    while (i < N-1 && A[i] > A[i+1]) {
        i++;
    }

    // Jeśli nie doszliśmy do końca tablicy, ciąg nie jest bitoniczny
    if (i != N-1) {
        wynik = 0;
    }

    printf("%d\n", wynik);
    return 0;
}