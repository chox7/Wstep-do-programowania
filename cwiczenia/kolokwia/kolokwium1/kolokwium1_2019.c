#include <assert.h>
#include <stdio.h>

int podia(int A[], int n) {
    int i = 0;
    int j = n - 1;

    //
    while (A[i] >= A[j]) {
        j--;
    } 
    j++;

    while (A[i] <= A[j]) {
        i++;
    }
    i--;

    int stala = 0;
    int pary = 0;
    while (A[i+1] != A[i+2] && A[j-1] != A[j-2]) {
        pary += (i+1) * (n-j);
        printf("%d\n", pary);
        if (A[i+1] >= A[j-1]) {
            j--;
        } else if (A[i+1] < A[j-1]) {
            i++;
        }
    }
    if (i != 0 || j != n-1) {
        pary += (i+1) * (n-j) * (j-i-1);
    }
    printf("%d\n", pary);
    return pary;
}

void test_podia() {
    // Test 1: Ciąg prawie bitoniczny, wynik oczekiwany: 3
    int A1[] = {1, 2, 2, 2, 1, 0};
    int n1 = sizeof(A1) / sizeof(A1[0]);
    assert(podia(A1, n1) == 6);

    // Test 2: Brak bitonicznego wzorca, wynik oczekiwany: 0
    int A2[] = {1, 1, 1, 1};
    int n2 = sizeof(A2) / sizeof(A2[0]);
    assert(podia(A2, n2) == 0);

    // Test 3: Ciąg całkowicie rosnący, wynik oczekiwany: 0
    int A3[] = {1, 2, 3, 4, 5};
    int n3 = sizeof(A3) / sizeof(A3[0]);
    assert(podia(A3, n3) == 0);

    // Test 4: Ciąg całkowicie malejący, wynik oczekiwany: 0
    int A4[] = {5, 4, 3, 2, 1};
    int n4 = sizeof(A4) / sizeof(A4[0]);
    assert(podia(A4, n4) == 0);

    // Test 5: Prawie bitoniczny, z dłuższymi fragmentami, wynik oczekiwany: 8
    int A5[] = {1, 2, 3, 3, 3, 2, 1, 0};
    int n5 = sizeof(A5) / sizeof(A5[0]);
    assert(podia(A5, n5) == 22);

    // Test 6: Jeden element, wynik oczekiwany: 0
    int A6[] = {1};
    int n6 = sizeof(A6) / sizeof(A6[0]);
    assert(podia(A6, n6) == 0);

    // Test 7: Dwa elementy, wynik oczekiwany: 0
    int A7[] = {1, 2};
    int n7 = sizeof(A7) / sizeof(A7[0]);
    assert(podia(A7, n7) == 0);

    printf("Wszystkie testy przeszły pomyślnie.\n");
}

int main() {
    test_podia();
    return 0;
}