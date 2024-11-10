// Podejście nr 1 

int b = 0;
int c = M - 1;

while (b < c) {
    if (kol(b) == 0) {
        ++b;
    } else {
        zam(b, c);
        --c;
    }
}

// Podejście nr 2

int b = 0;
int c = 0;

while (c < M) {
    if (kol(c) == 0) {
        if (b < c) { 
            zam(b, c);
        }
        ++b;
    }
    ++c;
}