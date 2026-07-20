#include <stdio.h>
#include <string.h>
#include <strings.h> 
#include <stdlib.h>
#include "student_registry.h"

static Student registry[MAX_STUDENTS];
static int studentCount = 0;
static const char* filename = "students.dat";

void addStudent(void) {
    if (studentCount >= MAX_STUDENTS) {
        printf("\nError: Registry full! Cannot add more students.\n");
        return;
    }
    
    Student s;
    printf("\nEnter ID: "); 
    if (scanf("%d", &s.id) != 1) {
        printf("Invalid input.\n");
        while(getchar() != '\n'); 
        return;
    }
    getchar(); 
    
    printf("Enter Name: "); 
    fgets(s.name, sizeof(s.name), stdin); 
    s.name[strcspn(s.name, "\n")] = 0; 
    
    printf("Enter Major: "); 
    fgets(s.major, sizeof(s.major), stdin); 
    s.major[strcspn(s.major, "\n")] = 0; 
    
    printf("Enter GPA: "); 
    if (scanf("%f", &s.gpa) != 1) {
        printf("Invalid input.\n");
        while(getchar() != '\n');
        return;
    }
    
    printf("Enter Credits: "); 
    if (scanf("%d", &s.credits) != 1) {
        printf("Invalid input.\n");
        while(getchar() != '\n');
        return;
    }
    
    registry[studentCount++] = s;
    printf("Student added successfully.\n");
}

void displayAllStudents(void) {
    if (studentCount == 0) { 
        printf("\nNo records found.\n"); 
        return; 
    }
    printf("\n--- Student Registry (%d total) ---\n", studentCount);
    for(int i = 0; i < studentCount; i++) {
        printf("[%d] %s | Major: %s | GPA: %.2f | Credits: %d\n", 
            registry[i].id, registry[i].name, registry[i].major, registry[i].gpa, registry[i].credits);
    }
}

void searchStudentByID(void) {
    int searchId;
    printf("\nEnter Student ID to search: ");
    if (scanf("%d", &searchId) != 1) {
        printf("Invalid input.\n");
        while(getchar() != '\n');
        return;
    }
    
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (registry[i].id == searchId) {
            printf("\nStudent Found:\n");
            printf("[%d] %s | Major: %s | GPA: %.2f | Credits: %d\n", 
                registry[i].id, registry[i].name, registry[i].major, registry[i].gpa, registry[i].credits);
            found = 1;
            break;
        }
    }
    if (!found) printf("No student found with ID %d.\n", searchId);
}

void searchStudentByMajor(void) {
    char searchMajor[50];
    printf("\nEnter Major to search: ");
    getchar(); 
    fgets(searchMajor, sizeof(searchMajor), stdin);
    searchMajor[strcspn(searchMajor, "\n")] = 0;

    int foundCount = 0;
    printf("\nSearch Results for Major '%s':\n", searchMajor);
    for (int i = 0; i < studentCount; i++) {
        if (strcasecmp(registry[i].major, searchMajor) == 0) {
            printf("[%d] %s | GPA: %.2f | Credits: %d\n", 
                registry[i].id, registry[i].name, registry[i].gpa, registry[i].credits);
            foundCount++;
        }
    }
    if (foundCount == 0) printf("No students found in that major.\n");
}

void searchStudentByGPA(void) {
    float minGpa;
    printf("\nEnter minimum GPA threshold: ");
    if (scanf("%f", &minGpa) != 1) {
        printf("Invalid input.\n");
        while(getchar() != '\n');
        return;
    }

    int foundCount = 0;
    printf("\nSearch Results for GPA >= %.2f:\n", minGpa);
    for (int i = 0; i < studentCount; i++) {
        if (registry[i].gpa >= minGpa) {
            printf("[%d] %s | Major: %s | GPA: %.2f\n", 
                registry[i].id, registry[i].name, registry[i].major, registry[i].gpa);
            foundCount++;
        }
    }
    if (foundCount == 0) printf("No students match or exceed this GPA.\n");
}

void deleteStudent(void) {
    if (studentCount == 0) {
        printf("\nRegistry is empty.\n");
        return;
    }

    int targetId;
    printf("\nEnter Student ID to delete: ");
    if (scanf("%d", &targetId) != 1) {
        printf("Invalid input.\n");
        while(getchar() != '\n');
        return;
    }

    int foundIndex = -1;
    for (int i = 0; i < studentCount; i++) {
        if (registry[i].id == targetId) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("Student ID %d not found.\n", targetId);
        return;
    }

    for (int i = foundIndex; i < studentCount - 1; i++) {
        registry[i] = registry[i + 1];
    }
    studentCount--;

    printf("Student ID %d deleted. Save & Exit to record changes to file.\n", targetId);
}

void saveStudentsToFile(void) {
    FILE *file = fopen(filename, "w");
    if (!file) { 
        printf("Error: Could not save data.\n"); 
        return; 
    }
    
    for (int i = 0; i < studentCount; i++) {
        fprintf(file, "%d|%s|%s|%.2f|%d\n", 
            registry[i].id, 
            registry[i].name, 
            registry[i].major, 
            registry[i].gpa, 
            registry[i].credits);
    }
    fclose(file);
    printf("Data successfully saved to %s\n", filename);
}

void loadStudentsFromFile(void) {
    FILE *file = fopen(filename, "r");
    if (!file) { 
        printf("No existing data file found. Starting fresh.\n"); 
        return; 
    }
    
    char line[300];
    studentCount = 0; 

    while (fgets(line, sizeof(line), file) && studentCount < MAX_STUDENTS) {
        line[strcspn(line, "\n")] = 0;
        if (strlen(line) == 0) continue;

        char *token = strtok(line, "|");
        if (token == NULL) continue;
        registry[studentCount].id = atoi(token);

        token = strtok(NULL, "|");
        if (token == NULL) continue;
        strncpy(registry[studentCount].name, token, sizeof(registry[studentCount].name) - 1);
        registry[studentCount].name[sizeof(registry[studentCount].name) - 1] = '\0';

        token = strtok(NULL, "|");
        if (token == NULL) continue;
        strncpy(registry[studentCount].major, token, sizeof(registry[studentCount].major) - 1);
        registry[studentCount].major[sizeof(registry[studentCount].major) - 1] = '\0';

        token = strtok(NULL, "|");
        if (token == NULL) continue;
        registry[studentCount].gpa = atof(token);

        token = strtok(NULL, "|");
        if (token == NULL) continue;
        registry[studentCount].credits = atoi(token);

        studentCount++;
    }
    fclose(file);
    printf("Loaded %d students.\n", studentCount);
}
