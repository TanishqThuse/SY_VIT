#include<stdio.h>
#include<stdlib.h>

typedef struct Queue{
    int front;
    int rear;
    int size;
    int arr[5];
} Queue;

struct Queue* Initialize();
void Enqueue(int x);
int Dequeue();
void Display();
int IsEmpty();
int IsFull();
int peek();

Queue *q ;

struct Queue* Initialize(){
    q = (Queue *)malloc(sizeof(Queue));
    q->front = q->rear = -1;
    q->size = 5;
    return q;
}

void Enqueue(int x){
    if(IsFull()){
        printf("Queue is full\n");
    }
    else{
        q->rear++;
        q->arr[q->rear] = x;
    }
}

int Dequeue(){
    int x = -1;
    if(IsEmpty()){
        printf("Queue is empty\n");
    }
    else{
        q->front++;
        x = q->arr[q->front];
    }
}

int IsEmpty(){
    if(q->front == q->rear){
        return 1;
    }
    else{
        return 0;
    }
}

int IsFull(){
    if(q->rear == q->size-1){
        return 1;
    }
    else{
        return 0;
    }
}

void Display(){
    for(int i=q->front+1; i<=q->rear; i++){
        printf("%d ", q->arr[i]);
    }
    printf("\n");
}

int peek(){
    if(IsEmpty()){
        printf("Queue is empty\n");
    }
    else{
        return q->arr[q->front+1];
    }
}

int main(){
    Initialize();
    Enqueue(10);
    Enqueue(20);
    Enqueue(30);
    Enqueue(40);
    Enqueue(50);
    Display();
    printf("%d\n",Dequeue());
    Display();
    printf("%d\n", peek());
    return 0;
}