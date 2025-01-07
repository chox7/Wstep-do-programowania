#!/bin/sh

# Wczytanie opcji kompilacji z pliku
if [ ! -f opcje ]; then
    echo "Plik 'opcje' nie istnieje!"
    exit 1
fi
OPCJE=$(cat opcje)

# Kompilacja programu
gcc $OPCJE sokoban.c -o sokoban
if [ $? -ne 0 ]; then
    echo "Błąd kompilacji!"
    exit 1
fi
echo "Kompilacja zakończona pomyślnie."

# Testy z użyciem valgrinda na przykładach 1-3
for i in 1 2 3; do
    INPUT="przyklady/przyklad${i}.in"
    echo "Testowanie Valgrind z przykładem $INPUT..."
    valgrind --leak-check=full -q --error-exitcode=1 ./sokoban < "$INPUT" > /dev/null
    if [ $? -ne 0 ]; then
        echo "Valgrind wykrył problemy w przykładzie $INPUT!"
        exit 1
    fi
done
echo "Valgrind zakończył testy na przykładach 1-3 pomyślnie."

# Testy z użyciem diff na testach 1-10
for i in $(seq 1 10); do
    INPUT="testy/test${i}.in"
    OUTPUT="testy/test${i}.out"
    echo "Testowanie diff na teście $INPUT..."

    ./sokoban < "$INPUT" | diff - "$OUTPUT"
    if [ $? -ne 0 ]; then
        echo "Błąd: Wynik różni się dla testu $INPUT!"
        exit 1
    fi
done
echo "Wszystkie testy zakończone pomyślnie."