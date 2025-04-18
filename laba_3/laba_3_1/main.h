/*
 * Задание: Для целого числа (char) вывести его дополнительный код.
 * Студент: [Лыщик]
 * Дата: [29.03.25]
 */

#include <stdio.h>
#include <limits.h>
#include <locale.h>

typedef struct {
    unsigned char b0 : 1; 
    unsigned char b1 : 1;
    unsigned char b2 : 1;
    unsigned char b3 : 1;
    unsigned char b4 : 1;
    unsigned char b5 : 1;
    unsigned char b6 : 1;
    unsigned char b7 : 1;  
} CharBits;

void print_binary(CharBits num) {
    printf("Двоичное представление (как хранится в памяти): ");
    printf("%d%d%d%d %d%d%d%d\n",
        num.b7, num.b6, num.b5, num.b4,
        num.b3, num.b2, num.b1, num.b0);
}

void print_twos_complement(char num) {
    if (num >= 0) {
        printf("Число положительное, дополнительный код совпадает с прямым.\n");
        return;
    }

    printf("Дополнительный код (инверсия + 1):\n");

    unsigned char abs_num = -num;
    printf("  Прямой код |%d|: ", abs_num);
    for (int i = 7; i >= 0; i--) {
        printf("%d", (abs_num >> i) & 1);
        if (i == 4) printf(" ");
    }
    printf("\n");

    unsigned char inverted = ~abs_num;
    printf("  Инверсия:     ");
    for (int i = 7; i >= 0; i--) {
        printf("%d", (inverted >> i) & 1);
        if (i == 4) printf(" ");
    }
    printf("\n");

    unsigned char twos_complement = inverted + 1;
    printf("  +1:           ");
    for (int i = 7; i >= 0; i--) {
        printf("%d", (twos_complement >> i) & 1);
        if (i == 4) printf(" ");
    }
    printf("\n");
}

int main() {
    setlocale(LC_ALL, "Russian");
    int input_number;
    int input_success = 0;

    while (!input_success) {
        printf("Введите число типа char (от %d до %d): ", CHAR_MIN, CHAR_MAX);

        if (scanf_s("%d", &input_number) == 1) {
            if (input_number >= CHAR_MIN && input_number <= CHAR_MAX) {
                input_success = 1;
            }
            else {
                printf("Ошибка! Число должно быть от %d до %d.\n", CHAR_MIN, CHAR_MAX);
                while (getchar() != '\n');
            }
        }
        else {
            printf("Ошибка ввода! Введите целое число.\n");
            while (getchar() != '\n');
        }
    }

    char num = (char)input_number;
    CharBits* bits = (CharBits*)&num;

    printf("\nВведенное число: %d\n", num);
    print_binary(*bits);
    print_twos_complement(num);

    return 0;
}
