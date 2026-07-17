#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "student_registry.h"

static Student registry[MAX_STUDENTS];
static int studentCount = 0;
const char* filename = "students.dat";

void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("Registry full!\n");
        return;
    }
    Student s;
    printf("Enter ID: "); scanf("%d", &s.id);
    getchar(); 
    printf("Enter Name: "); fgets(s.name, 100, stdin); s.name[strcspn(s.name, "\n")] = 0;
    printf("Enter Major: "); fgets(s.major, 50, stdin); s.major[strcspn(s.major, "\n")] = 0;
    printf("Enter GPA: "); scanf("%f", &s.gpa);
    printf("Enter Credits: "); scanf("%d", &s.credits);
    
    registry[studentCount++] = s;
    printf("Student added successfully.\n");
}

void displayAllStudents() {
    if (studentCount == 0) { printf("No records found.\n"); return; }
    for(int i = 0; i < studentCount; i++) {
        printf("[%d] %s | Major: %s | GPA: %.2f | Credits: %d\n", 
            registry[i].id, registry[i].name, registry[i].major, registry[i].gpa, registry[i].credits);
    }
}



void saveStudentsToFile() {

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

void loadStudentsFromFile() {
    
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
