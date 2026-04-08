#include <stdio.h>

int main() {
    float weight = 86;
    float height = 1.76;
    float imt = weight / (height * height);

    printf("Ваш ИМТ: %.1f\n", imt);

    if (imt >= 30) {
        printf("Категория: Ожирение\n");
    } else if (imt >= 25 && imt < 30) {
        printf("Категория: Избыточный вес\n");
    } else if (imt >= 18.5 && imt < 25) {
        printf("Категория: Нормальный вес\n");
    } else {
        printf("Категория: Недостаточный вес\n");
    }

    return 0;
}