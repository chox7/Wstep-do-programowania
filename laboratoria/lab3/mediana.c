#include <stdio.h>

int main(void) {
    int a, b, c;
    
    printf("Podaj trzy liczby w celu obliczenia ich mediany.\n");
    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);

    int mediana;

    if ((a >= b && a <= c) || (a >= c && a <= b)) {
        mediana = a;
    } else if ((b >= a && b <= c) || (b >= c && b <= a)) {
        mediana = b;
    } else {
        mediana = c;
    }

    printf("Mediana: %d\n", mediana);

    return 0;
}
