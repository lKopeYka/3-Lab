#pragma once
#include <stdio.h>
#include <stdlib.h>

/* Custom string functions (replacements for standard library) */
size_t custom_strlen(const char* str);
void custom_strcpy(char* destination, const char* source);
int custom_strcmp(const char* first_str, const char* second_str);
char* custom_strchr(const char* str, int character);

/* Task 1: Division by 4 using bitwise operations */
void divide_by_four_without_division_operator();

/* Structures for student records */
typedef struct {
    char date[11];  // Format: "DD.MM.YYYY"
} EnrollmentDate;

typedef struct {
    int student_id;          // Student ID number
    char* last_name;         // Student last name (dynamic string)
    EnrollmentDate enrollment_date;  // Enrollment date
    float gpa;               // Grade point average (0-5)
} StudentRecord;

/* Student record management functions */
void input_student_data(StudentRecord* student);
void print_student_record(const StudentRecord* student);
void search_student_by_last_name(StudentRecord* students, int student_count);
int remove_students_by_id_threshold(StudentRecord** students, int* student_count, int min_id);
void add_new_student(StudentRecord** students, int* student_count, int* capacity);
void display_all_students(StudentRecord* students, int student_count);
void student_management_system();
