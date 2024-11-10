#include <stdio.h>
#include <limits.h>

int collatz_steps(int n, int *overflow) {
    int steps = 0;
    long long collatz = n; 
    
    while (collatz > 1) {
        if (collatz % 2 == 0) {
            collatz /= 2;
        } else {
            collatz = 3 * collatz + 1;
            if (collatz > INT_MAX) {  // Sprawdzamy przekroczenie zakresu int
                *overflow = 1;
                return n;
            }
        }
        steps++;
    }
    return steps;
}

int main() {
    int a, b;
    scanf("%d", &a);
    scanf("%d", &b);

    if (a > 0 && a <= b) {
        int overflow_found = 0;
        int min_overflow_start = 0;
        int max_steps = 0;
        int max_steps_start = 0;

        for (int i = a; i <= b; i++) {
            int overflow = 0;
            int steps = collatz_steps(i, &overflow);

            if (overflow) {
                if (!overflow_found || i < min_overflow_start) {
                    min_overflow_start = i;
                    overflow_found = 1;
                }
            } else if (steps > max_steps) {
                max_steps = steps;
                max_steps_start = i;
            }
        }

        if (overflow_found) {
            printf("%d?\n", min_overflow_start);
        } else {
            printf("%d %d\n", max_steps_start, max_steps);
        }
    }

    return 0;
}