#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int randof(int n) {
    return (int) (rand() / (RAND_MAX + 1.0) * n);
}

int main() { 
    srand((unsigned) time(NULL));

    int n;
    scanf("%d", &n);

    int m = 11; // możliwe sumy: 2,3,4,5,6,7,8,9,10,11,12
    int A[m];
    for (int i = 0; i < m; i++) {
        A[i] = 0;
    }

    for (int i = 0; i < n; i++) { 
        int sum = randof(6) + 1 + randof(6) + 1;
        A[sum - 2]++;
    }
    
    for (int i = 0; i < m; i++) {
        printf("%d\n", A[i]);
    }

    return 0;
}