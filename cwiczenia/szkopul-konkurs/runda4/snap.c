#include <stdio.h>
#include <stdlib.h>

int main() {
    int N;
    scanf("%d", &N);
    int A[N];
    for (int i = 0; i < N; i++)
        scanf("%d", &A[i]);

    int wynik = 0;
    int i = 0;

    while (i < N) {
        // Rozpoczęcie nowego segmentu
        int cur = 0;
        int sign = (A[i] > 0) ? 1 : -1; // Określenie znaku pierwszego elementu segmentu
        int j = i;

        // Przetwarzanie segmentu naprzemiennego
        while (j < N && (A[j] > 0) == (sign > 0)) {
            cur += A[j];
            sign *= -1; // Zmiana oczekiwanego znaku
            j++;
        }

        // Aktualizacja wyniku, jeśli znaleziono lepszy segment
        if (cur > wynik) {
            wynik = cur;
        }

        // Kontynuacja od następnego elementu
        i = j;
    }

    printf("%d\n", wynik);
    return 0;
}