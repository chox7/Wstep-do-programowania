# Zadanie 1 

```c
int licznik_czerwonych = A[n - 1];
B[n - 1] = 0

for (int i = n - 2; i >= 0; i--) {
    B[i] = B[i+1]
    if (A[i] == 1) {
        licznik_czerwonych++;
    } else {
        B[i] += licznik_czerwonych; // Laczymy w pary bialy z kazdym juz znanym czerwonym
    }
}
```