#include "header.h"

// Custom string functions implementation
size_t my_strlen(const char* str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

void my_strcpy(char* dest, const char* src) {
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

int my_strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(unsigned char*)s1 - *(unsigned char*)s2;
}

char* my_strchr(const char* str, int c) {
    while (*str != '\0') {
        if (*str == c) {
            return (char*)str;
        }
        str++;
    }
    return NULL;
}

// Task 1 implementation
void task1() {
    printf("\nTask 1: Find number 4 times smaller without division\n");
    int num;
    printf("Enter an integer: ");

    while (scanf_s("%d", &num, sizeof(num)) != 1) {
        printf("Error! Please enter an integer: ");
        while (getchar() != '\n');
    }

    int result = num >> 2;
    printf("Result: %d\n", result);
}

// Student functions implementation
void inputStudent(Student* s) {
    printf("Enter student ID: ");
    while (scanf_s("%d", &s->recordBookNumber, sizeof(s->recordBookNumber)) != 1 || s->recordBookNumber < 0) {
        printf("Error! Please enter a positive integer: ");
        while (getchar() != '\n');
    }

    printf("Enter last name: ");
    char buffer[100];
    while (getchar() != '\n');
    fgets(buffer, sizeof(buffer), stdin);

    char* newline = my_strchr(buffer, '\n');
    if (newline) *newline = '\0';

    s->lastName = (char*)malloc(my_strlen(buffer) + 1);
    if (s->lastName == NULL) {
        printf("Memory allocation error!\n");
        exit(1);
    }
    my_strcpy(s->lastName, buffer);

    printf("Enter enrollment date (DD.MM.YYYY): ");
    scanf_s("%10s", s->date.date, (unsigned)_countof(s->date.date));

    printf("Enter GPA (0-5): ");
    while (scanf_s("%f", &s->averageGrade, sizeof(s->averageGrade)) != 1 || s->averageGrade < 0 || s->averageGrade > 5) {
        printf("Error! Please enter a number between 0 and 5: ");
        while (getchar() != '\n');
    }
}

void printStudent(const Student* s) {
    printf("Student ID: %d\n", s->recordBookNumber);
    printf("Last name: %s\n", s->lastName);
    printf("Enrollment date: %s\n", s->date.date);
    printf("GPA: %.2f\n", s->averageGrade);
    printf("----------------------------\n");
}

void searchByLastName(Student* students, int count) {
    char searchName[100];
    printf("Enter last name to search: ");
    while (getchar() != '\n');
    fgets(searchName, sizeof(searchName), stdin);

    char* newline = my_strchr(searchName, '\n');
    if (newline) *newline = '\0';

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (my_strcmp(students[i].lastName, searchName) == 0) {
            printStudent(&students[i]);
            found = 1;
        }
    }

    if (!found) {
        printf("No students with last name '%s' found.\n", searchName);
    }
}

int deleteStudentsByRecordBook(Student** students, int* count, int threshold) {
    int newCount = 0;
    Student* newArray = (Student*)malloc(*count * sizeof(Student));
    if (newArray == NULL) {
        printf("Memory allocation error!\n");
        return *count;
    }

    for (int i = 0; i < *count; i++) {
        if ((*students)[i].recordBookNumber >= threshold) {
            newArray[newCount] = (*students)[i];
            newCount++;
        }
        else {
            free((*students)[i].lastName);
        }
    }

    free(*students);
    *students = newArray;
    *count = newCount;

    return newCount;
}

void addStudent(Student** students, int* count, int* capacity) {
    if (*count >= *capacity) {
        *capacity *= 2;
        *students = (Student*)realloc(*students, *capacity * sizeof(Student));
        if (*students == NULL) {
            printf("Memory allocation error!\n");
            exit(1);
        }
    }

    inputStudent(&(*students)[*count]);
    (*count)++;
}

void viewAllStudents(Student* students, int count) {
    if (count == 0) {
        printf("No student data available.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printStudent(&students[i]);
    }
}

void task2() {
    printf("\nTask 2: Student Management System\n");

    int capacity = 2;
    int count = 0;
    Student* students = (Student*)malloc(capacity * sizeof(Student));
    if (students == NULL) {
        printf("Memory allocation error!\n");
        exit(1);
    }

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. View all students\n");
        printf("2. Add new student\n");
        printf("3. Search by last name\n");
        printf("4. Delete students with ID below threshold\n");
        printf("0. Exit\n");
        printf("Select option: ");

        while (scanf_s("%d", &choice, sizeof(choice)) != 1) {
            printf("Error! Please enter a number: ");
            while (getchar() != '\n');
        }

        switch (choice) {
        case 1:
            viewAllStudents(students, count);
            break;
        case 2:
            addStudent(&students, &count, &capacity);
            break;
        case 3:
            searchByLastName(students, count);
            break;
        case 4: {
            int threshold;
            printf("Enter minimum student ID: ");
            while (scanf_s("%d", &threshold, sizeof(threshold)) != 1) {
                printf("Error! Please enter an integer: ");
                while (getchar() != '\n');
            }
            count = deleteStudentsByRecordBook(&students, &count, threshold);
            printf("Deletion complete. Remaining students: %d\n", count);
            break;
        }
        case 0:
            printf("Exiting student management...\n");
            break;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 0);

    for (int i = 0; i < count; i++) {
        free(students[i].lastName);
    }
    free(students);
}