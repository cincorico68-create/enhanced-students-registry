#include <stdio.h>
#include <string.h>
#include "student_registry.h"

// Variable allocations managed completely at runtime
char fileName[100] = "students.dat"; 
Student students[5000];
int studentCount = 0;
int maxCapacity = 10; 

void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void addStudent(void) {
    if (studentCount >= maxCapacity) {
        printf("\n[Error] System full! Cannot exceed the file-defined capacity of %d students.\n", maxCapacity);
        return;
    }

    Student s;
    printf("\n--- Registering Student #%d (Max Capacity: %d) ---\n", studentCount + 1, maxCapacity);
    
    printf("Step 1: Enter ID: ");
    if (scanf("%d", &s.id) != 1) { clearInputBuffer(); return; }
    clearInputBuffer();

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == s.id) {
            printf("[Error] ID %d is already assigned.\n", s.id);
            return;
        }
    }

    printf("Step 2: Enter Name: ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = '\0';

    printf("Step 3: Enter Major: ");
    fgets(s.major, sizeof(s.major), stdin);
    s.major[strcspn(s.major, "\n")] = '\0';

    printf("Step 4: Enter GPA (0.00 - 4.00): ");
    if (scanf("%f", &s.gpa) != 1) { clearInputBuffer(); return; }
    clearInputBuffer();

    printf("Step 5: Enter Credits Completed: ");
    if (scanf("%d", &s.credits) != 1) { clearInputBuffer(); return; }
    clearInputBuffer();

    students[studentCount] = s;
    studentCount++;
    printf("\n[Success] Student record staged locally!\n");
}

void displayAllStudents(void) {
    if (studentCount == 0) {
        printf("\n[Notice] Registry is empty.\n");
        return;
    }

    printf("\n%-8s %-30s %-25s %-6s %-8s\n", "ID", "Name", "Major", "GPA", "Credits");
    printf("-------------------------------------------------------------------------------------\n");

    for (int i = 0; i < studentCount; i++) {
        printf("%-8d %-30s %-25s %-6.2f %-8d\n",
               students[i].id, students[i].name, students[i].major, students[i].gpa, students[i].credits);
    }
}

void searchByID(void) {
    if (studentCount == 0) {
        printf("\n[Notice] Registry is empty.\n");
        return;
    }

    int searchID;
    printf("\nEnter Student ID to find: ");
    if (scanf("%d", &searchID) != 1) { clearInputBuffer(); return; }
    clearInputBuffer();

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == searchID) {
            printf("\nMatch Found\n");
            printf("ID      : %d\n", students[i].id);
            printf("Name    : %s\n", students[i].name);
            printf("Major   : %s\n", students[i].major);
            printf("GPA     : %.2f\n", students[i].gpa);
            printf("Credits : %d\n", students[i].credits);
            return;
        }
    }
    printf("\nID %d not found.\n", searchID);
}

void findByGPA(void) {
    if (studentCount == 0) {
        printf("\n[Notice] Registry is empty.\n");
        return;
    }

    float threshold;
    printf("\nEnter minimum GPA threshold: ");
    if (scanf("%f", &threshold) != 1) { clearInputBuffer(); return; }
    clearInputBuffer();

    printf("\nStudents with GPA >= %.2f:\n", threshold);
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].gpa >= threshold) {
            printf("- %s (ID: %d | GPA: %.2f | Major: %s)\n",
                   students[i].name, students[i].id, students[i].gpa, students[i].major);
            found++;
        }
    }
    if (found == 0) printf("No students match this threshold.\n");
}

void findByMajor(void) {
    if (studentCount == 0) {
        printf("\n[Notice] Registry is empty.\n");
        return;
    }

    char searchMajor[50];
    printf("\nEnter Major to query: ");
    fgets(searchMajor, sizeof(searchMajor), stdin);
    searchMajor[strcspn(searchMajor, "\n")] = '\0';

    printf("\nStudents in %s:\n", searchMajor);
    int count = 0;
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].major, searchMajor) == 0) {
            printf("- %s (ID: %d | GPA: %.2f)\n", students[i].name, students[i].id, students[i].gpa);
            count++;
        }
    }
    printf("Total headcount for %s: %d\n", searchMajor, count);
}

void saveStudentsToFile(void) {
    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        printf("\nCannot open file to save.\n");
        return;
    }

    // Dynamic key-value pairs written out directly
    fprintf(file, "CAPACITY=%d\n", maxCapacity);

    for (int i = 0; i < studentCount; i++) {
        fprintf(file, "%d|%s|%s|%.2f|%d\n",
                students[i].id, students[i].name, students[i].major, students[i].gpa, students[i].credits);
    }

    fclose(file);
    printf("[Success] Saved configuration and %d records securely to %s.\n", studentCount, fileName);
}

void loadStudentsFromFile(void) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("No existing file found. Instantiating dynamic runtime defaults.\n");
        saveStudentsToFile();
        return;
    }

    char line[300];
    studentCount = 0;

    while (fgets(line, sizeof(line), file)) {
        // Parse options directly out of the text configurations
        if (sscanf(line, " CAPACITY=%d", &maxCapacity) == 1 || sscanf(line, " capacity=%d", &maxCapacity) == 1) {
            continue; 
        }

        if (studentCount >= maxCapacity) break;

        Student s;
        if (sscanf(line, "%d|%[^|]|%[^|]|%f|%d", &s.id, s.name, s.major, &s.gpa, &s.credits) == 5) {
            students[studentCount] = s;
            studentCount++;
        }
    }

    fclose(file);
    printf("Loaded storage. System configuration parameters set dynamically to: %d\n", maxCapacity);
}