# Kartkówka 2 (4-11-2020)
W urnach numerowanych od 1 do n znajdują się tylko żetony białe i czerwone. Robot
potrafi wykonywać drogą instrukcję Kol(i) przyjmującą wartości ze zbioru {biały,
czerwony}.

Białym segmentem nazwiemy taką parę (i,j), że 1<=i<=j<=n oraz dla każdego k: jeśli
i<=k<=j, to Kol(k)=biały.

Napisz fragment programu, który zmiennej bs nada wartość równą liczbie białych
segmentów.

Określ, ile razy w najgorszym przypadku wykona się funkcja Kol.

```C
int bs = 0; // Początkowo 0 białych segmentów
int i = 1; // Wskaźnik do iteracji przez urny
int p;
int liczbabiałych;
while (i <= n) {
    if (Kol(i) == 'biały') {
        p = i; // zapamiętujemy indeks początku segmentu
        i++;
        // Pomijamy wszystkie kolejne białe żetony
        while (i <= n && Kol(i) == 'biały') {
            i++;
        }
        liczbabiałych = i - p;
        bs += liczbabiałych * (liczbabiałych + 1) / 2;
    }
    i++;
}
```

Funkcja Kol wywoła się n razy. 