for ((i = 1; i <= 100; i++)); do
    # Sprawdzenie, czy pliki testowe istnieją
    input_file="./in/test$i.in"
    expected_output_file="./out/test$i.out"
    if [[ ! -f "$input_file" ]]; then
        echo "Test $i: Brak pliku wejściowego $input_file"
        continue
    fi
    if [[ ! -f "$expected_output_file" ]]; then
        echo "Test $i: Brak oczekiwanego wyjścia $expected_output_file"
        continue
    fi

    # Wykonanie programu i porównanie wyników
    ./set < "$input_file" > "./set.out"
    echo -n "Test $i. Wynik: "
    if diff -q "./set.out" "$expected_output_file" > /dev/null; then
        echo "OK"
    else
        echo "Źle!"
    fi
done

# Usuwanie tymczasowego pliku
rm -f "./set.out"