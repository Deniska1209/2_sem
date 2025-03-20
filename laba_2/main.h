#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

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

void print_file_contents(const char* filename) {
    FILE* file;
    errno_t err = fopen_s(&file, filename, "rb");
    if (err != 0) {
        printf("Ошибка открытия файла для чтения!\n");
        return;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
}

int is_digit(char ch) {
    return ch >= '0' && ch <= '9';
}

int sum_of_digits_in_file(const char* filename) {
    FILE* file;
    errno_t err = fopen_s(&file, filename, "rb");
    if (err != 0) {
        printf("Ошибка открытия файла для чтения!\n");
        return 0;
    }

    int sum = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (is_digit(ch)) {
            sum += ch - '0';
        }
    }

    fclose(file);
    return sum;
}

void replace_longest_number_with_spaces(const char* filename) {
    FILE* file;
    errno_t err = fopen_s(&file, filename, "r+");
    if (err != 0) {
        printf("Ошибка открытия файла для чтения и записи!\n");
        return;
    }

    char buffer[1024];
    char longest_number[1024] = "";
    long longest_number_pos = -1;
    int longest_number_length = 0;

    long current_pos = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (is_digit(ch)) {
            int length = 0;
            buffer[length++] = ch;
            while ((ch = fgetc(file)) != EOF && is_digit(ch)) {
                buffer[length++] = ch;
            }
            buffer[length] = '\0';

            if (length >= longest_number_length) {
                longest_number_length = length;
                strcpy_s(longest_number, sizeof(longest_number), buffer);
                longest_number_pos = current_pos;
            }

            current_pos = ftell(file);
        }
        else {
            current_pos++;
        }
    }

    if (longest_number_pos != -1) {
        fseek(file, longest_number_pos, SEEK_SET);
        for (int i = 0; i < longest_number_length; i++) {
            fputc(' ', file);
        }
    }

    fclose(file);
}

void write_to_file_until_exclamation(const char* filename) {
    FILE* file;
    errno_t err = fopen_s(&file, filename, "wb");
    if (err != 0) {
        printf("Ошибка открытия файла для записи!\n");
        return;
    }

    printf("Введите символы для записи в файл (для завершения введите '!'):\n");
    char ch;
    while ((ch = getchar()) != '!') {
        fputc(ch, file);
    }
    fclose(file);
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    if (argc != 2) {
        printf("Использование: %s <имя_файла>\n", argv[0]);
        return 1;
    }

    const char* filename = argv[1];

    write_to_file_until_exclamation(filename);

    printf("Содержимое файла:\n");
    print_file_contents(filename);

    int sum = sum_of_digits_in_file(filename);
    printf("Сумма всех цифр в файле: %d\n", sum);

    replace_longest_number_with_spaces(filename);
    printf("Содержимое файла после замены самого длинного числа на пробелы:\n");
    print_file_contents(filename);

    system("pause");
    return 0;
}
