/**
 * @file matrix_spiral_ref_2.c
 * @brief Заполнение матрицы N×N числами от 1 до N² по спирали из центра
 *
 * Поддерживает два направления: по часовой и против часовой стрелки.
 * Режимы работы:
 *   - Интерактивный (без аргументов)
 *   - Командная строка: ./program <N> <direction> [output_file]
 *
 * Аргументы:
 *   N          - размер матрицы (целое число > 0)
 *   direction  - направление: "cw" (по часовой) или "ccw" (против часовой)
 *   output_file - опционально, файл для вывода (по умолчанию stdout)
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

/* ==================== Константы ==================== */
#define MIN_MATRIX_SIZE 1
#define DIRECTION_COUNT 4
#define MAX_FILENAME_LENGTH 256
#define DIRECTION_CW_STR "cw"
#define DIRECTION_CCW_STR "ccw"

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

typedef struct {
    int n;
    Direction dir;
    bool use_file;
    char filename[MAX_FILENAME_LENGTH];
} ProgramConfig;

typedef enum {
    MODE_INTERACTIVE,
    MODE_CLI
} ProgramMode;

/* ==================== Прототипы функций ==================== */
/* Конфигурация и аргументы */
static ProgramMode detect_mode(int argc, char *argv[]);
static bool parse_arguments(int argc, char *argv[], ProgramConfig *config);
static void print_usage(const char *program_name);

/* Ввод данных (интерактивный режим) */
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
static void print_matrix_to_stream(const int **matrix, int n, FILE *stream);
static int calculate_field_width(int max_value);

/* ==================== Основная функция ==================== */
int main(int argc, char *argv[]) {
    ProgramConfig config;
    ProgramMode mode = detect_mode(argc, argv);

    /* Получение конфигурации */
    if (mode == MODE_CLI) {
        if (!parse_arguments(argc, argv, &config)) {
            return EXIT_FAILURE;
        }
    } else {
        config.n = input_n();
        config.dir = input_direction();
        config.use_file = false;
    }

    /* Выделение памяти */
    int **matrix = allocate_matrix(config.n);
    if (!matrix) {
        fprintf(stderr, "Ошибка: недостаточно памяти\n");
        return EXIT_FAILURE;
    }

    /* Заполнение спирали */
    fill_spiral(matrix, config.n, config.dir);

    /* Вывод результата */
    FILE *output = stdout;
    if (config.use_file) {
        output = fopen(config.filename, "w");
        if (!output) {
            fprintf(stderr, "Ошибка: не удалось открыть файл '%s' для записи: %s\n",
                    config.filename, strerror(errno));
            free_matrix(matrix, config.n);
            return EXIT_FAILURE;
        }
    }

    print_matrix_to_stream((const int **)matrix, config.n, output);

    if (config.use_file) {
        fclose(output);
        printf("Результат сохранён в файл: %s\n", config.filename);
    }

    free_matrix(matrix, config.n);
    return EXIT_SUCCESS;
}

/* ==================== Конфигурация и аргументы ==================== */
static ProgramMode detect_mode(int argc, char *argv[]) {
    (void)argv; /* Подавление предупреждения о неиспользуемом параметре */
    return (argc >= 3) ? MODE_CLI : MODE_INTERACTIVE;
}

static void print_usage(const char *program_name) {
    fprintf(stderr, "Использование:\n");
    fprintf(stderr, "  %s <N> <direction> [output_file]\n\n", program_name);
    fprintf(stderr, "Аргументы:\n");
    fprintf(stderr, "  N           - размер матрицы (целое число > 0)\n");
    fprintf(stderr, "  direction   - направление обхода:\n");
    fprintf(stderr, "                  cw  - по часовой стрелке\n");
    fprintf(stderr, "                  ccw - против часовой стрелки\n");
    fprintf(stderr, "  output_file - опционально, файл для вывода результата\n\n");
    fprintf(stderr, "Примеры:\n");
    fprintf(stderr, "  %s 5 cw              - матрица 5x5 по часовой в stdout\n", program_name);
    fprintf(stderr, "  %s 4 ccw result.txt  - матрица 4x4 против часовой в файл\n", program_name);
    fprintf(stderr, "  %s                   - интерактивный режим\n", program_name);
}

static bool parse_direction_arg(const char *arg, Direction *dir) {
    if (strcmp(arg, DIRECTION_CW_STR) == 0) {
        *dir = CLOCKWISE;
        return true;
    } else if (strcmp(arg, DIRECTION_CCW_STR) == 0) {
        *dir = COUNTER_CLOCKWISE;
        return true;
    }
    return false;
}

static bool parse_int_arg(const char *arg, int *value) {
    char *endptr;
    errno = 0;
    long val = strtol(arg, &endptr, 10);

    if (errno != 0 || *endptr != '\0' || endptr == arg) {
        return false;
    }

    *value = (int)val;
    return true;
}

static bool parse_arguments(int argc, char *argv[], ProgramConfig *config) {
    /* Парсинг размера матрицы */
    if (!parse_int_arg(argv[1], &config->n)) {
        fprintf(stderr, "Ошибка: некорректный размер матрицы '%s'\n", argv[1]);
        print_usage(argv[0]);
        return false;
    }

    if (config->n < MIN_MATRIX_SIZE) {
        fprintf(stderr, "Ошибка: размер матрицы должен быть > 0\n");
        print_usage(argv[0]);
        return false;
    }

    /* Парсинг направления */
    if (!parse_direction_arg(argv[2], &config->dir)) {
        fprintf(stderr, "Ошибка: некорректное направление '%s'\n", argv[2]);
        fprintf(stderr, "Допустимые значения: cw, ccw\n");
        print_usage(argv[0]);
        return false;
    }

    /* Парсинг имени файла (опционально) */
    config->use_file = (argc >= 4);
    if (config->use_file) {
        if (strlen(argv[3]) >= MAX_FILENAME_LENGTH) {
            fprintf(stderr, "Ошибка: имя файла слишком длинное\n");
            return false;
        }
        strncpy(config->filename, argv[3], MAX_FILENAME_LENGTH - 1);
        config->filename[MAX_FILENAME_LENGTH - 1] = '\0';
    }

    return true;
}

/* ==================== Функции ввода (интерактивный режим) ==================== */
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
        printf("  1 - По часовой стрелке (cw)\n");
        printf("  2 - Против часовой стрелки (ccw)\n");
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

static void print_matrix_to_stream(const int **matrix, int n, FILE *stream) {
    int max_value = n * n;
    int field_width = calculate_field_width(max_value);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(stream, "%*d", field_width, matrix[i][j]);
        }
        fprintf(stream, "\n");
    }
}
