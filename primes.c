#include <stdio.h>

int main() {
    for (int num = 2; num <= 100; num++) {
        int is_prime = 1;  // Предпологаем что число простое

        for (int div = 2; div * div <= num; div++) {
            if (num % div == 0) {
                is_prime = 0;  // Нашли делитель --> не простое
                break;
            }
        }

        if (is_prime) {
            printf("%d ", num);
        }
    }
    printf("\n");
    return 0;
}