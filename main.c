#include <stdio.h>
#include "student_registry.h"

int main(void) {
    loadStudentsFromFile();
    int choice;
    
    do {
        printf("\n===== STUDENT REGISTRY SYSTEM =====\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search by ID\n");
        printf("4. Search by Major\n");
        printf("5. Search by GPA Threshold\n");
        printf("6. Delete Student\n");
        printf("7. Save & Exit\n");
        printf("===================================\n");
        printf("Choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Please enter a valid menu number.\n");
            while(getchar() != '\n'); 
            choice = 0;
            continue;
        }

        switch(choice) {
            case 1: addStudent(); break;
            case 2: displayAllStudents(); break;
            case 3: searchStudentByID(); break;
            case 4: searchStudentByMajor(); break;
            case 5: searchStudentByGPA(); break;
            case 6: deleteStudent(); break;
            case 7: saveStudentsToFile(); break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 7);
    
    printf("Goodbye!\n");
    return 0;
}
