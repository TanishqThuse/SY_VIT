#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
} Node;

typedef struct Queue{
    Node* front;
    Node* rear;
} Queue;

Queue* Initialize();
void Enqueue(int x);
int Dequeue();
void Display();
int IsEmpty();
int peek();

Queue *q;

Queue* Initialize(){
    q = (Queue *)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void Enqueue(int x){
    Node* temp = (Node*)malloc(sizeof(Node));
    if (!temp){
        printf("Memory error\n");
        return;
    }
    temp->data = x;
    temp->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = temp;
    } else {
        q->rear->next = temp;
        q->rear = temp;
    }
    printf("%d enqueued to queue\n", x);
}

int Dequeue(){
    if(IsEmpty()){
        printf("Queue is empty\n");
        return -1;
    }
    Node* temp = q->front;
    int x = temp->data;
    
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    printf("%d dequeued from queue\n", x);
    return x;
}

int IsEmpty(){
    return (q->front == NULL);
}

void Display(){
    if (IsEmpty()){
        printf("Queue is empty\n");
        return;
    }
    Node* temp = q->front;
    while (temp) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int peek(){
    if (IsEmpty()) {
        printf("Queue is empty\n");
        return -1;
    } else {
        return q->front->data;
    }
}

int main(){
    int choice, value;
    
    Initialize();

    do {
        printf("\nQueue Operations Menu:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Peek\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter the value to enqueue: ");
                scanf("%d", &value);
                Enqueue(value);
                break;

            case 2:
                Dequeue();
                break;

            case 3:
                Display();
                break;

            case 4:
                value = peek();
                if(value != -1)
                    printf("Peek: %d\n", value);
                break;

            case 5:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice, please try again.\n");
        }
    } while(choice != 5);

    while (!IsEmpty()) {
        Dequeue();
    }
    
    free(q);
    return 0;
}



// #include<stdio.h>
// #include<stdlib.h>

// typedef struct Node{
//     int data;
//     struct Node* next;
// } Node;

// typedef struct Queue{
//     Node* front;
//     Node* rear;
// } Queue;

// Queue* Initialize();
// void Enqueue(int x);
// int Dequeue();
// void Display();
// int IsEmpty();
// int peek();

// Queue *q;

// // Function to initialize the queue
// Queue* Initialize(){
//     q = (Queue *)malloc(sizeof(Queue));
//     q->front = q->rear = NULL;
//     return q;
// }

// // Function to enqueue an element into the queue
// void Enqueue(int x){
//     Node* temp = (Node*)malloc(sizeof(Node));
//     if (!temp){
//         printf("Memory error\n");
//         return;
//     }
//     temp->data = x;
//     temp->next = NULL;
//     if (q->rear == NULL) {
//         // If the queue is empty, both front and rear are the new node
//         q->front = q->rear = temp;
//     } else {
//         // Add the new node at the end of the queue and update rear
//         q->rear->next = temp;
//         q->rear = temp;
//     }
//     printf("%d enqueued to queue\n", x);
// }

// // Function to dequeue an element from the queue
// int Dequeue(){
//     if(IsEmpty()){
//         printf("Queue is empty\n");
//         return -1;
//     }
//     Node* temp = q->front;
//     int x = temp->data;
    
//     q->front = q->front->next;
//     if (q->front == NULL) {
//         q->rear = NULL;
//     }
//     free(temp);  // Free the memory of dequeued node
//     printf("%d dequeued from queue\n", x);
//     return x;
// }

// // Function to check if the queue is empty
// int IsEmpty(){
//     return (q->front == NULL);
// }

// // Function to display the elements of the queue
// void Display(){
//     if (IsEmpty()){
//         printf("Queue is empty\n");
//         return;
//     }
//     Node* temp = q->front;
//     while (temp) {
//         printf("%d ", temp->data);
//         temp = temp->next;
//     }
//     printf("\n");
// }

// // Function to peek at the front element of the queue
// int peek(){
//     if (IsEmpty()) {
//         printf("Queue is empty\n");
//         return -1;
//     } else {
//         return q->front->data;
//     }
// }

// // Main function with a menu-driven interface
// int main(){
//     int choice, value;
    
//     Initialize();  // Initialize the linked list queue

//     do {
//         printf("\nQueue Operations Menu:\n");
//         printf("1. Enqueue\n");
//         printf("2. Dequeue\n");
//         printf("3. Display\n");
//         printf("4. Peek\n");
//         printf("5. Exit\n");
//         printf("Enter your choice: ");
//         scanf("%d", &choice);

//         switch(choice) {
//             case 1:  // Enqueue
//                 printf("Enter the value to enqueue: ");
//                 scanf("%d", &value);
//                 Enqueue(value);
//                 break;

//             case 2:  // Dequeue
//                 Dequeue();
//                 break;

//             case 3:  // Display
//                 Display();
//                 break;

//             case 4:  // Peek
//                 value = peek();
//                 if(value != -1)
//                     printf("Peek: %d\n", value);
//                 break;

//             case 5:  // Exit
//                 printf("Exiting program.\n");
//                 break;

//             default:
//                 printf("Invalid choice, please try again.\n");
//         }
//     } while(choice != 5);

//     // Free any remaining memory in the queue before exiting
//     while (!IsEmpty()) {
//         Dequeue();
//     }
    
//     free(q);  // Free the queue structure itself
//     return 0;
// }
