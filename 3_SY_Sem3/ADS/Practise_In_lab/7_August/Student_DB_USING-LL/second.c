#include<stdio.h>
#include<stdlib.h>

struct Node {
    int RollNo;
    char name[20];
    float CPI;
};

void createDataBase(struct Node* head, struct Node* prev,int n){
    // struct Node* new;
    // struct Node* prev;
    prev = head;
    for(int i=0; i<n; i++){
        printf("Enter details of student %d", i+1);
        printf("\nEnter roll no. : ");
        scanf("%d", &prev->RollNo);
        printf("\nSuccesfull");
    }

}

int main(){
    int ch;
    struct Node* head = (struct Node*)malloc(sizeof(struct Node));
    struct Node* prev = (struct Node*)malloc(sizeof(struct Node));
    // struct Node* next = (struct Node*)malloc(sizeof(struct Node));
    

    while(ch!=0){
        printf("Enter your choice\n");
        printf("1) Create a student Database\n");
        printf("2) Add a student in Database\n");
        printf("3) Display Students in Database\n");
        printf("4) Exit\n");

        scanf("%d",&ch);

        // switch (ch)
        // {
        // case 1:
        //     int n;
        //     // printf("Enter number of students\n");
        //     scanf("%d", &n);
        //     createDataBase(head, prev,n);
        //     break;
        
        // default:
        //     break;
        // }

    }

    return 0;
}