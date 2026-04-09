#include <stdio.h>

int main() {
    int a = 10, b = 3;
    printf("a + b = %d\n", a + b);   // 13
    printf("a - b = %d\n", a - b);   // 7
    printf("a * b = %d\n", a * b);   // 30
    printf("a / b = %d\n", a / b);   // 3 (целочисленое деление)
    printf("a %% b = %d\n", a % b);  // 1 (остаток от деления)

    // Для дробных чисел
    float x = 10.0f, y = 3.0f;
    printf("x / y = %.2f\n", x / y);  // 3.33

    a = 15;
    b = 4;

    printf("a / b = %.2f\n", (float)a / b);

    return 0;
}