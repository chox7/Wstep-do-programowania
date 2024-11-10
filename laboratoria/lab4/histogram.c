#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NSUM 11 // Liczba mozliwych wynikow od 2 do 12
#define SCALE 20 // Skala wysokosci histogramu

// Funkcja losujaca liczbe od 1 do n
int randof(int n) {
    return 1 + (int) (rand() / (RAND_MAX + 1.0) * n);
}

// Funkcja znajdujaca maksimum danej listy
int znajdz_maks(int A[], int n) {
    int max = 0;
    for (int i = 0; i < n; i++) {
        if (A[i] > max) {
            max = A[i];
        }
    }
    return max;
}

// Funkcja rysujaca ramke pozioma
void ramka_pozioma() {
    printf("+");
    for (int i = 0; i < NSUM + 2; i++) {
       printf("-");
    }
    printf("+");
    printf("\n");
}

int main() {
    srand((unsigned) time(NULL));

    int n;
    scanf("%d", &n);

    // Inicializacja listy sumowan
    int A[NSUM];
    for (int i = 0; i < NSUM; i++) {
        A[i] = 0;
    }

    // Losowanie n razy
    for (int i = 0; i < n; i++) {
        int sum = randof(6) + randof(6);
        A[sum - 2]++;
    }

    // Szukanie maksimum histogramu
    int max = znajdz_maks(A, NSUM);

    // Ramka gora
    ramka_pozioma();

    // Rysowanie histogramu
    for (int i = SCALE; i > 0; i--) {
        // Ramka lewo
        printf("| ");
        for (int j = 0; j < NSUM; j++) {
            if (A[j] * SCALE / max >= i) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        // Ramka prawo
        printf(" |");
        printf("\n");
    }

    // Ramka dol
    ramka_pozioma();

    return 0;
}
