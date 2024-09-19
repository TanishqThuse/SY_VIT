#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_VERTICES 100

int graph[MAX_VERTICES][MAX_VERTICES];
int visited[MAX_VERTICES];
int vertices, edges;

// Stack implementation for DFS
struct Stack {
    int items[MAX_VERTICES];
    int top;
};

void initializeStack(struct Stack* stack) {
    stack->top = -1;
}

void push(struct Stack* stack, int value) {
    stack->top++;
    stack->items[stack->top] = value;
}

int pop(struct Stack* stack) {
    int item = stack->items[stack->top];
    stack->top--;
    return item;
}

bool isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Depth-Limited Search algorithm
void depthLimitedSearch(int startVertex, int depthLimit) {
    struct Stack stack;
    initializeStack(&stack);
    push(&stack, startVertex);
    visited[startVertex] = 1;

    printf("Depth-Limited Search starting from vertex %d with depth limit %d:\n", startVertex, depthLimit);

    while (!isEmpty(&stack)) {
        int currentVertex = pop(&stack);
        printf("%d ", currentVertex);

        if (currentVertex == depthLimit) {
            printf("\nReached the depth limit %d\n", depthLimit);
            return;
        }

        for (int i = 0; i < vertices; ++i) {
            if (graph[currentVertex][i] == 1 && !visited[i]) {
                push(&stack, i);
                visited[i] = 1;
            }
        }
    }
    printf("\nNo further nodes to explore.\n");
}

int main() {
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    for (int i = 0; i < vertices; i++) {
        visited[i] = 0;
        for (int j = 0; j < vertices; j++)
            graph[i][j] = 0;
    }

    printf("Enter the edges (format: vertex1 vertex2):\n");
    for (int i = 0; i < edges; i++) {
        int vertex1, vertex2;
        scanf("%d %d", &vertex1, &vertex2);
        graph[vertex1][vertex2] = 1;
        graph[vertex2][vertex1] = 1;
    }

    int startVertex, depthLimit;
    printf("Enter the starting vertex for DLFS: ");
    scanf("%d", &startVertex);

    printf("Enter the depth limit for DLFS: ");
    scanf("%d", &depthLimit);

    depthLimitedSearch(startVertex, depthLimit);
    printf("\n");

    return 0;

    /** Visualization
            0
           / \
          1   2
         / \  \
        3  4  5
     */

    /**Enter the number of vertices: 6
    Enter the number of edges: 5
    Enter the edges (format: vertex1 vertex2):
    0 1
    0 2
    1 3
    1 4
    2 5
    Enter the starting vertex for DLFS: 0
    Enter the depth limit for DLFS: 2
    Depth-Limited Search starting from vertex 0 with depth limit 2:
    0 2 1 
    Reached the depth limit 2 */
}
