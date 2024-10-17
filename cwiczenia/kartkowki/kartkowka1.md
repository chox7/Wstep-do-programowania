# Kartkówka 1 - 15.10.2024

W urnach numerowanych od 1 do n znajdują się żetony czerwone albo białe. Masz do dyspozycji funkcję `Kol(i)`, która przyjmuje wartości ze zbioru `{czerwony, biały}` i określa kolor żetonu w urnie o indeksie `i`. Przypisz całkowitoliczbowej zmiennej `ccb` wartość `1`, jeśli istnieją kolejne indeksy `i`, `i+1`, `i+2` w podanym zakresie takie, że urny o tych indeksach zawierają kolejno żeton czerwony, czerwony i biały, lub nadaj zmiennej `ccb` wartość `0`, jeśli takie indeksy nie istnieją.

Postaraj się nie wywoływać funkcji `Kol` więcej razy, niż jest to konieczne do ustalenia wyniku w pesymistycznym przypadku (w szczególności, wywołanie funkcji `Kol` więcej niż raz dla tego samego argumentu lub wywołanie jej, jeśli wynik jest już znany, będzie traktowane jako błąd). Napisz stosowny algorytm w postaci fragmentu programu. Określ, dla jakich przykładowych danych program wykona najwięcej wywołań funkcji `Kol` oraz podaj dokładną liczbę tych wywołań.

Uwaga: funkcja `Kol` może się zepsuć, jeśli jej argument będzie spoza zakresu `[1...n]`. Zakładamy, że `n >= 0` (`n = 0` oznacza, że nie ma żadnej urny).


## Najprostszy pomysł: liczenie czerwonych żetonów pod rząd

W tym podejściu, przechodzimy przez wszystkie urny i sprawdzamy, ile razy z rzędu pojawia się czerwony żeton. Gdy natrafimy na żeton biały, sprawdzamy, czy poprzednie dwie urny zawierały czerwone żetony.

```C
int ccb = 0; // Na początku zakładamy, że nie ma pasującej trójki
int czerwone_count = 0; // Zmienna do zliczania czerwonych żetonów pod rząd

// Sprawdzenie, czy jest wystarczająco dużo urn
if (n < 3) {
    return ccb; // Zwróć 0, jeśli nie ma wsytarczającej liczby urn
}

// Iterujemy przez wszystkie urny od 1 do n
for (int i = 1; i <= n; i++) {
    if (Kol(i) == 'czerwony') {
        czerwone_count++; // Zwiększamy licznik czerwonych żetonów, jeśli znajdziemy czerwony żeton
    } else {
        // Jeśli napotkamy biały żeton, sprawdzamy, czy wcześniejsze 2 urny zawierały czerwone żetony
        if (czerwone_count >= 2) {
            ccb = 1; // Znaleźliśmy pasującą sekwencję (czerwony, czerwony, biały)
            break; // Możemy zakończyć, bo znaleźliśmy rozwiązanie
        }
        czerwone_count = 0; // Resetujemy licznik, bo natrafiliśmy na żeton biały
    }
}

return ccb; // Zwracamy wynik (1, jeśli znaleźliśmy pasującą sekwencję, 0 jeśli nie)
```

### Opis:

W pierwszej kolejności sprawdzamy, czy mamy co najmniej 3 urny — bez tego nie ma możliwości, by istniała szukana sekwencja.
Iterujemy przez urny i zliczamy czerwone żetony. Jeśli natrafimy na biały żeton, sprawdzamy, czy poprzednie dwie urny były czerwone.
Gdy znajdziemy sekwencję (czerwony, czerwony, biały), przypisujemy ccb = 1 i kończymy pętlę.
W przeciwnym razie, po zakończeniu pętli, zwracamy ccb = 0, jeśli sekwencja nie została znaleziona.

### Złożoność:

W najgorszym przypadku funkcja Kol jest wywoływana dokładnie n razy, czyli złożoność czasowa wynosi O(n).

## Algorytm KMP

To podejście opiera się na wykorzystaniu prostszej wersji [algorytmu KMP](https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm), który efektywnie znajduje podciągi w ciągu. Algorytm KMP minimalizuje liczbę porównań, korzystając z tablicy wskaźników powrotu, co pozwala uniknąć zbędnych porównań, jeśli częściowe dopasowanie zawiedzie.

```C
char* szukany[] = {"czerwony", "czerwony", "bialy"}; // Szukana sekwencja żetonów
int szukany_index[] = {0, 1, 0}; // Wskaźnik powrotu w przypadku niepowodzenia dopasowania
int j = 0; // Wskaźnik dla szukanej sekwencji
int ccb = 0; // Zmienna wynikowa
int i = 1; // Iteracja po urnach zaczyna się od 1

while (i <= n && j < 3) {
    if (Kol(i) == szukany[j]) {
        j++; // Zwiększamy wskaźnik, jeśli kolor w urnie pasuje do szukanej sekwencji
    } else {
        j = szukany_index[j]; // Resetujemy wskaźnik do odpowiedniej wartości w tablicy wskaźników
    }
    i++; // Przechodzimy do następnej urny
}

if (j == 3) {
    ccb = 1; // Jeśli udało się dopasować całą sekwencję (3 żetony), ustawiamy ccb na 1
}

return ccb; // Zwracamy wynik
```

### Opis:

Sekwencję szukanych żetonów przechowujemy w tablicy szukany[], a dodatkowo korzystamy z tablicy szukany_index[], która wskazuje, jak daleko cofnąć się w przypadku niepowodzenia dopasowania.
Algorytm porównuje żetony z urn z szukaną sekwencją. Gdy nie uda się dopasować elementu, zamiast wracać do początku, algorytm cofa wskaźnik na podstawie tablicy wskaźników szukany_index[].
Jeśli uda się znaleźć pełne dopasowanie (wskaźnik j osiągnie wartość 3), algorytm ustawia ccb = 1.

### Zalety:

Efektywność: unikasz zbędnych porównań, minimalizując liczbę wywołań funkcji Kol w przypadku częściowego dopasowania.
Czytelność: kod jest prosty i klarowny, a zastosowanie algorytmu KMP zmniejsza złożoność w przypadku dłuższych sekwencji.

### Złożoność:

Dzięki zastosowaniu algorytmu KMP złożoność czasowa wynosi O(n), ale algorytm działa bardziej efektywnie w przypadku długich sekwencji żetonów, ponieważ eliminuje zbędne porównania.

## Wydajność

W najgorszym przypadku, dla obu rozwiązań, funkcja Kol będzie wywoływana n razy. Może to się zdarzyć, jeśli przeszukujemy wszystkie urny, a pasująca sekwencja pojawia się dopiero na końcu lub wcale.

Najbardziej kosztowny przypadek dla algorytmu KMP wystąpi wtedy, gdy napotykamy wiele czerwonych żetonów, ale nie znajdziemy pełnej sekwencji (np. czerwony, czerwony, czerwony, ...). W takim scenariuszu algorytm będzie wracał do częściowych dopasowań, co zminimalizuje liczbę porównań.