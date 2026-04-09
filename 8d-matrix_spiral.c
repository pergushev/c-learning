#include <stdio.h>
#include <stdlib.h>

typedef enum {
    CLOCKWISE,
    COUNTER_CLOCKWISE
} Direction;

int input_n(void);
Direction input_direction(void);
void get_center(int n, Direction dir, int *row, int *col);
int **allocate_matrix(int n);
void free_matrix(int **matrix, int n);
void fill_spiral(int **matrix, int n, Direction dir);
void print_matrix(int **matrix, int n);

int main(void) {
    int n = input_n();
    Direction dir = input_direction();

    int **matrix = allocate_matrix(n);
    if (!matrix) {
        fprintf(stderr, "Ошибка: недостаточно памяти\n");
        return 1;
    }

    fill_spiral(matrix, n, dir);
    print_matrix(matrix, n);

    free_matrix(matrix, n);
    return 0;
}

int input_n(void) {
    int n;
    int is_valid = 0;
    while (!is_valid) {
        printf("Введите размер матрицы N (N > 0): ");

        if (scanf("%d", &n) != 1) {
            while (getchar() != '\n');
            printf("Ошибка: введите целое число\n");
        } else if (n <= 0) {
            printf("Ошибка: N должно быть больше 0\n");
        } else {
            is_valid = 1;
        } 
    }
    return n;
}

Direction input_direction(void) {
    int choice = 0;
    int is_valid = 0;
    Direction result = CLOCKWISE;

    while (!is_valid) {
        printf("Выберите направление обхода:\n");
        printf("  1 - По часовой стрелке\n");
        printf("  2 - Против часовой стрелки\n");
        printf("Ваш выбор: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Ошибка: введите 1 или 2\n");
        } else if (choice == 1) {
            result = CLOCKWISE;
            is_valid = 1;
        } else if (choice == 2) {
            result = COUNTER_CLOCKWISE;
            is_valid = 1;
        } else {
            printf("Ошибка: введите 1 или 2\n");
        }
    }

    return result;
    
}

void get_center(int n, Direction dir, int *row, int *col) {
    *row = n / 2;

    if (dir == CLOCKWISE) {
        *col = (n % 2 == 0) ? (n / 2 - 1) : (n / 2);
    } else {
        *col = (n % 2 == 0) ? (n / 2) : (n / 2);
    }
}

int **allocate_matrix(int n) {
    // Выделяем массив из n указателей на строки
    int **m = (int **)malloc(n * sizeof(int *));
    if (!m) return NULL;

    for (int i = 0; i < n; i++) {
        *(m + i) = (int *)calloc(n, sizeof(int));

        if (!*(m + i)) {
            // Освобождаем уже выделенное при ошибке
            while (i--) free(*(m + i));
            free(m);
            return NULL;
        }
    }
    return m;
}

void free_matrix(int **m, int n) {
    for (int i = 0; i < n; i++) {
        free(*(m + i));
    }
    free(m);
}

void fill_spiral(int **m, int n, Direction dir) {
    // по часовой       dy/dx: вверх, вправо, вниз, влево
    // против часовой   dy/dx: вверх, влево, вниз, вправо
    int dy[] = {-1, 0, 1, 0};
    int dx_cw[] = {0, 1, 0, -1};
    int dx_ccw[] = {0, -1, 0, 1};
    int *dx = (dir == CLOCKWISE) ? dx_cw : dx_ccw;

    int row, col;

    get_center(n, dir, &row, &col);

    // Устанавливаем первый элемент через указатель
    *(*(m + row) + col) = 1;

    int d = 0;    // начинаем вверх
    int steps = 1;   // шагов в теккущем направлении
    int count = 2;  // следующее значение
    int turns = 0;  // счётчик поворотов

    while (count <= n * n) {
        // Делаем 'steps' шагов в направлении dir
        for (int i = 0; i < steps && count <= n * n; i++) {
            row += dy[d];
            col += dx[d];
            *(*(m + row) + col) = count++;
        }
        turns++;
        d = (d + 1) % 4; // поворот по часовой
        // После каждых 2 поворотов увеличиваем шаг
        if (turns % 2 == 0) steps++;
    }
}

void print_matrix(int **m, int n) {
    // Вычисляем ширину поля для выравнивания
    int max_val = n * n;
    int width = 1;
    while (max_val >= 10) {
        max_val /= 10;
        width++;
    }
    width++;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%*d", width, *(*(m + i) + j));
        }
        printf("\n");
    }
}
