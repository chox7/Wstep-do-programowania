# Kartkówka 1 - 2020

Liczba $n$ jest nieujemną liczbą całkowitą podzielną przez 3. W urnach numerowanych od 1 do $n$
znajdują się żetony czerwone albo białe ustawione kolejno według wzoru `ccbccbccb...ccb`. Masz do
dyspozycji procedurę `Zamień(i, j)`, która zamienia zawartości urn o numerach $i$ oraz $j$.

Napisz fragment programu, który poprzestawia żetony tak, aby wszystkie czerwone znalazły się przed
białymi. Postaraj się wykonać możliwie mało zamian. Pod żadnym pozorem nie wolno wywołać
procedury `Zamień` z którymkolwiek z argumentów spoza przedziału $1 \ldots n$, czyli argumenty
procedury muszą spełniać warunek $1 \leq i, j \leq n$. Ponadto błędem zakończy się każde wywołanie
procedury z argumentami sobie równymi.


```c
int a = 3;
int b = n - 1;
skok = 1;
while (a < b) {
    Zamień(a,b);
    a += 3;
    b -= skok;
    skok = 3 - skok;
}

```