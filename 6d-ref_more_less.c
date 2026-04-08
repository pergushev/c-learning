#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Функция проверки корректности ввода
int get_valid_number() {
    int num;
    while (1) {
        if (scanf("%d", &num) != 1) {
            printf("Это не число! Попробуй снова: \n");
            while (getchar() != '\n');  // Очистить буфер ввода
            continue;
        }
        if (num < 1 || num > 100500) {
            printf("Число должно быть от 1 до 1000. Попробуй снова: ");
            continue;
        }
        return num;  // Корректное число
    }
}

// Фукция игры
int play_game(int answer) {
    int count = 0;
    int num = 0;

    while (num != answer) {
        printf("Введите ваш вариант: ");
        num = get_valid_number();
        count++;

        if (num > answer) {
            printf("Меньше\n");
        } else if (num < answer) {
            printf("Больше\n");
        }
    }

    return count;
}

int main() {
    srand(time(NULL));
    int answer = rand() % 1000 + 1;  // Число от 1 до 1000
                                     //    int answer = 119;

    printf("Загадано число от 1 до 1000\n");
    int attempts = play_game(answer);

    printf("Ты угадал загаданное число: %d\n", answer);

    if (attempts <= 5) {
        printf("Ты затратил всего %d попыток ты молодец и хорощая бебра!\n", attempts);
    } else {
        printf("Ты затратил целых %d попыток ты какашка и плохая бебра.\n", attempts);
    }

    return 0;
}