#include <stdio.h>

int main(void) {
    int x;
    int y = 2; // Zaczynamy od dzielnika 2

    scanf("%d", &x); // Pobieramy liczbe ktorej policzymy rozklad

    // Petla dopoki nie rozlozymy x na pierwsze
    while (x != 1) {
        // Sprawdzamy czy liczba x jest podzielna przez y
        if (x % y == 0) {
            x /= y; // Jezeli tak to dzielimy
            if (x != 1) {
                printf("%d * ", y); // I zapisujemy w rozkladzie
            }
        }
        else {
            y++; // Zwiekszamy dzielnik
        }
    }
    printf("%d\n", y); // Ostatni element rozkladu

    return 0;
}

