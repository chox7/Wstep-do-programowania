#include <stdio.h>
#include <limits.h>

int collatz_steps(int n, int *steps) {
    int collatz = n;
    *steps = 0;
    
    while (collatz > 1) {
        if (collatz % 2 == 0) {
            collatz /= 2;
        } else {
            if (collatz > (INT_MAX - 1) / 3) {
                return -1; // Przepełnienie
            }
            collatz = 3 * collatz + 1;
        }
        (*steps)++;
    }
    return 0;
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
            int steps;
            int result = collatz_steps(i, &steps);

            if (result == -1) {
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