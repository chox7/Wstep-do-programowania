int c = 0;
int b = 0;
int n = N - 1;

while (b < n) {
    if (kol(b) == 1) {
        ++b;
    } else if (kol(b) == 0) {
        if (c < b) {
            zam(c, b);
        }
        ++b;
        ++c;
    } else {
        zam(b, n);
        --n;
    }
}