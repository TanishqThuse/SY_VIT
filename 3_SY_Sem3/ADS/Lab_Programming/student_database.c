#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char name[100];
    int roll;
    float CPI;
};

// Function to check for duplicate roll numbers and return a valid one
int checkRollNo(struct Student students[], int index) {
    int r;
    while (1) {
        printf("Enter roll number :\n");
        scanf("%d", &r);
        int duplicate = 0;
        for (int i = 0; i < index; i++) {
            if (students[i].roll == r) {
                printf("Roll number already exists. Please enter a different roll number\n");
                duplicate = 1;
                break;
            }
        }
        if (!duplicate) {
            return r;
        }
    }
}

// Function to add a student
void addStudent(struct Student students[], int index) {
    printf("Enter name :\n");
    scanf("%s", students[index].name);
    students[index].roll = checkRollNo(students, index);
    printf("Enter CPI :\n");
    scanf("%f", &students[index].CPI);
}

// Function to delete a student by roll number
int deleteStudent(struct Student students[], int index) {
    printf("Enter roll no. of student to delete\n");
    int r;
    scanf("%d", &r);
    int found = 0;
    for (int i = 0; i < index; i++) {
        if (students[i].roll == r) {
            found = 1;
            for (int j = i; j < index - 1; j++) {
                students[j] = students[j + 1];
            }
            index--;
            break;
        }
    }
    if (!found) {
        printf("Roll number not found\n");
    }
    return index;
}

// Function to display all students
void displayStudents(struct Student students[], int index) {
    for (int i = 0; i < index; i++) {
        printf("Name of student : %s\n", students[i].name);
        printf("Roll number of student : %d\n", students[i].roll);
        printf("CPI of student : %f\n", students[i].CPI);
        printf("\n");
    }
}

int createDataBase(struct Student students[]){
    int index=0;
    int n ;
    printf("Enter number of students\n");
    scanf("%d", &n);   
    for(int i=0; i<n; i++){
        addStudent(students, index++);
    }
    return index;
}

int main() {
    int index = 0;
    int flag = 0;
    struct Student students[50];

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
            index = createDataBase(students);
            break;
        
        case 1:
            addStudent(students, index);
            index++;
            break;
        case 2:
            index = deleteStudent(students, index);
            break;
        case 3:
            displayStudents(students, index);
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

    return 0;
}
