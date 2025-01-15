#include <stdio.h>

// Funkcja do rozwiązania Wież Hanoi z zakazanym przejściem między A i B
void hanoi(int* sizes, int n, char source, char target, char auxiliary) {
    if (n == 0) {
        return; // Nic do przeniesienia
    }
    int i = n-1;
    while (i>=0 && sizes[i] == sizes[n-1]) {
        i--;
    }
    i++;
    hanoi(sizes, i, source, auxiliary, target); // Przenieś mniejsze dyski na pomocniczy
    for (int j = i; j < n; j++) {
        printf("%c %c %d\n", source, target, sizes[j]); // Przenieś dyski o rozmiarze sizes[j] na target
    }
    hanoi(sizes, i, auxiliary, target, source); // Przenieś mniejsze dyski na target
}

int main() {
    int n; // Liczba dysków
    scanf("%d", &n);
    int sizes[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &sizes[n-i-1]);
    }
    hanoi(sizes, n, '1', '3', '2');
    return 0;
}