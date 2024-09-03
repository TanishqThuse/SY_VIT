#include<stdio.h>
#include<stdlib.h>

struct Student {
    char name[100];
    int roll;
    float CPI;
    struct Student* next;
};

void createDataBase(struct Student std){
    struct Student* head;
    head = (struct Student*)malloc(sizeof(struct Student));
    head->next = NULL;
}

int main(){
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
            createDataBase(students);
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
