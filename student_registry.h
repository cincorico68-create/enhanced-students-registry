#ifndef STUDENT_REGISTRY_H
#define STUDENT_REGISTRY_H

#define MAX_STUDENTS 100

// Student Data Structure
typedef struct {
    int id;
    char name[100];
    char major[50];
    float gpa;
    int credits;
} Student;

// Function Declarations (Interface)
void addStudent(void);
void displayAllStudents(void);
void searchStudentByID(void);
void searchStudentByMajor(void);
void searchStudentByGPA(void);
void saveStudentsToFile(void);
void loadStudentsFromFile(void);

#endif // STUDENT_REGISTRY_H