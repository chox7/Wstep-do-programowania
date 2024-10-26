#include <stdio.h>

int main(void) {
    double s, k;
    int n;

    scanf("%lf", &s);
    scanf("%lf", &k);
    scanf("%d", &n);

    // Ze wzoru
    double suma = (2 * s + (n - 1) * k) / 2 * n;

    printf("%lf\n", suma);
    
    return 0;
}
