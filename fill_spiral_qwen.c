#include <stdio.h>

#define N 4  // Меняйте на 1, 2, 3, 5 и т.д.

int main() {
    int matrix[N][N] = {0};

    // Определяем центр (для чётных и нечётных N)
    int x = N / 2;
    int y = N / 2;
    if (N % 2 == 0) {
        x--;  // Для чётных N: левый верхний из 4 центральных элементов
        y--;
    }

    int num = 1;
    int step_size = 1;
    int direction = 0;  // 0=вправо, 1=вниз, 2=влево, 3=вверх
    int dir_changes = 0;

    // Заполняем центр
    matrix[x][y] = num++;

    // Заполняем спиралью
    while (num <= N * N) {
        for (int i = 0; i < step_size && num <= N * N; i++) {
            // Двигаемся в текущем направлении
            switch (direction) {
                case 0:
                    y++;
                    break;  // вправо
                case 1:
                    x++;
                    break;  // вниз
                case 2:
                    y--;
                    break;  // влево
                case 3:
                    x--;
                    break;  // вверх
            }

            // 🔒 КРИТИЧЕСКАЯ ПРОВЕРКА ГРАНИЦ
            if (x < 0 || x >= N || y < 0 || y >= N) {
                printf("Ошибка: выход за границы на числе %d!\n", num);
                return 1;
            }

            matrix[x][y] = num++;
        }

        // Меняем направление
        direction = (direction + 1) % 4;
        dir_changes++;

        // Увеличиваем шаг после каждых 2 направлений
        if (dir_changes % 2 == 0) {
            step_size++;
        }
    }

    // Вывод матрицы
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}