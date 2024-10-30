#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    int n;
    scanf("%d", &n);

    double x, y, pi;
    int count = 0;

    srand((unsigned) time(NULL));

    for (int i = 0; i < n; i++) {
        x = (double) rand() / RAND_MAX;
        y = (double) rand() / RAND_MAX;

        if (x * x + y * y <= 1.0) {
            count++;
        }
    }
    pi = (double) count / n * 4;
    printf("%lf", pi);
    return 0;
}
