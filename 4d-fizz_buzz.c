#include <stdio.h>

int main() {
    for (int num = 1; num <= 100; num++) {
        if (num % 3 == 0) {
            printf("Fizz ");
            continue;
        } else if (num % 5 == 0) {
            printf("Buzz ");
            continue;
        } else if (num % 15 == 0) {
            printf("FizzBuzz ");
            continue;
        }
        printf("%d ", num);
    }

    printf("\n");

    return 0;
}