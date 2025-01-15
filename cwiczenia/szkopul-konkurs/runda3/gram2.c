#include <stdio.h>
#include <stdlib.h>

// Funkcja sprawdzająca Z ::= 0 | 1Z | 2Z | 3Z
int checkZ(int* A, int start, int end) {
    int i = start;
    while (i < end) {
        if (A[i] == 0) {
            return i; // Znaleziono Z, kończymy
        }
        if (A[i] != 1 && A[i] != 2 && A[i] != 3) {
            return -1; // Niepoprawny znak
        }
        i++;
    }
    return -1; // Nie znaleziono Z
}

// Funkcja sprawdzająca J ::= 1 | J0 | J2 | J3
int checkJ(int* A, int start, int end) {
    int i = end - 1;
    while (i >= start) {
        if (A[i] == 1) {
            return i; // Znaleziono J, kończymy
        }
        if (A[i] != 0 && A[i] != 2 && A[i] != 3) {
            return -1; // Niepoprawny znak
        }
        i--;
    }
    return -1; // Nie znaleziono J
}

// Funkcja sprawdzająca S ::= ZSJ | ǫ
int checkS(int* A, int start, int end) {
    if (start == end) return 0; // Pusty zakres, poprawne S

    int z = checkZ(A, start, end - 1);
    if (z == -1) return -1; // Niepoprawny Z

    int j = checkJ(A, z + 1, end);
    if (j == -1) return -1; // Niepoprawny J

    return checkS(A, z + 1, j); // Rekurencyjnie sprawdzamy środek
}

int main() {
    int N;
    scanf("%d", &N);
    int A[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    int wynik = 1;

    // Sprawdzamy warunek
    if (N == 0 || checkS(A, 0, N) == 0) {
        wynik = 1;
    } else {
        wynik = 0;
    }

    printf("%d\n", wynik);
    return 0;
}