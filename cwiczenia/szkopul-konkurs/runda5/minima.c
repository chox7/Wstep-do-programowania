#include <stdio.h>
#include <stdlib.h>

int main() {
    int N;
    scanf("%d", &N);
    int A[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < N; i++) {
        int temp;
        scanf("%d", &temp);
        if (temp > A[i]) {
            A[i] = temp;
        }
    }


    int left = 0;
    int right = N - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (A[mid] < )
    }

}