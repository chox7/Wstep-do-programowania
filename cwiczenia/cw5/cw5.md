# Ćwiczenia 05: Najdłuższy segment stały (plateau)

Twoim zadaniem jest znalezienie **najdłuższego segmentu o stałej wartości** w tablicy. W zależności od warunków, zadanie rozważane jest w dwóch wariantach:

1. **Tablica posortowana** – elementy tablicy są uporządkowane rosnąco.
2. **Tablica nieposortowana** – elementy mogą być w dowolnej kolejności.

Dla obu przypadków należy znaleźć najdłuższy ciąg sąsiadujących elementów, które mają tę samą wartość.


```C
int count = 1;
int el_max = 0;
int ind_plateau = 0;

for (int i = 1; i < n; i++) {
    if (A[i] == A[i-1]) {
        count++;
    } else {
        if (count > el_max) {
            el_max = count;
            ind_plateau = i - count;  // gdzie zaczyna się najdłuższy segment
        }
        count = 1;  // resetuj licznik dla nowego elementu
    }
}

if (count > el_max) {
    el_max = count;
    ind_plateau = n - count;
```

