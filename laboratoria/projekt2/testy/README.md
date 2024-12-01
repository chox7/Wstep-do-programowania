# Kostka-Rubika-Testy
Siemano, nie umiem w githuba ale łapcie takie coś.
Aby przetestować swój program:
1. Wrzuć w jeden folder plik 'testerka.sh', foldery '/in' i '/out', swój program nazwany 'kostka_rubika.c' oraz flagi kompilacji w pliku 'opcje'.
2. (NIE ZNAM SIE WIEC NIE WIEM CZY TO POTRZEBNE) Nadaj uprawnienia do uruchamiania tego skryptu pisząc w terminalu 'chmod -x testerka.sh'.
3. Uruchom testerkę komendą './testerka.sh'.
4. Czekaj cierpliwie.

Testerka ta sama kompiluje program, przy kompilacji nadając wartość N. Program jest testowany w valgrindzie, więc testowanie trochę zajmuje.  
Testy wygladają następująco:  
1-3 - testy z moodla, program kompiluje się bez definiowania N.  
4-10 - kostka 1x1x1, parę testów z ręki.  
11-100 - kostka 2x2x2.  
101-200 - kostka 3x3x3.  
...  
801-900 - kostka 10x10x10.  

Liczba komend w jednym tescie to losowa liczba z przedziału [5, i - (N - 2) * 100) * 2 + 5), gdzie 'i' to numer testu a 'N' - liczba ścian.
Wzorek wygląda dziwnie, ale chodzi o to by dla każdego N pierwsze testy były mniejsze, za to ostatnie wieksze (chociaż no niekoniecznie musi tak być przez to ze to wartość losowa).

To chyba tyle, pozdrawiam!
