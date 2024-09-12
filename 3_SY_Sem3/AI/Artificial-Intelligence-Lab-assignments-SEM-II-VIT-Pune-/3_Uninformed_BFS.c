// Uninformed search  BFS algo .

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_VERTICES 100

int queue[MAX_VERTICES];
int front = -1, rear = -1;

void enqueue(int vertex) {
    if (rear == MAX_VERTICES - 1) {
        printf("Queue is full.\n");
    } else {
        if (front == -1) {
            front = 0;
        }
        rear++;
        queue[rear] = vertex;
    }
}

int dequeue() {
    int item;
    if (front == -1 || front > rear) {
        printf("Queue is empty.\n");
        item = -1;
    } else {
        item = queue[front];
        front++;
    }
    return item;
}

bool isEmpty() {
    return front == -1 || front > rear;
}

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node* graph[MAX_VERTICES];

void addEdge(int from, int to) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = to;
    newNode->next = graph[from];
    graph[from] = newNode;
}

void BFS(int startVertex, int vertices) {
    bool visited[MAX_VERTICES] = { false };
    printf("BFS traversal");

    visited[startVertex] = true;
    enqueue(startVertex);

    while (!isEmpty()) {
        int currentVertex = dequeue();
        printf("%d ", currentVertex);

        Node* temp = graph[currentVertex];
        while (temp != NULL) {
            int adjacentVertex = temp->vertex;
            if (!visited[adjacentVertex]) {
                visited[adjacentVertex] = true;
                enqueue(adjacentVertex);
            }
            temp = temp->next;
        }
    }
}

int main() {
    int vertices, edges;
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    for (int i = 0; i < vertices; i++) {
        graph[i] = NULL;
    }

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    printf("Enter the edges (from to): \n");
    for (int i = 0; i < edges; i++) {
        int from, to;
        scanf("%d %d", &from, &to);
        addEdge(from, to);
        //addEdge(to, from); 
    }

    int startVertex;
    printf("Enter the starting vertex: ");
    scanf("%d", &startVertex);

    BFS(startVertex, vertices);
    printf("\n");

    return 0;
}
