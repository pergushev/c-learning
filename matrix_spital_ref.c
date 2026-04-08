/**
 * @file matrix_spital_ref.c
 * @brief Заполнение матрицы N×N числами от 1 до N² по спирали из центра
 * 
 * Поддерживает два направления: по часовой и против часовой стрелки.
 * Рефакторинг версии 8d-matrix_spiral.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* ==================== Константы ==================== */
#define MIN_MATRIX_SIZE 1
#define DIRECTION_COUNT 4

/* ==================== Типы данных ==================== */
typedef enum {
    CLOCKWISE,
    COUNTER_CLOCKWISE,
    DIRECTION_COUNT_TOTAL
} Direction;

typedef struct {
    int dy;
    int dx;
} DirectionVector;

/* ==================== Прототипы функций ==================== */
/* Ввод данных */
static int input_n(void);
static Direction input_direction(void);

/* Работа с матрицей */
static int **allocate_matrix(int n);
static void free_matrix(int **matrix, int n);
static void get_start_position(int n, Direction dir, int *row, int *col);

/* Алгоритм заполнения */
static void fill_spiral(int **matrix, int n, Direction dir);
static DirectionVector get_direction_vector(Direction dir, int step);

/* Вывод */
static void print_matrix(const int **matrix, int n);
static int calculate_field_width(int max_value);

/* ==================== Основная функция ==================== */
int main(void) {
    int n = input_n();
    Direction dir = input_direction();

    int **matrix = allocate_matrix(n);
    if (!matrix) {
        fprintf(stderr, "Ошибка: недостаточно памяти\n");
        return EXIT_FAILURE;
    }

    fill_spiral(matrix, n, dir);
    print_matrix((const int **)matrix, n);

    free_matrix(matrix, n);
    return EXIT_SUCCESS;
}

/* ==================== Функции ввода ==================== */
static int input_n(void) {
    int n;
    bool is_valid = false;
    
    while (!is_valid) {
        printf("Введите размер матрицы N (N > 0): ");

        if (scanf("%d", &n) != 1) {
            while (getchar() != '\n');
            printf("Ошибка: введите целое число\n");
        } else if (n < MIN_MATRIX_SIZE) {
            printf("Ошибка: N должно быть больше 0\n");
        } else {
            is_valid = true;
        }
    }
    return n;
}

static Direction input_direction(void) {
    int choice;
    bool is_valid = false;

    while (!is_valid) {
        printf("Выберите направление обхода:\n");
        printf("  1 - По часовой стрелке\n");
        printf("  2 - Против часовой стрелки\n");
        printf("Ваш выбор: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Ошибка: введите 1 или 2\n");
        } else if (choice == 1) {
            return CLOCKWISE;
        } else if (choice == 2) {
            return COUNTER_CLOCKWISE;
        } else {
            printf("Ошибка: введите 1 или 2\n");
        }
    }
    
    return CLOCKWISE; /* По умолчанию, никогда не достигается */
}

/* ==================== Работа с матрицей ==================== */
static int **allocate_matrix(int n) {
    int **matrix = (int **)malloc(n * sizeof(int *));
    if (!matrix) {
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)calloc(n, sizeof(int));
        if (!matrix[i]) {
            /* Освобождаем ранее выделенную память при ошибке */
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }
    }
    return matrix;
}

static void free_matrix(int **matrix, int n) {
    if (!matrix) return;
    
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

static void get_start_position(int n, Direction dir, int *row, int *col) {
    *row = n / 2;

    /* Для чётных N центр смещается */
    if (dir == CLOCKWISE) {
        *col = (n % 2 == 0) ? (n / 2 - 1) : (n / 2);
    } else {
        *col = n / 2;
    }
}

/* ==================== Алгоритм заполнения ==================== */
static DirectionVector get_direction_vector(Direction dir, int step) {
    /* 
     * Направления: 0-вверх, 1-вправо/влево, 2-вниз, 3-влево/вправо
     * По часовой:    вверх, вправо, вниз, влево
     * Против часовой: вверх, влево, вниз, вправо
     */
    static const int dy[DIRECTION_COUNT] = {-1, 0, 1, 0};
    static const int dx_cw[DIRECTION_COUNT] = {0, 1, 0, -1};
    static const int dx_ccw[DIRECTION_COUNT] = {0, -1, 0, 1};
    
    DirectionVector result;
    result.dy = dy[step];
    result.dx = (dir == CLOCKWISE) ? dx_cw[step] : dx_ccw[step];
    
    return result;
}

static void fill_spiral(int **matrix, int n, Direction dir) {
    int row, col;
    get_start_position(n, dir, &row, &col);

    matrix[row][col] = 1;

    int direction_step = 0;      /* Текущее направление (0-3) */
    int steps_in_direction = 1;  /* Количество шагов в текущем направлении */
    int current_value = 2;       /* Следующее значение для записи */
    int turn_count = 0;          /* Счётчик поворотов */

    while (current_value <= n * n) {
        DirectionVector move = get_direction_vector(dir, direction_step);
        
        /* Делаем steps_in_direction шагов в текущем направлении */
        for (int i = 0; i < steps_in_direction && current_value <= n * n; i++) {
            row += move.dy;
            col += move.dx;
            matrix[row][col] = current_value++;
        }
        
        /* Поворот по часовой стрелке */
        direction_step = (direction_step + 1) % DIRECTION_COUNT;
        turn_count++;
        
        /* Увеличиваем количество шагов после каждых 2 поворотов */
        if (turn_count % 2 == 0) {
            steps_in_direction++;
        }
    }
}

/* ==================== Вывод ==================== */
static int calculate_field_width(int max_value) {
    int width = 1;
    while (max_value >= 10) {
        max_value /= 10;
        width++;
    }
    return width + 1; /* Дополнительный пробел между числами */
}

static void print_matrix(const int **matrix, int n) {
    int max_value = n * n;
    int field_width = calculate_field_width(max_value);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%*d", field_width, matrix[i][j]);
        }
        printf("\n");
    }
}
