#include <stdio.h>

int main() {
    int i = 1;

    while (i <= 5) {
        printf("Итерация %d\n", i);
        i = i + 1;
    }

    for (int j = 1; j <= 5; j = j + 1) {
        printf("Итерация %d\n", j);
    }

    for (int k = 1; k <= 10; k++) {
        if (k == 6) {
            break;
        }
        printf("%d ", k);
    }
    printf("\n");

    for (int l = 1; l <= 10; l++) {
        if (l % 2 == 0) {
            continue;
        }
        printf("%d ", l);
    }
    printf("\n");

    return 0;
}