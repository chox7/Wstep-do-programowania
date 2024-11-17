#include <stdio.h>

int main(void) {
    int x;
    int y = 2; // Zaczynamy od dzielnika 2

    scanf("%d", &x);

    // Petla dopoki nie rozlozymy x na pierwsze
    while (x != 1) {
        if (x % y == 0) {
            x /= y;
            if (x != 1) {
                printf("%d * ", y);
            }
        }
        else {
            y++;
        }
    }
    printf("%d\n", y); // Ostatni element rozkladu

    return 0;
}

