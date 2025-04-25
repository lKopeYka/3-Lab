#include "header.h"

/* Custom string functions implementation */
size_t custom_strlen(const char* str) {
    size_t length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

void custom_strcpy(char* destination, const char* source) {
    while (*source != '\0') {
        *destination = *source;
        destination++;
        source++;
    }
    *destination = '\0';
}

int custom_strcmp(const char* first_str, const char* second_str) {
    while (*first_str && (*first_str == *second_str)) {
        first_str++;
        second_str++;
    }
    return *(unsigned char*)first_str - *(unsigned char*)second_str;
}

char* custom_strchr(const char* str, int character) {
    while (*str != '\0') {
        if (*str == character) {
            return (char*)str;
        }
        str++;
    }
    return NULL;
}

/* Task 1: Division by 4 using bit shift */
void divide_by_four_without_division_operator() {
    printf("\nTask 1: Division by 4 without division operator\n");
    int input_number;
    printf("Enter an integer: ");

    while (scanf_s("%d", &input_number, sizeof(input_number)) != 1) {
        printf("Error! Please enter an integer: ");
        while (getchar() != '\n');
    }

    int result = input_number >> 2; // Bitwise right shift
    printf("Result: %d\n", result);
}

/* Student record functions */
void input_student_data(StudentRecord* student) {
    printf("Enter student ID: ");
    while (scanf_s("%d", &student->student_id, sizeof(student->student_id)) != 1 || student->student_id < 0) {
        printf("Error! Enter a positive integer: ");
        while (getchar() != '\n');
    }

    printf("Enter last name: ");
    char buffer[100];
    while (getchar() != '\n');
    fgets(buffer, sizeof(buffer), stdin);

    char* newline = custom_strchr(buffer, '\n');
    if (newline) *newline = '\0';

    student->last_name = (char*)malloc(custom_strlen(buffer) + 1);
    if (!student->last_name) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    custom_strcpy(student->last_name, buffer);

    printf("Enter enrollment date (DD.MM.YYYY): ");
    scanf_s("%10s", student->enrollment_date.date, (unsigned)_countof(student->enrollment_date.date));

    printf("Enter GPA (0-5): ");
    while (scanf_s("%f", &student->gpa, sizeof(student->gpa)) != 1 || student->gpa < 0 || student->gpa > 5) {
        printf("Error! Enter a number between 0 and 5: ");
        while (getchar() != '\n');
    }
}

void print_student_record(const StudentRecord* student) {
    printf("\nStudent ID: %d\n", student->student_id);
    printf("Last Name: %s\n", student->last_name);
    printf("Enrollment Date: %s\n", student->enrollment_date.date);
    printf("GPA: %.2f\n", student->gpa);
    printf("------------------------\n");
}

void display_all_students(StudentRecord* students, int student_count) {
    if (student_count == 0) {
        printf("No students in database.\n");
        return;
    }

    for (int i = 0; i < student_count; i++) {
        print_student_record(&students[i]);
    }
}

void search_student_by_last_name(StudentRecord* students, int student_count) {
    char search_name[100];
    printf("Enter last name to search: ");
    while (getchar() != '\n');
    fgets(search_name, sizeof(search_name), stdin);

    char* newline = custom_strchr(search_name, '\n');
    if (newline) *newline = '\0';

    int found = 0;
    for (int i = 0; i < student_count; i++) {
        if (custom_strcmp(students[i].last_name, search_name) == 0) {
            print_student_record(&students[i]);
            found = 1;
        }
    }

    if (!found) {
        printf("No students found with last name '%s'\n", search_name);
    }
}

int remove_students_by_id_threshold(StudentRecord** students, int* student_count, int min_id) {
    int new_count = 0;
    StudentRecord* new_array = (StudentRecord*)malloc(*student_count * sizeof(StudentRecord));
    if (!new_array) {
        printf("Memory allocation failed!\n");
        return *student_count;
    }

    for (int i = 0; i < *student_count; i++) {
        if ((*students)[i].student_id >= min_id) {
            new_array[new_count] = (*students)[i];
            new_count++;
        }
        else {
            free((*students)[i].last_name);
        }
    }

    free(*students);
    *students = new_array;
    *student_count = new_count;

    return new_count;
}

void add_new_student(StudentRecord** students, int* student_count, int* capacity) {
    if (*student_count >= *capacity) {
        *capacity *= 2;
        *students = (StudentRecord*)realloc(*students, *capacity * sizeof(StudentRecord));
        if (!*students) {
            printf("Memory allocation failed!\n");
            exit(1);
        }
    }

    input_student_data(&(*students)[*student_count]);
    (*student_count)++;
}

/* Main student management interface */
void student_management_system() {
    printf("\n=== Student Management System ===\n");

    int capacity = 2;
    int student_count = 0;
    StudentRecord* students = (StudentRecord*)malloc(capacity * sizeof(StudentRecord));
    if (!students) {
        printf("Initial memory allocation failed!\n");
        exit(1);
    }

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Display all students\n");
        printf("2. Add new student\n");
        printf("3. Search by last name\n");
        printf("4. Remove students by ID threshold\n");
        printf("0. Exit to main menu\n");
        printf("Enter your choice: ");

        while (scanf_s("%d", &choice, sizeof(choice)) != 1) {
            printf("Invalid input! Enter a number: ");
            while (getchar() != '\n');
        }

        switch (choice) {
        case 1:
            display_all_students(students, student_count);
            break;
        case 2:
            add_new_student(&students, &student_count, &capacity);
            break;
        case 3:
            search_student_by_last_name(students, student_count);
            break;
        case 4: {
            int min_id;
            printf("Enter minimum student ID to keep: ");
            while (scanf_s("%d", &min_id, sizeof(min_id)) != 1) {
                printf("Invalid input! Enter an integer: ");
                while (getchar() != '\n');
            }
            student_count = remove_students_by_id_threshold(&students, &student_count, min_id);
            printf("Operation complete. Current students: %d\n", student_count);
            break;
        }
        case 0:
            printf("Returning to main menu...\n");
            break;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 0);

    /* Cleanup memory */
    for (int i = 0; i < student_count; i++) {
        free(students[i].last_name);
    }
    free(students);
}
