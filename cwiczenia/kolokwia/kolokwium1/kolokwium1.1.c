#include <stdio.h>
int znajdzDlugoscSchodkow(int A[], int n) {
    int schody = 0;
    int i = 0;
    int len = 0;
    for (int i = 1; i < n; ++i) {
        if (A[i] == A[i - 1] - 1) {  // Sprawdzamy, czy mamy ciąg schodkowy
            len++;
            // Sprawdzamy warunek A[j] = j - i + 1 dla bieżącego segmentu
            // Lub gdy A[j] < j - i + 1 to znaczy że mozemy zwiekszyc i i skrocic ciag
            if (A[i] <= len) {
                len = A[i];
                if (len > schody) {
                    schody = len;
                }
            }
        } else {
            len = 1; // Resetujemy długość ciągu
        }
    }

    return schody;
}

// Funkcja pomocnicza do uruchamiania testów.
void test(int A[], int n, int expected) {
    int result = znajdzDlugoscSchodkow(A, n);
    if (result == expected) {
        printf("Test passed! (Expected: %d, Got: %d)\n", expected, result);
    } else {
        printf("Test failed. (Expected: %d, Got: %d)\n", expected, result);
    }
}

int main() {
    // Testy jednostkowe

    // Przykład z zadania
    int A1[] = {6, 5, 4, 3, 7, 6, 5, 4, 3, 2};
    test(A1, 10, 4);

    // Brak schodkowego segmentu
    int A2[] = {3, 6, 1, 4};
    test(A2, 4, 0);

    // Jednoelementowy segment
    int A3[] = {1};
    test(A3, 1, 0);

    // Długi schodkowy segment
    int A4[] = {10, 9, 8, 7, 6, 5};
    test(A4, 6, 5);

    // Segment schodkowy o różnych długościach
    int A5[] = {4, 3, 2, 1, 5, 4, 3, 2, 1};
    test(A5, 9, 3);

    // Pusty segment (gdy długość segmentu wynosi 0)
    int A6[] = {1, 1, 1, 1};
    test(A6, 4, 0);

    return 0;
}