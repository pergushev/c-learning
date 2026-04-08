#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int num = 0;
    srand(time(NULL));
    int answer = rand() % 1000 + 1;  // Число от 1 до 1000
    int count = 0;

    printf("Загадано число от 1 до 1000\n");

    while (num != answer) {
        printf("Введите ваш вариант: ");
        count++;

        if (scanf("%d", &num) != 1) {
            printf("Это не число! \n");
            while (getchar() != '\n');  // Очистить буфер ввода
            count--;
            continue;
        }

        if (num < 1 || num > 1000) {
            printf("Число должно быть от 1 до 1000. Тупая ты бебра!!!");
            count--;
            continue;
        }

        if (num > answer) {
            printf("Меньше\n");
        } else if (num < answer) {
            printf("Больше\n");
        }
    }

    printf("Ты угадал загаданное число: %d\n", num);

    if (count <= 5) {
        printf("Ты затратил всего %d попыток ты молодец и хорощая бебра!\n", count);
    } else {
        printf("Ты затратил целых %d попыток ты какашка и плохая бебра.\n", count);
    }

    return 0;
}