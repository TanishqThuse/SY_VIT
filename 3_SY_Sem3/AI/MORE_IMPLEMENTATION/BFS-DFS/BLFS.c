#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_VERTICES 100

struct Queue {
    int items[MAX_VERTICES];
    int front, rear;
};

int graph[MAX_VERTICES][MAX_VERTICES];
int visited_start[MAX_VERTICES];
int visited_goal[MAX_VERTICES];
int vertices, edges;

struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

void enqueue(struct Queue* q, int value) {
    if (q->rear == MAX_VERTICES - 1)
        printf("Queue is full\n");
    else {
        if (q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

int dequeue(struct Queue* q) {
    int item;
    if (q->front == -1) {
        printf("Queue is empty\n");
        return -1;
    } else {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            q->front = q->rear = -1;
        }
        return item;
    }
}

// Function to check if any common vertex is visited by both searches
int isIntersecting() {
    for (int i = 0; i < vertices; i++) {
        if (visited_start[i] && visited_goal[i])
            return i;  // Return the intersecting vertex
    }
    return -1;
}

// Bidirectional BFS algorithm
void bidirectionalBFS(int startVertex, int goalVertex) {
    struct Queue* q_start = createQueue();
    struct Queue* q_goal = createQueue();

    // Initialize visited arrays for both searches
    visited_start[startVertex] = 1;
    visited_goal[goalVertex] = 1;

    enqueue(q_start, startVertex);
    enqueue(q_goal, goalVertex);

    printf("Bidirectional BFS from vertex %d to vertex %d:\n", startVertex, goalVertex);

    while (q_start->front != -1 && q_goal->front != -1) {
        // BFS from start vertex
        int current_start = dequeue(q_start);
        printf("Start search visiting: %d\n", current_start);

        for (int i = 0; i < vertices; ++i) {
            if (graph[current_start][i] == 1 && !visited_start[i]) {
                visited_start[i] = 1;
                enqueue(q_start, i);
            }
        }

        // BFS from goal vertex
        int current_goal = dequeue(q_goal);
        printf("Goal search visiting: %d\n", current_goal);

        for (int i = 0; i < vertices; ++i) {
            if (graph[current_goal][i] == 1 && !visited_goal[i]) {
                visited_goal[i] = 1;
                enqueue(q_goal, i);
            }
        }

        // Check for intersection between the two searches
        int intersecting_vertex = isIntersecting();
        if (intersecting_vertex != -1) {
            printf("Path found! The searches intersect at vertex %d\n", intersecting_vertex);
            return;
        }
    }

    printf("No path found between vertex %d and vertex %d\n", startVertex, goalVertex);
}

int main() {
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    for (int i = 0; i < vertices; i++) {
        visited_start[i] = 0;
        visited_goal[i] = 0;
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

    int startVertex, goalVertex;
    printf("Enter the starting vertex for BLFS: ");
    scanf("%d", &startVertex);

    printf("Enter the goal vertex for BLFS: ");
    scanf("%d", &goalVertex);

    bidirectionalBFS(startVertex, goalVertex);
    printf("\n");

    return 0;

    /**Visualization : 
     *    0
         / \
         1  2
        / \  \
        3  4  5

     */
}
