#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char name[100];
    int roll;
    float CPI;
    struct Student* next;
};

int checkRollNo(struct Student* head, int roll) {
    struct Student* current = head;
    while (current != NULL) {
        if (current->roll == roll) {
            return 0;
        }
        current = current->next;
    }
    return 1;
}

struct Student* createStudentNode(char* name, int roll, float CPI) {
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
    strcpy(newStudent->name, name);
    newStudent->roll = roll;
    newStudent->CPI = CPI;
    newStudent->next = NULL;
    return newStudent;
}

void addStudent(struct Student** head) {
    char name[100];
    int roll;
    float CPI;

    printf("Enter name :\n");
    scanf("%s", name);
    
    while (1) {
        printf("Enter roll number :\n");
        scanf("%d", &roll);
        if (checkRollNo(*head, roll)) {
            break;
        } else {
            printf("Roll number already exists. Please enter a different roll number\n");
        }
    }
    
    printf("Enter CPI :\n");
    scanf("%f", &CPI);

    struct Student* newStudent = createStudentNode(name, roll, CPI);
    newStudent->next = *head;
    *head = newStudent;
}

void deleteStudent(struct Student** head) {
    int roll;
    printf("Enter roll no. of student to delete\n");
    scanf("%d", &roll);

    struct Student* current = *head;
    struct Student* previous = NULL;

    while (current != NULL && current->roll != roll) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Roll number not found\n");
        return;
    }

    if (previous == NULL) {
        *head = current->next;
    } else {
        previous->next = current->next;
    }
    free(current);
}

void displayStudents(struct Student* head) {
    struct Student* current = head;
    while (current != NULL) {
        printf("Name of student : %s\n", current->name);
        printf("Roll number of student : %d\n", current->roll);
        printf("CPI of student : %f\n", current->CPI);
        printf("\n");
        current = current->next;
    }
}

void createDataBase(struct Student** head) {
    int n;
    printf("Enter number of students\n");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        addStudent(head);
    }
}

int main() {
    struct Student* head = NULL;
    int flag = 0;

    while (1) {
        printf("Enter your choice : \n");
        printf("0) Create Student Database\n");
        printf("1) Add student\n");
        printf("2) Delete student\n");
        printf("3) Display student\n");
        printf("4) Exit\n\n");

        int choice;
        scanf("%d", &choice);
        switch (choice) {
        case 0:
            createDataBase(&head);
            break;
        case 1:
            addStudent(&head);
            break;
        case 2:
            deleteStudent(&head);
            break;
        case 3:
            displayStudents(head);
            break;
        case 4:
            flag = 1;
            break;
        default:
            printf("Invalid choice. Please try again\n");
            break;
        }

        if (flag) {
            break;
        }
    }

    struct Student* current = head;
    while (current != NULL) {
        struct Student* next = current->next;
        free(current);
        current = next;
    }

    return 0;
}
