#include "header.h"

int main() {
    int choice;

    do {
        printf("\nMain Menu:\n");
        printf("1. Task 1 (Division by 4 without division)\n");
        printf("2. Task 2 (Student Management System)\n");
        printf("0. Exit\n");
        printf("Select task: ");

        while (scanf_s("%d", &choice, sizeof(choice)) != 1) {
            printf("Error! Please enter a number: ");
            while (getchar() != '\n');
        }

        switch (choice) {
        case 1:
            task1();
            break;
        case 2:
            task2();
            break;
        case 0:
            printf("Exiting program...\n");
            break;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}