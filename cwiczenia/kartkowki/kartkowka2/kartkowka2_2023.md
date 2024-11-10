Dana jest tablica liczb całkowitych `A` o długości `N > 0`. Spójny fragment tablicy od `i` do `j`, gdzie `0 <= i <= j < N`, nazwiemy **segmentem Fibonacciego**, jeśli dla każdego `k` takiego, że `i + 2 <= k <= j`, zachodzi `A[k] = A[k - 1] + A[k - 2]`.

Napisz fragment programu obliczający długość najdłuższego segmentu Fibonacciego w tablicy `A` i przypisujący ją do zmiennej `maksfib`.

### Przykłady
- Dla tablicy `A = {2, 6, 7, 13, 20, 1}` wynik to `maksfib = 4`.
- Dla tablicy `A = {4, 3, 2, 1}` wynik to `maksfib = 2`.


```c
int maksFib = 2;
int maks;

for (int i = 2; i < n; i++) {
    maks = 2;
    while (i < n && A[i-2] + A[i-1] == A[i]) {
        maks++;
        i++;
    }
    if (maks > maksFib) {
        maksFib = maks;
    }
}
```
