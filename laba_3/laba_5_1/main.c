/*
Задание: Создать стек для целых чисел. Максимальный размер стека вводится с экрана.
Найти максимальный четный элемент стека.
Студент: [Лыщик]
Дата: [12.04.25]
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <locale.h> 

typedef struct {
    int* data;     // массив для хранения элементов стека
    int top;       // индекс вершины стека
    int capacity;  // максимальная вместимость стека
} Stack;

// Функция для инициализации стека
Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) {
        printf("Ошибка выделения памяти под стек.\n");
        exit(EXIT_FAILURE);
    }
    stack->data = (int*)malloc(capacity * sizeof(int));
    if (stack->data == NULL) {
        printf("Ошибка выделения памяти под данные стека.\n");
        free(stack);
        exit(EXIT_FAILURE);
    }
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

// Проверка, пуст ли стек
bool isEmpty(Stack* stack) {
    return stack->top == -1;
}

// Проверка, заполнен ли стек
bool isFull(Stack* stack) {
    return stack->top == stack->capacity - 1;
}

// Добавление элемента в стек
void push(Stack* stack, int value) {
    if (isFull(stack)) {
        printf("Стек переполнен. Невозможно добавить элемент.\n");
        return;
    }
    stack->data[++stack->top] = value;
}

// Удаление элемента из стека
int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Стек пуст. Невозможно извлечь элемент.\n");
        return INT_MIN; 
    }
    return stack->data[stack->top--];
}

// Функция для просмотра содержимого стека
void displayStack(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Стек пуст.\n");
        return;
    }
    printf("Содержимое стека (от вершины к основанию):\n");
    for (int i = stack->top; i >= 0; i--) {
        printf("%d\n", stack->data[i]);
    }
}

// Функция для поиска максимального четного элемента в стеке
int findMaxEven(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Стек пуст. Нет элементов для поиска.\n");
        return INT_MIN;
    }
    int maxEven = INT_MIN;
    bool foundEven = false;

    for (int i = stack->top; i >= 0; i--) {
        if (stack->data[i] % 2 == 0) {
            if (!foundEven || stack->data[i] > maxEven) {
                maxEven = stack->data[i];
                foundEven = true;
            }
        }
    }

    if (!foundEven) {
        printf("В стеке нет четных элементов.\n");
        return INT_MIN;
    }
    return maxEven;
}

int main() {
    setlocale(LC_ALL, "ru");
    int capacity;
    printf("Введите максимальный размер стека: ");
    while (scanf_s("%d", &capacity) != 1 || capacity <= 0) {
        printf("Некорректный ввод. Введите положительное целое число: ");
        while (getchar() != '\n'); 
    }

    Stack* stack = createStack(capacity);

    int choice, value;
    do {
        printf("\nМеню:\n");
        printf("1. Добавить элемент в стек\n");
        printf("2. Удалить элемент из стека\n");
        printf("3. Просмотреть содержимое стека\n");
        printf("4. Найти максимальный четный элемент\n");
        printf("5. Выход\n");
        printf("Выберите действие: ");
        while (scanf_s("%d", &choice) != 1 || choice < 1 || choice > 5) {
            printf("Некорректный ввод. Введите число от 1 до 5: ");
            while (getchar() != '\n');
        }

        switch (choice) {
        case 1:
            printf("Введите целое число для добавления в стек: ");
            while (scanf_s("%d", &value) != 1) {
                printf("Некорректный ввод. Введите целое число: ");
                while (getchar() != '\n');
            }
            push(stack, value);
            break;
        case 2:
            value = pop(stack);
            if (value != INT_MIN) {
                printf("Извлеченный элемент: %d\n", value);
            }
            break;
        case 3:
            displayStack(stack);
            break;
        case 4:
            value = findMaxEven(stack);
            if (value != INT_MIN) {
                printf("Максимальный четный элемент в стеке: %d\n", value);
            }
            break;
        case 5:
            printf("Завершение программы.\n");
            break;
        }
    } while (choice != 5);
    
    free(stack->data);
    free(stack);

    return 0;
}
