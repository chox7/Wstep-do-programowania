#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NSUM 11 // Liczba mozliwych wynikow od 2 do 12
#define SCALE 20 // Skala wysokosci histogramu

// Funkcja inicjująca tablicę liczb
void inicjuj_sumy(int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = 0;
    }
}

// Funkcja losujaca liczbe od 1 do n
int randof(int n) {
    return 1 + (int) (rand() / (RAND_MAX + 1.0) * n);
}

// Funkcja losujaca n razy i zapisujaca wynik w tablicy
void losuj_n_razy(int A[], int n) {
    for (int i = 0; i < n; i++) {
        int sum = randof(6) + randof(6);
        A[sum - 2]++;
    }
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
    printf("+\n");
}

void wypisz_histogram(int A[], int n, int skala) {
    // Szukanie maksimum histogramu
    int max = znajdz_maks(A, n);

    // Ramka gora
    ramka_pozioma();

    for (int i = skala; i > 0; i--) {
        // Ramka lewo
        printf("| ");

        for (int j = 0; j < n; j++) {
            if (A[j] * skala / max >= i) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        // Ramka prawo
        printf(" |\n");
    }

    // Ramka dol
    ramka_pozioma();
 }

int main() {
    srand((unsigned) time(NULL));

    int n;
    printf("Podaj liczbę rzutów kostką: ");
    scanf("%d", &n);

    // Inicializacja listy sumowan
    int rzuty[NSUM];
    inicjuj_sumy(rzuty, NSUM);

    // Losowanie n razy
    losuj_n_razy(rzuty, n);

    // Rysowanie histogramu
    wypisz_histogram(rzuty, NSUM, SCALE);

    return 0;
}
