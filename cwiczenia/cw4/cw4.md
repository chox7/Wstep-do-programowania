# Ćwiczenia 04: Sortowanie małych zbiorów danych
Twoim zadaniem jest zoptymalizowanie sortowania zbiorów danych o małych rozmiarach, zawierających od 0 do 5 elementów. Ważnym aspektem jest minimalizacja liczby porównań podczas sortowania.

Wymagania:

- Dane wejściowe: zbiory o rozmiarze od 0 do 5 elementów.

- Cel: Posortuj dane, używając najmniejszej możliwej liczby porównań.

- Przykład:

    - Dla zbioru danych: 0, 0, 1, 3, 5, 7
    
    - Zadanie polega na optymalnym posortowaniu pierwszych 5 elementów, przy czym osiągnięcie rezultatu z 7 porównaniami można uznać za sukces.

Zadanie kładzie nacisk na znalezienie minimalnej liczby porównań potrzebnych do uporządkowania elementów.

---

- **2 elementy**: 1 porównanie.
- **3 elementy**: 2–3 porównania.
- **4 elementy**: 5 porównań. Najpierw sortujemy 3 elementy (3 porównania), a potem wstawiamy czwarty (2 porównania).
- **5 elementów**: Optymalnie 7 porównań (za pomocą algorytmu Forda-Johnsona).


## Zadanie: Merging Sorted Lists

Masz dwie listy: `A` i `B`, obie zawierające posortowane elementy. Twoim zadaniem jest połączenie tych dwóch list w jedną, która również będzie posortowana.


```C
int i = 0;
int j = 0;
int k = 0;

int C[N + M];

while (i < N && j < M) {
    if (A[i] <= B[j]) {
        C[k] = A[i];
        i++;
    } else {
        C[k] = B[j];
        j++;
    }
    k++;
}

while (i < N) {
    C[k] = A[i];
    i++;
    k++;
}

while (j < M) {
    C[k] = B[j];
    j++;
    k++;
}
```