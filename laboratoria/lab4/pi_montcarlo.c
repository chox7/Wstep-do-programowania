#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double random_double(void) {
    return (double) rand() / RAND_MAX;
}

int main(void) {
    int n;
    scanf("%d", &n);

    double x, y, pi;
    int count = 0;

    srand((unsigned) time(NULL));

    for (int i = 0; i < n; i++) {
        x = random_double();
        y = random_double();

        if (x * x + y * y <= 1.0) {
            count++;
        }
    }
    pi = (double) count / n * 4;
    printf("Przybliżona wartość liczby pi: %lf", pi);
    return 0;
}
