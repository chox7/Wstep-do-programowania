# Ćwiczenia 03: Zadanie o fladze holenderskiej

#### Treść:

Mamy `N` urn z żetonami 3 kolorów: czerwonym, białym i niebieskim. Celem jest poprzestawienie ich tak, aby były ułożone w kolejności: czerwone, białe, niebieskie.

#### Wskazówka:

Postaraj się zachować następujący niezmiennik:

**N(c, b, n)** = ∀1≤k<c: Kol(k) = czerwony ∧ ∀c≤k≤b: Kol(k) = biały ∧ ∀n<k≤N: Kol(k) = niebieski ∧ 1≤c≤b≤n+1≤N+1

```C
int c = 0;
int b = 0;
int n = N - 1;

while (b < n) {
    if (kol(b) == 1) {
        ++b;
    } else if (kol(b) == 0) {
        if (c < b) {
            zam(c, b);
        }
        ++b;
        ++c;
    } else {
        zam(b, n);
        --n;
    }
}
```