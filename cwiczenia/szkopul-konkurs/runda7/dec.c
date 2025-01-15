#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N;
    scanf("%d", &N);

    int A[N];
    int B[N];

    for(int i = N-1; i >= 0; i--) scanf("%d", &A[i]);
    for(int i = N-1; i >= 0; i--) scanf("%d", &B[i]);

    int wynik = 1;

    int i = N - 1;
    while (A[i] == 0) i--;

    int j = N - 1;
    while (B[j] == 0) j--;


    while (i >= 0 && j >= 0 && wynik) {
        if (A[i] != B[j]) {
            wynik = 0;
        }
        i--;
        j--;
    }

    while (i >= 0 && wynik) {
        if (A[i] != 0) {
            wynik = 0;
        }
        i--;
    }

    while (j >= 0 && wynik) {
        if (B[j] != 0) {
            wynik = 0;
        }
        j--;
    }
    if (wynik) {
        printf("1\n");
    } else {
        printf("0\n");
    }
    return 0;
}