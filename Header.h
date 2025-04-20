#pragma once
#include <stdio.h>
#include <stdlib.h>

// Custom string functions
size_t my_strlen(const char* str);
void my_strcpy(char* dest, const char* src);
int my_strcmp(const char* s1, const char* s2);
char* my_strchr(const char* str, int c);

// Task 1 function
void task1();

// Student structure definitions
typedef struct {
    char date[11];
} EnrollmentDate;

typedef struct {
    int recordBookNumber;
    char* lastName;
    EnrollmentDate date;
    float averageGrade;
} Student;

// Student management functions
void inputStudent(Student* s);
void printStudent(const Student* s);
void searchByLastName(Student* students, int count);
int deleteStudentsByRecordBook(Student** students, int* count, int threshold);
void addStudent(Student** students, int* count, int* capacity);
void viewAllStudents(Student* students, int count);
void task2();