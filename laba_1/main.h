#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

bool is_prime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

void print_array(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void negate_numbers(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = -arr[i];
    }
}

void sort_negatives(int* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] < 0 && arr[j] < 0 && arr[i] < arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int safe_input_int(const char* prompt) {
    int value;
    while (1) {
        printf("%s", prompt);
        if (scanf_s("%d", &value) == 1) {
            break; 
        }
        else {
            printf("Ошибка: введен некорректный символ. Пожалуйста, введите целое число.\n");
            while (getchar() != '\n');
        }
    }
    return value;
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian"); 

    if (argc != 2) {
        printf("Ошибка\n", argv[0]);
        return 1;
    }

    const char* filename = argv[1]; 
    FILE* file;
    int n;

    n = safe_input_int("Введите количество чисел: ");

    int* numbers = (int*)malloc(n * sizeof(int));
    if (numbers == NULL) {
        printf("Ошибка выделения памяти!\n");
        return 1;
    }

    printf("Введите %d целых чисел:\n", n);
    for (int i = 0; i < n; i++) {
        numbers[i] = safe_input_int("");
    }

    errno_t err = fopen_s(&file, filename, "wb");
    if (err != 0) {
        printf("Ошибка открытия файла для записи!\n");
        free(numbers);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        fprintf(file, "%d\n", numbers[i]); 
    }
    fclose(file);

    err = fopen_s(&file, filename, "rb");
    if (err != 0) {
        printf("Ошибка открытия файла для чтения!\n");
        free(numbers);
        return 1;
    }
    
    for (int i = 0; i < n; i++) {
        fscanf_s(file, "%d", &numbers[i]);
    }
    fclose(file);

    printf("Числа из файла:\n");
    print_array(numbers, n);

    int prime_count = 0;
    for (int i = 0; i < n; i++) {
        if (is_prime(numbers[i])) {
            prime_count++;
        }
    }
    printf("Количество простых чисел: %d\n", prime_count);

    negate_numbers(numbers, n);

    err = fopen_s(&file, filename, "wb");
    if (err != 0) {
        printf("Ошибка открытия файла для записи!\n");
        free(numbers);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        fprintf(file, "%d\n", numbers[i]);
    }
    fclose(file);

    printf("Числа после замены знака:\n");
    print_array(numbers, n);

    sort_negatives(numbers, n);

    err = fopen_s(&file, filename, "wb");
    if (err != 0) {
        printf("Ошибка открытия файла для записи!\n");
        free(numbers);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        fprintf(file, "%d\n", numbers[i]);
    }
    fclose(file);

    printf("Отрицательные числа после сортировки по убыванию:\n");
    print_array(numbers, n);

    free(numbers);

    system("pause");
    return 0;
}
