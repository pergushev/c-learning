#include <stdio.h>

void fillSpiralFromCenter(int n, int arr[n][n]) {
    // Инициализируем массив нулями
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            arr[i][j] = 0;
        }
    }

    // Находим центр (для чётных - левый верхний из 4 центральных)
    int row = (n - 1) / 2;
    int col = (n - 1) / 2;

    arr[row][col] = 1;
    int num = 2;

    // Направления: вправо, вниз, влево, вверх
    int dr[] = {0, 1, 0, -1};
    int dc[] = {1, 0, -1, 0};
    int dir = 0;  // Начинаем с движения вправо

    int steps = 1;  // Количество шагов в текущем направлении

    while (num <= n * n) {
        for (int repeat = 0; repeat < 2; repeat++) {  // Два направления с одинаковым количеством шагов
            for (int step = 0; step < steps; step++) {
                row += dr[dir];
                col += dc[dir];

                if (row >= 0 && row < n && col >= 0 && col < n) {
                    arr[row][col] = num++;
                }

                if (num > n * n) return;
            }
            dir = (dir + 1) % 4;  // Поворот по часовой стрелке
        }
        steps++;  // Увеличиваем количество шагов после каждых двух поворотов
    }
}

void printArray(int n, int arr[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%3d ", arr[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Нечётный размер 3×3
    printf("Массив 3×3 (центр [1][1]):\n");
    int n1 = 3;
    int matrix1[n1][n1];
    fillSpiralFromCenter(n1, matrix1);
    printArray(n1, matrix1);

    printf("\n");

    // Чётный размер 4×4
    printf("Массив 4×4 (центр [1][1] - левый верхний из 4):\n");
    int n2 = 4;
    int matrix2[n2][n2];
    fillSpiralFromCenter(n2, matrix2);
    printArray(n2, matrix2);

    printf("\n");

    // Нечётный размер 5×5
    printf("Массив 5×5 (центр [2][2]):\n");
    int n3 = 5;
    int matrix3[n3][n3];
    fillSpiralFromCenter(n3, matrix3);
    printArray(n3, matrix3);

    printf("\n");

    // Чётный размер 6×6
    printf("Массив 6×6 (центр [2][2] - левый верхний из 4):\n");
    int n4 = 6;
    int matrix4[n4][n4];
    fillSpiralFromCenter(n4, matrix4);
    printArray(n4, matrix4);

    return 0;
}
