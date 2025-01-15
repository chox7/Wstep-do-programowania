# Publiczne pliki do zadania LNAD (nadlista) #

### Opis plików: ###

* lnad.h - plik nagłówkowy zawierający deklarację typu listowego
  (jak na zajęciach) oraz deklarację funkcji nadlista;
* lnadmain.c - plik zawierający funkcję main, która uruchamia
  funkcję nadlista na przykładzie wczytanym ze standardowego wejścia
  i wypisuje rezultat jej działania;
* lnad_dummy.c - implementacja funkcji nadlista, która działa
  wyłącznie dla przykładu z treści zadania; 
* lnad0a.in - plik wejściowy z przykładem z treści zadania.

Aby uruchomić dostarczoną pseudo-implementację funkcji nadlista należy
wydać polecenie

    gcc -o lnad lnadmain.c lnad_dummy.c
i następnie uruchomić powstały program wykonywalny

    ./lnad
Podobnie, gdy napiszesz własną wersję funkcji nadlista np. w pliku o
nazwie lnad17.c należy go skompilować analogiczną komendą:

    gcc -o lnad lnadmain.c lnad17.c
i uruchomić jak wyżej.
