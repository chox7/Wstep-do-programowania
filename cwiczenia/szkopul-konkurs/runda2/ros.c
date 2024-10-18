#include <stdio.h>
#include <stdlib.h>
int main(){
    int N; scanf("%d", &N);
    int A[N]; for(int i = 0; i < N; i++) scanf("%d", &A[i]);
    
    // Zakładamy, że początkowo ciąg jest rosnący.
    int wynik = 1; 
    
    // Sprawdzamy, czy tablica jest ściśle rosnąca
    for (int i = 1; i < N; i++) {
        // Jeśli znajdziemy element, który nie jest większy od poprzedniego, wynik = 0
        if (A[i-1] >= A[i]) {
            wynik = 0;
            break; // Nie ma potrzeby dalszego sprawdzania, przerywamy pętlę
        }
    }
    
    printf("%d\n", wynik);
    return 0;
}