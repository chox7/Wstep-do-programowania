#include <stdio.h>

int main(void) {
    int a, b, c;
    
    printf("Podaj trzy liczby w celu obliczenia ich mediany.\n");
    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);

    // Upewniamy się, ze a <= b, a nastepnie b <= c
    if (a > b) {
        int temp = a;
        a = b;
        b = temp;
    }
    if (b > c) {
        int temp = b;
        b = c;
        c = temp;
    }
    if (a > b) {
        int temp = a;
        a = b;
        b = temp;
    }
    printf("Mediana: %d\n", b);

    return 0;
}
