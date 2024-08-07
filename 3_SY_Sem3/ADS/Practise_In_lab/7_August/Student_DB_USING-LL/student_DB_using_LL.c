#include<stdio.h>
#include<stdlib.h>

struct Node {
    int RollNo;
    char name[20];
    float CPI;
    struct Node* next;
};

void createDataBase(struct Node* head, struct Node* prev,int n){
    // struct Node* new;
    // struct Node* prev;
    printf("Enter details of student %d", 1);
    printf("\nEnter roll no. : ");
    scanf("%d", &head->RollNo);
    printf("Enter name : ");
    scanf("%s", prev->name);
    printf("Enter CPI : ");
    scanf("%f",&prev->CPI);
    prev = head;
    for(int i=1; i<n; i++){
        struct Node* latest = (struct Node*)malloc(sizeof(struct Node));
        printf("Enter details of student %d", i+1);
        printf("\nEnter roll no. : ");
        scanf("%d", &latest->RollNo);
        printf("Enter name : ");
        scanf("%s", prev->name);
        printf("Enter CPI : ");
        scanf("%f",&prev->CPI);
        prev->next = latest;
        latest->next=NULL;
    }
    
}

void Display(struct Node* head){
    struct Node* temp = head;
    int i=1;
    while(temp!=NULL){
        printf("Details of student %d\n",i++);
        printf("Roll No. of student %d : \n", temp->RollNo);
        printf("Name of student %s : \n", temp->name);
        printf("CPI of student %f : \n", temp->CPI);
        printf("\n");
        temp = temp->next;
    }
}

int main(){
    int ch=1;
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

        switch (ch)
        {
        case 1:
            int n;
            printf("Enter number of students\n");
            scanf("%d", &n);
            createDataBase(head, prev,n);
            break;
        
        case 3:
            Display(head);
        default:
            break;
        }

    }

    return 0;
}