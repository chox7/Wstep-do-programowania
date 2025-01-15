#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N;
    scanf("%d", &N);

    int A[N];
    int B[N];

    for(int i = N-1; i >= 0; i--) scanf("%d", &A[i]);
    for(int i = N-1; i >= 0; i--) scanf("%d", &B[i]);

    return 0;
}