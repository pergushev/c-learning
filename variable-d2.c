#include <stdio.h>

int main() {
    int age = 25;
    float height = 1.75;
    char inital = 'A';
    double pi = 3.1415926535;

    // Вывод разных типов
    printf("Возраст: %d лет\n", age);
    printf("Рост: %.2f м\n", height);  // %.2f - 2 знака после зваятой
    printf("Инициал: %c\n", inital);
    printf("Число Пи: %.10f\n", pi);  // 10 знаков после запятой

    return 0;
}
