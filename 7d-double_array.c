#include <stdio.h>

#define MAX_SIZE 100
#define ERROR_CODE -1

int read_array(int arr[], int size);
void double_array(int arr[], int max_size);
void print_array(int arr[], int size);


int main(void) {
    
    int arr[MAX_SIZE] = {0};
    int size = read_array(arr, MAX_SIZE);
    if (size == ERROR_CODE || size == 0) {
        printf("n/a");
    } else {
        double_array(arr, size);
        print_array(arr, size);
    }

    return 0;
}

int read_array(int arr[], int max_size) {
    int status = 1;
    int i = 0;

    while(i < max_size && status) {
        int result = scanf("%d", &arr[i]);
        if (result == 0) {
            status = 0;
            i = ERROR_CODE;
        } else if (result == EOF) {
            status = 0;
        } else {
            i++;
        }
    }
    return i;
}

void double_array(int arr[], int size) {
    int i = 0;
    while (i < size) {
        arr[i] = 2 * arr[i];
        i++;
    }
}

void print_array(int arr[], int size) {
    int i = 0;
    while (i < size) {
        if (i != 0) {
            printf(" %d", arr[i]);
        } else {
            printf("%d", arr[i]);
        }
        i++;
    }
    printf("\n");
}