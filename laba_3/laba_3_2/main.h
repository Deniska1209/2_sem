/*
Задание:
Структура содержит информацию об автомобилях: стоимость (число), марку (указатель),
вложенную структуру – тип кузова (строка фиксированной длины) и объём двигателя.
Найти автомобили со стоимостью больше заданной. Удалить автомобили заданной марки.

Фамилия студента: [Лыщик]
Дата написания кода: [01.04.25]
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#define MAX_BODY_TYPE_LENGTH 30
#define MAX_BRAND_LENGTH 50

// Структура для типа кузова и объема двигателя
typedef struct {
    char bodyType[MAX_BODY_TYPE_LENGTH];
    float engineVolume;
} CarDetails;

// Структура для автомобиля
typedef struct {
    float price;
    char* brand;
    CarDetails details;
} Car;

// Функция для ввода данных об автомобиле
void inputCar(Car* car) {
    printf("Введите стоимость автомобиля: ");
    while (scanf_s("%f", &car->price) != 1 || car->price <= 0) {
        printf("Ошибка! Введите положительное число для стоимости: ");
        while (getchar() != '\n'); 
    }

    printf("Введите марку автомобиля: ");
    char brandBuffer[MAX_BRAND_LENGTH];
    while (getchar() != '\n'); 
    fgets(brandBuffer, MAX_BRAND_LENGTH, stdin);
    brandBuffer[strcspn(brandBuffer, "\n")] = '\0'; 

    car->brand = (char*)malloc(strlen(brandBuffer) + 1);
    if (car->brand == NULL) {
        printf("Ошибка выделения памяти для марки автомобиля!\n");
        exit(1);
    }
    strcpy_s(car->brand, strlen(brandBuffer) + 1, brandBuffer);

    printf("Введите тип кузова автомобиля: ");
    fgets(car->details.bodyType, MAX_BODY_TYPE_LENGTH, stdin);
    car->details.bodyType[strcspn(car->details.bodyType, "\n")] = '\0';

    printf("Введите объем двигателя автомобиля: ");
    while (scanf_s("%f", &car->details.engineVolume) != 1 || car->details.engineVolume <= 0) {
        printf("Ошибка! Введите положительное число для объема двигателя: ");
        while (getchar() != '\n'); 
    }
}

// Функция для вывода данных об автомобиле
void printCar(const Car* car) {
    printf("Марка: %s\n", car->brand);
    printf("Стоимость: %.2f\n", car->price);
    printf("Тип кузова: %s\n", car->details.bodyType);
    printf("Объем двигателя: %.2f\n", car->details.engineVolume);
    printf("----------------------------\n");
}

// Функция для поиска автомобилей с ценой выше заданной
void findCarsAbovePrice(const Car* cars, int size, float price) {
    int found = 0;
    for (int i = 0; i < size; i++) {
        if (cars[i].price > price) {
            printCar(&cars[i]);
            found = 1;
        }
    }
    if (!found) {
        printf("Автомобилей с ценой выше %.2f не найдено.\n", price);
    }
}

// Функция для удаления автомобилей по марке
int deleteCarsByBrand(Car** cars, int* size, const char* brand) {
    int deleted = 0;
    for (int i = 0; i < *size; i++) {
        if (strcmp((*cars)[i].brand, brand) == 0) {
            free((*cars)[i].brand); 
            for (int j = i; j < *size - 1; j++) {
                (*cars)[j] = (*cars)[j + 1];
            }
            (*size)--;
            i--; // Проверяем текущий индекс снова после сдвига
            deleted++;
        }
    }

    // Перераспределяем память
    if (deleted > 0) {
        Car* temp = (Car*)realloc(*cars, (*size) * sizeof(Car));
        if (temp == NULL && *size > 0) {
            printf("Ошибка перераспределения памяти!\n");
            return deleted;
        }
        *cars = temp;
    }

    return deleted;
}

// Функция для освобождения памяти
void freeCars(Car* cars, int size) {
    for (int i = 0; i < size; i++) {
        free(cars[i].brand);
    }
    free(cars);
}

int main() {
    setlocale(LC_ALL, "Russian");
    Car* cars = NULL;
    int size = 0;
    int choice;

    do {
        printf("\nМеню:\n");
        printf("1. Просмотр всех автомобилей\n");
        printf("2. Добавить новый автомобиль\n");
        printf("3. Найти автомобили с ценой выше заданной\n");
        printf("4. Удалить автомобили по марке\n");
        printf("5. Выход\n");
        printf("Выберите пункт меню: ");
        while (scanf_s("%d", &choice) != 1 || choice < 1 || choice > 5) {
            printf("Ошибка! Введите число от 1 до 5: ");
            while (getchar() != '\n'); 
        }

        switch (choice) {
        case 1: // Просмотр всех автомобилей
            if (size == 0) {
                printf("Список автомобилей пуст.\n");
            }
            else {
                for (int i = 0; i < size; i++) {
                    printf("\nАвтомобиль %d:\n", i + 1);
                    printCar(&cars[i]);
                }
            }
            break;

        case 2: // Добавить новый автомобиль
        {
            Car* temp = (Car*)realloc(cars, (size + 1) * sizeof(Car));
            if (temp == NULL) {
                printf("Ошибка выделения памяти!\n");
                break;
            }
            cars = temp;
            inputCar(&cars[size]);
            size++;
            printf("Автомобиль успешно добавлен.\n");
        }
        break;

        case 3: // Найти автомобили с ценой выше заданной
            if (size == 0) {
                printf("Список автомобилей пуст.\n");
            }
            else {
                float price;
                printf("Введите минимальную стоимость для поиска: ");
                while (scanf_s("%f", &price) != 1 || price <= 0) {
                    printf("Ошибка! Введите положительное число: ");
                    while (getchar() != '\n');
                }
                findCarsAbovePrice(cars, size, price);
            }
            break;

        case 4: // Удалить автомобили по марке
            if (size == 0) {
                printf("Список автомобилей пуст.\n");
            }
            else {
                char brand[MAX_BRAND_LENGTH];
                printf("Введите марку автомобиля для удаления: ");
                while (getchar() != '\n');
                fgets(brand, MAX_BRAND_LENGTH, stdin);
                brand[strcspn(brand, "\n")] = '\0';

                int deleted = deleteCarsByBrand(&cars, &size, brand);
                printf("Удалено %d автомобилей марки %s.\n", deleted, brand);
            }
            break;

        case 5: 
            printf("Завершение программы...\n");
            break;
        }
    } while (choice != 5);

    freeCars(cars, size);
    return 0;
}
