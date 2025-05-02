/*
Задание: Создать два стека для целых чисел. Первый стек – организовать ввод по убыванию,
второй стек – организовать ввод по возрастанию. Без сортировок и переворачивания исходных стеков
сформировать третий стек, упорядоченный по убыванию.
Студент: [Ваша фамилия]
Дата: [Дата написания кода]
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

// Добавление элемента в стек (по убыванию)
void pushDescending(Stack* stack, int value) {
    if (isFull(stack)) {
        printf("Стек переполнен. Невозможно добавить элемент.\n");
        return;
    }
    if (isEmpty(stack) || value <= stack->data[stack->top]) {
        stack->data[++stack->top] = value;
    }
    else {
        printf("Элемент %d нарушает порядок убывания. Пропуск.\n", value);
    }
}

// Добавление элемента в стек (по возрастанию)
void pushAscending(Stack* stack, int value) {
    if (isFull(stack)) {
        printf("Стек переполнен. Невозможно добавить элемент.\n");
        return;
    }
    if (isEmpty(stack) || value >= stack->data[stack->top]) {
        stack->data[++stack->top] = value;
    }
    else {
        printf("Элемент %d нарушает порядок возрастания. Пропуск.\n", value);
    }
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

// Функция для создания третьего стека, упорядоченного по убыванию
Stack* mergeStacksDescending(Stack* stack1, Stack* stack2) {
    // Размер третьего стека равен сумме размеров двух исходных стеков
    Stack* result = createStack(stack1->capacity + stack2->capacity);
    int val1, val2;

    while (!isEmpty(stack1) || !isEmpty(stack2)) {
        val1 = !isEmpty(stack1) ? stack1->data[stack1->top] : INT_MIN;
        val2 = !isEmpty(stack2) ? stack2->data[stack2->top] : INT_MIN;

        if (val1 >= val2) {
            pushDescending(result, pop(stack1));
        }
        else {
            pushDescending(result, pop(stack2));
        }
    }

    return result;
}

int main() {
    setlocale(LC_ALL, "ru");
    int capacity;
    printf("Введите максимальный размер стеков: ");
    while (scanf_s("%d", &capacity) != 1 || capacity <= 0) {
        printf("Некорректный ввод. Введите положительное целое число: ");
        while (getchar() != '\n'); 
    }

    Stack* stackDesc = createStack(capacity); // Стек с убывающим порядком
    Stack* stackAsc = createStack(capacity);  // Стек с возрастающим порядком

    int choice, value;
    do {
        printf("\nМеню:\n");
        printf("1. Добавить элемент в убывающий стек\n");
        printf("2. Добавить элемент в возрастающий стек\n");
        printf("3. Просмотреть убывающий стек\n");
        printf("4. Просмотреть возрастающий стек\n");
        printf("5. Создать и просмотреть третий стек (убывающий)\n");
        printf("6. Выход\n");
        printf("Выберите действие: ");
        while (scanf_s("%d", &choice) != 1 || choice < 1 || choice > 6) {
            printf("Некорректный ввод. Введите число от 1 до 6: ");
            while (getchar() != '\n');
        }

        switch (choice) {
        case 1:
            printf("Введите целое число для добавления в убывающий стек: ");
            while (scanf_s("%d", &value) != 1) {
                printf("Некорректный ввод. Введите целое число: ");
                while (getchar() != '\n');
            }
            pushDescending(stackDesc, value);
            break;
        case 2:
            printf("Введите целое число для добавления в возрастающий стек: ");
            while (scanf_s("%d", &value) != 1) {
                printf("Некорректный ввод. Введите целое число: ");
                while (getchar() != '\n');
            }
            pushAscending(stackAsc, value);
            break;
        case 3:
            printf("Убывающий стек:\n");
            displayStack(stackDesc);
            break;
        case 4:
            printf("Возрастающий стек:\n");
            displayStack(stackAsc);
            break;
        case 5:
            if (isEmpty(stackDesc) && isEmpty(stackAsc)) {
                printf("Оба стека пусты. Невозможно создать третий стек.\n");
            }
            else {
                Stack* mergedStack = mergeStacksDescending(stackDesc, stackAsc);
                printf("Третий стек (убывающий, размер = %d):\n", stackDesc->capacity + stackAsc->capacity);
                displayStack(mergedStack);
                free(mergedStack->data);
                free(mergedStack);
            }
            break;
        case 6:
            printf("Завершение программы.\n");
            break;
        }
    } while (choice != 6);

    free(stackDesc->data);
    free(stackDesc);
    free(stackAsc->data);
    free(stackAsc);

    return 0;
}
