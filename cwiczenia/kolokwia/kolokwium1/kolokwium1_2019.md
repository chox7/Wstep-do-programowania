# Zadanie 1 

```c
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

    bool stala = false;
    int pary = 0;
    while (!stala) {
        pary += (i+1) * (n-j)
        if (A[i+1] > A[j-1]) {
            j--;
        } else if (A[i+1] < A[j-1]) {
            i++;
        } else {
            stala = true; 
        }
    }

    pary += (i+1) * (n-j) * (j-i-1);
    return pary;
}
```