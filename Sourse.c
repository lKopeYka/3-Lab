//Условие
//1. 1. Найти и вывести целое число в 4 раза меньше заданного, не выполняя
//деления и не используя операцию взятия остатка от деления.
//2. Структура содержит информацию о студентах: номер зачётки (число),
//фамилию (указатель), вложенную структуру – дату зачисления (строка
//фиксированной длины) и средний балл. Найти студентов с заданной
//фамилией. Удалить студентов с номером зачетки меньше заданного.


//Ямонт Михаил Денисович
#include "Header.h"

int main() {
    int user_choice;

    do {
        printf("\nMain Menu:\n");
        printf("1. Task 1 (Bitwise operations)\n");
        printf("2. Task 2 (Student management system)\n");
        printf("0. Exit\n");
        printf("Select task: ");

        while (scanf_s("%d", &user_choice, sizeof(user_choice)) != 1) {
            printf("Error! Please enter a number: ");
            while (getchar() != '\n');
        }

        switch (user_choice) {
        case 1:
            divide_by_four_without_division_operator();
            break;
        case 2:
            student_management_system();
            break;
        case 0:
            printf("Exiting program...\n");
            break;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    } while (user_choice != 0);

    return 0;
}
