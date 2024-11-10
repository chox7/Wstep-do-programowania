#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LOTTO_SIZE 6    // Liczba losowań
#define MAX_NUMBER 49   // Maksymalna liczba do wylosowania

// Funkcja losująca liczbę od 1 do n
int randof(int n) {
    return 1 + (int) (rand() / (RAND_MAX + 1.0) * n);
}

// Funkcja sprawdzająca, czy liczba jest w tablicy
int number_exists(int numbers[], int size, int num) {
    for (int i = 0; i < size; i++) {
        if (numbers[i] == num) {
            return 1;  // liczba już jest w tablicy
        }
    }
    return 0;  // liczba jest unikalna
}

// Funkcja losująca 6 unikalnych liczb. Zapisuje wynik w tablicy A.
void lotto_simulation(int A[]) {
    int count = 0;
    while (count < LOTTO_SIZE) {
        int a = randof(MAX_NUMBER);
        if (!number_exists(A, count, a)) {
            A[count] = a;
            count++;
        }
    }
}

// Funkcja zwracająca liczbę trafionych liczb w kuponie
int count_wins(int coupon[], int winners[], int size) {
    int score = 0;
    for (int i = 0; i < size; i++) {
        if (number_exists(winners, size, coupon[i])) {
            score++;
        }
    }
    return score;
}

int main() {
    srand((unsigned) time(NULL));

    // Pobranie od użytkownika liczby losowań
    int n;
    printf("Podaj liczbe losowan: ");
    scanf("%d", &n);

    // Inicjalizacja tablicy do zbierania wyników
    int results[LOTTO_SIZE + 1] = {0}; 

    // Symulacja losowania 6 liczb wygranych
    int winners[LOTTO_SIZE];
    lotto_simulation(winners);

    // Przeprowadzenie losowania n kuponów
    for (int i = 0; i < n; i++) {
        // Losowanie 6 liczb dla kuponu
        int coupon[LOTTO_SIZE];
        lotto_simulation(coupon);
        results[count_wins(coupon, winners, LOTTO_SIZE)]++;
    }

    // Wypisanie wyników
    printf("Wyniki:\n");
    for (int i = 0; i < LOTTO_SIZE + 1; i++) {
        printf("%d: %d\n", i, results[i]);
    }
    return 0;
}