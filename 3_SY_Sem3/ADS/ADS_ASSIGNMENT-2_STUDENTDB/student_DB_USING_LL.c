#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure to represent a Student
typedef struct Student {
    int rollNo;
    char name[100];
    int age;
    struct Student* next;
} Student;

// Function prototypes
void addStudent(Student** head);
void viewStudents(const Student* head);
void deleteStudent(Student** head);

int main() {
    Student* head = NULL;
    int choice;

    while (1) {
        printf("Student Database Menu:\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Delete Student\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(&head);
                break;
            case 2:
                viewStudents(head);
                break;
            case 3:
                deleteStudent(&head);
                break;
            case 4:
                // Free the allocated memory before exiting
                while (head != NULL) {
                    Student* temp = head;
                    head = head->next;
                    free(temp);
                }
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// Function to add a student
void addStudent(Student** head) {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    if (newStudent == NULL) {
        printf("Memory allocation failed. Cannot add student.\n");
        return;
    }

    printf("Enter student roll number: ");
    scanf("%d", &newStudent->rollNo);
    printf("Enter student name: ");
    scanf("%s", newStudent->name);
    printf("Enter student age: ");
    scanf("%d", &newStudent->age);

    newStudent->next = *head;
    *head = newStudent;

    printf("Student added successfully.\n");
}

// Function to view all students
void viewStudents(const Student* head) {
    if (head == NULL) {
        printf("No students in the database.\n");
        return;
    }

    printf("Student Records:\n");
    const Student* current = head;
    while (current != NULL) {
        printf("Roll No: %d, Name: %s, Age: %d\n", current->rollNo, current->name, current->age);
        current = current->next;
    }
}

// Function to delete a student
void deleteStudent(Student** head) {
    if (*head == NULL) {
        printf("No students to delete.\n");
        return;
    }

    int rollNo;
    printf("Enter student roll number to delete: ");
    scanf("%d", &rollNo);

    Student* current = *head;
    Student* previous = NULL;

    while (current != NULL && current->rollNo != rollNo) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Student not found.\n");
        return;
    }

    if (previous == NULL) {
        *head = current->next;
    } else {
        previous->next = current->next;
    }

    free(current);
    printf("Student deleted successfully.\n");
}
