#include <stdio.h>

float add(float a, float b);
float subtract(float a, float b);
float multiply(float a, float b);
float divide(float a, float b);
int is_division_safe(float b);
void print_menu();

int main() {
    int choice;
    float a, b, result;

    while (1) {
        print_menu();
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');  // Очистить буфер ввода
            printf("Введите число!\n");
            continue;
        }

        if (choice == 0) break;

        printf("Введите два числа: ");
        if (scanf("%f %f", &a, &b) != 2) {
            while (getchar() != '\n');  // Очистить буфер ввода
            printf("Ошибка ввода чисел!\n");
            continue;
        }

        if (choice == 4 && !is_division_safe(b)) {
            continue;
        }

        switch (choice) {
            case 1:
                result = add(a, b);
                break;
            case 2:
                result = subtract(a, b);
                break;
            case 3:
                result = multiply(a, b);
                break;
            case 4:
                result = divide(a, b);
                break;
            default:
                printf("Неверный выбор!\n");
                continue;
        }

        printf("Результат: %.2f\n\n", result);
    }

    printf("До свидвния!\n");
    return 0;
}

void print_menu() {
    printf("\n=== КАЛЬКУЛЯТОР ===\n");
    printf("1. Сложить\n");
    printf("2. Вычесть\n");
    printf("3. Умножить\n");
    printf("4. Разделить\n");
    printf("0. Выйти\n");
    printf("Ваш выбор: ");
}

int is_division_safe(float b) {
    if (b == 0.0f) {
        printf("❌ Ошибка: деление на ноль запрещено!\n");
        return 0;
    }
    return 1;
}

float add(float a, float b) { return a + b; }

float subtract(float a, float b) { return a - b; }

float multiply(float a, float b) { return a * b; }

float divide(float a, float b) { return a / b; }