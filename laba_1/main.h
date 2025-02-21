#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

// Функция для проверки, является ли число простым
bool is_prime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// Функция для вывода массива на экран
void print_array(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Функция для замены знака каждого числа на противоположный
void negate_numbers(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = -arr[i];
    }
}

// Функция для сортировки отрицательных чисел по убыванию
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

// Функция для безопасного ввода целого числа
int safe_input_int(const char* prompt) {
    int value;
    while (1) {
        printf("%s", prompt);
        if (scanf_s("%d", &value) == 1) {
            break; // Ввод корректен, выходим из цикла
        }
        else {
            printf("Ошибка: введен некорректный символ. Пожалуйста, введите целое число.\n");
            // Очистка буфера ввода
            while (getchar() != '\n'); // Удаляем все символы до конца строки
        }
    }
    return value;
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian"); // Для поддержки русского языка

    if (argc != 2) {
        printf("Нету памяти\n", argv[0]);
        return 1;
    }

    const char* filename = argv[1]; // Путь к текстовому файлу
    FILE* file;
    int n;

    // Ввод количества чисел с проверкой
    n = safe_input_int("Введите количество чисел: ");

    int* numbers = (int*)malloc(n * sizeof(int));
    if (numbers == NULL) {
        printf("Ошибка выделения памяти!\n");
        return 1;
    }

    // Ввод чисел с проверкой
    printf("Введите %d целых чисел:\n", n);
    for (int i = 0; i < n; i++) {
        numbers[i] = safe_input_int("");
    }

    // Открываем файл для записи
    errno_t err = fopen_s(&file, filename, "wb");
    if (err != 0) {
        printf("Ошибка открытия файла для записи!\n");
        free(numbers);
        return 1;
    }

    // Записываем числа в файл
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d\n", numbers[i]); // Каждое число на новой строке
    }
    fclose(file);

    // Открываем файл для чтения
    err = fopen_s(&file, filename, "rb");
    if (err != 0) {
        printf("Ошибка открытия файла для чтения!\n");
        free(numbers);
        return 1;
    }

    // Считываем числа из файла
    for (int i = 0; i < n; i++) {
        fscanf_s(file, "%d", &numbers[i]);
    }
    fclose(file);

    printf("Числа из файла:\n");
    print_array(numbers, n);

    // Подсчет количества простых чисел
    int prime_count = 0;
    for (int i = 0; i < n; i++) {
        if (is_prime(numbers[i])) {
            prime_count++;
        }
    }
    printf("Количество простых чисел: %d\n", prime_count);

    // Замена знака каждого числа на противоположный
    negate_numbers(numbers, n);

    // Открываем файл для записи
    err = fopen_s(&file, filename, "wb");
    if (err != 0) {
        printf("Ошибка открытия файла для записи!\n");
        free(numbers);
        return 1;
    }

    // Записываем измененные числа в файл
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d\n", numbers[i]);
    }
    fclose(file);

    printf("Числа после замены знака:\n");
    print_array(numbers, n);

    // Сортировка отрицательных чисел по убыванию
    sort_negatives(numbers, n);

    // Открываем файл для записи
    err = fopen_s(&file, filename, "wb");
    if (err != 0) {
        printf("Ошибка открытия файла для записи!\n");
        free(numbers);
        return 1;
    }

    // Записываем отсортированные числа в файл
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
