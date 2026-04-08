/**
 * @file 9d-student_struct.c
 * @brief База данных студентов с динамическим массивом
 *
 * Использует динамическое выделение памяти с автоматическим
 * увеличением ёмкости через realloc при переполнении.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* ==================== Константы ==================== */
#define MAX_NAME 50
#define FILENAME "students.dat"
#define INITIAL_CAPACITY 10
#define GROWTH_FACTOR 2

/* ==================== Структуры ==================== */
struct Student {
    char name[MAX_NAME];
    int age;
    float gpa;
};

typedef struct {
    struct Student *data;
    int count;
    int capacity;
} StudentArray;

/* ==================== Прототипы функций ==================== */
/* Утилиты */
static void clear_input_buffer(void);
static bool ensure_capacity(StudentArray *arr);

/* Операции со студентами */
static void add_student(StudentArray *arr);
static int find_by_name(const StudentArray *arr, const char *name);
static void find_and_print(StudentArray *arr);
static void del_student(StudentArray *arr);
static void print_students(const StudentArray *arr);

/* Работа с файлами */
static void save_to_file(const StudentArray *arr);
static int load_from_file(StudentArray *arr);

/* Память */
static StudentArray create_array(int initial_capacity);
static void free_array(StudentArray *arr);

/* ==================== Основная функция ==================== */
int main(void) {
    StudentArray students = create_array(INITIAL_CAPACITY);

    students.count = load_from_file(&students);

    int choice;

    do {
        printf("\n=== МЕНЮ ===\n");
        printf("1. Добавить студента\n");
        printf("2. Показать всех студентов\n");
        printf("3. Найти студента по имени\n");
        printf("4. Удалить студента\n");
        printf("5. Сохранить и выйти\n");
        printf("Ваш выбор: ");
        scanf("%d", &choice);
        clear_input_buffer();

        switch (choice) {
            case 1: add_student(&students); break;
            case 2: print_students(&students); break;
            case 3: find_and_print(&students); break;
            case 4: del_student(&students); break;
            case 5: save_to_file(&students); break;
            default: printf("❌ Неверный выбор!\n");
        }
    } while (choice != 5);

    printf("👋 До свидания!\n");

    free_array(&students);
    return 0;
}

/* ==================== Управление памятью ==================== */
static StudentArray create_array(int initial_capacity) {
    StudentArray arr;
    arr.count = 0;
    arr.capacity = initial_capacity;
    arr.data = (struct Student *)malloc(initial_capacity * sizeof(struct Student));

    if (!arr.data) {
        fprintf(stderr, "❌ Ошибка выделения памяти\n");
        exit(EXIT_FAILURE);
    }

    return arr;
}

static void free_array(StudentArray *arr) {
    if (arr && arr->data) {
        free(arr->data);
        arr->data = NULL;
        arr->count = 0;
        arr->capacity = 0;
    }
}

static bool ensure_capacity(StudentArray *arr) {
    if (arr->count < arr->capacity) {
        return true; /* Есть свободное место */
    }

    int new_capacity = arr->capacity * GROWTH_FACTOR;
    struct Student *new_data = (struct Student *)realloc(arr->data,
                                                          new_capacity * sizeof(struct Student));

    if (!new_data) {
        fprintf(stderr, "❌ Ошибка увеличения ёмкости\n");
        return false;
    }

    arr->data = new_data;
    arr->capacity = new_capacity;
    printf("📈 Ёмкость увеличена до %d\n", new_capacity);
    return true;
}

/* ==================== Утилиты ==================== */
static void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* ==================== Операции со студентами ==================== */
static void add_student(StudentArray *arr) {
    if (!ensure_capacity(arr)) {
        printf("❌ Не удалось добавить студента\n");
        return;
    }

    struct Student new_student;

    printf("Имя: ");
    scanf("%49s", new_student.name);
    clear_input_buffer();

    printf("Возраст: ");
    scanf("%d", &new_student.age);
    clear_input_buffer();

    printf("Средний балл: ");
    scanf("%f", &new_student.gpa);
    clear_input_buffer();

    arr->data[arr->count] = new_student;
    arr->count++;
    printf("✅ Студент добавлен!\n");
}

static int find_by_name(const StudentArray *arr, const char *name) {
    for (int i = 0; i < arr->count; i++) {
        if (strcmp(arr->data[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

static void find_and_print(StudentArray *arr) {
    if (arr->count == 0) {
        printf("📭 База пуста, некого искать\n");
        return;
    }

    char name[MAX_NAME];
    printf("Введите имя для поиска: ");
    scanf("%49s", name);
    clear_input_buffer();

    int index = find_by_name(arr, name);

    if (index >= 0) {
        printf("✅ Найден: %d. %s, %d лет, бал: %.2f\n",
               index + 1, arr->data[index].name, arr->data[index].age, arr->data[index].gpa);
    } else {
        printf("❌ Студент '%s' не найден\n", name);
    }
}

static void del_student(StudentArray *arr) {
    if (arr->count == 0) {
        printf("📭 База пуста, некого удалять\n");
        return;
    }

    int index;
    printf("\nНомер студента для удаления: ");
    scanf("%d", &index);
    clear_input_buffer();

    /* Проверка корректности номера (1-based индекс) */
    if (index < 1 || index > arr->count) {
        printf("❌ Неверный номер: должно быть от 1 до %d\n", arr->count);
        return;
    }

    /* Сдвиг элементов влево (index - 1, т.к. ввод 1-based) */
    int shift_index = index - 1;
    for (int i = shift_index; i < arr->count - 1; i++) {
        arr->data[i] = arr->data[i + 1];
    }
    arr->count--;
    printf("✅ Студент #%d удалён\n", index);
}

/* ==================== Вывод ==================== */
static void print_students(const StudentArray *arr) {
    if (arr->count == 0) {
        printf("📭 База пуста\n");
        return;
    }

    printf("\n=== СПИСОК СТУДЕНТОВ ===\n");
    printf("Ёмкость: %d, Записей: %d\n", arr->capacity, arr->count);
    for (int i = 0; i < arr->count; i++) {
        printf("%d. %s, %d лет, бал: %.2f\n",
               i + 1, arr->data[i].name, arr->data[i].age, arr->data[i].gpa);
    }
}

/* ==================== Работа с файлами ==================== */
static void save_to_file(const StudentArray *arr) {
    FILE *file = fopen(FILENAME, "wb");
    if (file == NULL) {
        perror("❌ Ошибка открытия файла");
        return;
    }

    fwrite(&arr->count, sizeof(int), 1, file);
    fwrite(arr->data, sizeof(struct Student), arr->count, file);

    fclose(file);
    printf("💾 Данные сохранены в %s\n", FILENAME);
}

static int load_from_file(StudentArray *arr) {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("📭 Файл не найден - создаем новую базу\n");
        return 0;
    }

    int count = 0;
    if (fread(&count, sizeof(int), 1, file) != 1) {
        fclose(file);
        return 0;
    }

    /* Проверяем, хватает ли ёмкости */
    if (count > arr->capacity) {
        struct Student *new_data = (struct Student *)realloc(arr->data,
                                                              count * sizeof(struct Student));
        if (!new_data) {
            perror("❌ Ошибка выделения памяти");
            fclose(file);
            return 0;
        }
        arr->data = new_data;
        arr->capacity = count;
    }

    if (fread(arr->data, sizeof(struct Student), count, file) != (size_t)count) {
        perror("❌ Ошибка чтения данных");
        fclose(file);
        return 0;
    }

    fclose(file);
    printf("✅ Загружено %d студентов из %s\n", count, FILENAME);
    return count;
}
