# Ćwiczenia 01: Wstęp

**Zadanie o przecinających się prostokątach** – na płaszczyźnie dane są dwa prostokąty o bokach prostopadłych do osi. Wyznacz ich przecięcie.

#### Wskazówki do rozwiązania:

1. **Rodzaj rozwiązania**: Odpowiedź zależy od tego, czy prostokąty są otwarte, czy domknięte. Dla ułatwienia załóżmy, że są otwarte. W takim przypadku możliwe są dwa typy wyników:
   - Zbiór pusty.
   - Prostokąt o bokach prostopadłych do osi.

2. **Reprezentacja danych i wyników**: 
   - Dla każdego prostokąta potrzebujemy 4 liczby rzeczywiste (lub całkowite, jeśli chcemy to robić na kratkach), które reprezentują współrzędne wierzchołków przy przekątnej. 
   - Wygodnie jest ustalić, że chodzi o konkretną przekątną, np. tę, która idzie w prawo w górę.

#### Treść zadania:

Dane są 8 liczb rzeczywistych: `a1, b1, a2, b2, a3, b3, a4, b4`. Punkty o współrzędnych `(a1, b1)` i `(a2, b2)` są wierzchołkami prostokąta P1, natomiast `(a3, b3)` i `(a4, b4)` są wierzchołkami prostokąta P2, przy czym:
- `a1 < a2, b1 < b2`
- `a3 < a4, b3 < b4`