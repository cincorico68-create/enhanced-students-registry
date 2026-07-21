#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "student_registry.h"

static int isStrictDigits(const char *str) {
    if (*str == '\0') return 0;
    while (*str) {
        if (!isdigit((unsigned char)*str)) return 0;
        str++;
    }
    return 1;
}

int main(void) {
    loadStudentsFromFile();
    int choice;
    char input[50];

menu:
    printf("\n===== STUDENT REGISTRY SYSTEM =====\n");
    printf("1. Add Student\n");
    printf("2. Display All Students\n");
    printf("3. Search by ID\n");
    printf("4. Search by Major\n");
    printf("5. Search by GPA Threshold\n");
    printf("6. Save & Exit\n");
    printf("===================================\n");
    printf("Choice: ");

    if (fgets(input, sizeof(input), stdin) == NULL) {
        goto menu;
    }

    input[strcspn(input, "\r\n")] = '\0';

    if (!isStrictDigits(input)) {
        printf("Invalid choice. Please enter digits only (no + or -).\n");
        goto menu;
    }

    choice = atoi(input);

    switch (choice) {
        case 1: addStudent(); goto menu;
        case 2: displayAllStudents(); goto menu;
        case 3: searchStudentByID(); goto menu;
        case 4: searchStudentByMajor(); goto menu;
        case 5: searchStudentByGPA(); goto menu;
        case 6: saveStudentsToFile(); break;
        default: 
            printf("Invalid choice. Try again.\n");
            goto menu;
    }

    printf("Goodbye!\n");
    return 0;
}
