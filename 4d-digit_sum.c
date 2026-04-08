#include <stdio.h>

int main() {
    int number = 1234567;
    int sum = 0;
    int temp = number;
    int last_digit = 0;

    while (temp > 0) {
        last_digit = temp % 10;
        sum = sum + last_digit;
        temp = temp / 10;
    }

    printf("Сумма цифр числа %d = %d\n", number, sum);

    return 0;
}