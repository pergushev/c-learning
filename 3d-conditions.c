#include <stdio.h>

int main() {
    int age = 18;
    int temperature = 0;
    int score = 85;
    int has_license = 1;

    if (age >= 18) {
        printf("Вам разрешено голосовать!\n");
    }

    if (temperature > 0) {
        printf("На улице тепло, %d градусов\n", temperature);
    } else {
        printf("На улице холодно, %d градусов\n", temperature);
    }

    if (score >= 90) {
        printf("Оценка: Отлично (5)\n");
    } else if (score >= 75) {
        printf("Оценка: Хорошо (4)\n");
    } else if (score >= 60) {
        printf("Оценка: Удовлетворительно (3)\n");
    } else {
        printf("Оценка: Неудовлетворительно (2)\n");
    }

    age = 20;

    if (age >= 18 && has_license == 1) {
        printf("Можно водить машину\n");
    } else {
        printf("Нельзя водить машину\n");
    }

    return 0;
}