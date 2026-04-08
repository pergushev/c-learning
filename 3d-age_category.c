#include <stdio.h>

int main() {
    int age = 25;

    if (age < 13) {
        printf("Ребёнок\n");
    } else if (age >= 13 && age < 18) {
        printf("Подросток\n");
    } else if (age >= 18 && age < 65) {
        printf("Взрослый\n");
    } else {
        printf("Пенсионер\n");
    }

    return 0;
}