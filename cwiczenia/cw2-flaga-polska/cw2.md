# Ćwiczenia 02: Flaga Polska

**Zadanie o fladze polskiej**.

#### Treść:

Dane są `M` urn, numerowanych od 1 do `M`, z których każda zawiera żeton biały lub czerwony. Robot ma za zadanie tak poprzestawiać urny, aby wśród kolejnych urn najpierw były te z czerwonymi żetonami, a potem te z białymi żetonami.

#### Do dyspozycji ma dwie funkcje:

1. **Kol(i)** – funkcja określająca kolor żetonu w i-tej urnie.
2. **Z(i, j)** – funkcja zamieniająca urnę i-tą z j-tą.

#### Uwaga:

Robot może się zepsuć, jeśli:
- Każe mu sięgnąć poza zakres `1..M`.
- Zamieni urnę i-tą z urną i-tą (czyli `i` z `i`).


## Podejście nr 1 

```C
int b = 0;
int c = M - 1;

while (b < c) {
    if (kol(b) == 0) {
        ++b;
    } else {
        zam(b, c);
        --c;
    }
}
```

## Podejście nr 2
```C
int b = 0;
int c = 0;

while (c < M) {
    if (kol(c) == 0) {
        if (b < c) { 
            zam(b, c);
        }
        ++b;
    }
    ++c;
}
```