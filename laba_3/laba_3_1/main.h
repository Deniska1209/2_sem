/*
 * Задание: Для целого числа (char) вывести его дополнительный код.
 * Студент: [Лыщик]
 * Дата: [29.03.25]
 */

#include <stdio.h>
#include <limits.h>
#include <locale.h>

  // Функция для вывода двоичного представления числа
void print_binary(char num) {
    int bits = CHAR_BIT; 

    // Проходим по каждому биту, начиная со старшего
    for (int i = bits - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if (i == 4) printf(" "); 
    }
    printf("\n");
}

int main() {
    setlocale(LC_ALL, "Russian");
    int input_number;  
    int input_success = 0;

    // Запрос на ввод числа с клавиатуры до получения корректного значения
    while (!input_success) {
        printf("Введите число типа char (от %d до %d): ", CHAR_MIN, CHAR_MAX);

        // Проверка корректности ввода
        if (scanf("%d", &input_number) == 1) {
            // Проверка, что число входит в диапазон char
            if (input_number >= CHAR_MIN && input_number <= CHAR_MAX) {
                input_success = 1;
            }
            else {
                printf("Ошибка! Число должно быть от %d до %d.\n", CHAR_MIN, CHAR_MAX);
                while (getchar() != '\n');
            }
        }
        else {
            printf("Ошибка ввода! Пожалуйста, введите целое число.\n");
            while (getchar() != '\n');
        }
    }

    char num = (char)input_number;

    printf("\nВведенное число: %d\n", num);
    printf("Двоичное представление: ");
    print_binary(num);
    printf("Дополнительный код:    ");
    print_binary(num);  

    return 0;
}
