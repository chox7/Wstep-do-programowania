# Zadanie 1

Dana jest tablica liczb całkowitych $A$ długości $N > 0$. Spójny fragment tablicy od $i$ do $j$ ($0 \leq i \leq j < N$) nazwiemy segmentem schodkowym, jeśli dla każdego $k$ takiego, że $i+1 \leq k \leq j$, zachodzi $A[k] = A[k-1] - 1$, oraz $A[j] = j - i + 1$.

Napisz fragment programu, który nada zmiennej typu `int` o nazwie `schody` długość najdłuższego segmentu schodkowego w tablicy $A$. Jeśli żaden segment nie jest schodkowy, wynikiem powinno być 0.

Przykładowo, dla tablicy $A = \{6, 5, 4, 3, 7, 6, 5, 4, 3, 2\}$ wynikiem funkcji powinno być 4 ze względu na czteroelementowy segment o indeksach $4..7$. Nie jest to jedyny segment schodkowy w tej tablicy, np. segment o indeksach $1..3$ też jest schodkowy.

## Dziwne moje rozwiązanie, ale chyba dobre

```c
int schody = 0;
int i = 0;
int schody = 0;
int i = 0;
while (i < n - 1) {
    int j = i;

    // Szukamy maksymalnej długości segmentu schodkowego zaczynającego się od i
    while (j < n - 1 && A[j+1] == A[j] - 1) {
        j++;
    }
    if (j > i) {
        int a = A[j];
        int b = j - i + 1;
        if (a <= b) {
            int len = j - (b - a) / 2 - i - (b - a) % 2 + 1;
            if (len > schody) {
                schody = len;
            }
        }
    }
    // Przechodzimy do następnego potencjalnego segmentu
    i = j + 1;
}
```


## Najlepsze rozwiazanie


```c
int schody = 0;
int i = 0;
while (i < n - 1) {
    int j = i;
    while (j < n - 1 && A[j+1] == A[j] - 1) {
        j++;
        int len = j - i + 1;
        // w tym przypadku 
        if (A[j] < len) {
            i++;
            len--;
        }
        if (len == A[j] &&  len > schody) { 
            schody = len;
        }
    }
    i = j + 1;
}
```



# Jeszcze lepsze

```c
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
```