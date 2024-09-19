#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define ROWS 5
#define COLS 5

typedef struct Node {
    struct Node* parent;
    int position[2];
    int g;
    int h;
    int f;
} Node;

Node* createNode(Node* parent, int row, int col) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->parent = parent;
    newNode->position[0] = row;
    newNode->position[1] = col;
    newNode->g = 0;
    newNode->h = 0;
    newNode->f = 0;
    return newNode;
}

bool isValid(int row, int col) {
    return (row >= 0 && row < ROWS && col >= 0 && col < COLS);
}

bool isObstacle(int maze[ROWS][COLS], int row, int col) {
    return (maze[row][col] == 1);
}

bool isDestination(int row, int col, int end[2]) {
    return (row == end[0] && col == end[1]);
}

int calculateHValue(int current[2], int end[2]) {
    return (int)(pow((current[0] - end[0]), 2) + pow((current[1] - end[1]), 2));
}

void printPath(Node* current) {
    if (current == NULL) {
        return;
    }
    printPath(current->parent);
    printf("(%d, %d)\n", current->position[0], current->position[1]);
}

void printMaze(int maze[ROWS][COLS], Node* currentNode, int start[2], int end[2]) {
    char visualMaze[ROWS][COLS];
    
    // Initialize the visualization maze based on the original maze
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (maze[i][j] == 1) {
                visualMaze[i][j] = '#';  // Obstacle
            } else {
                visualMaze[i][j] = '.';  // Empty space
            }
        }
    }

    // Mark the start and end positions
    visualMaze[start[0]][start[1]] = 'S';
    visualMaze[end[0]][end[1]] = 'E';

    // Mark the current node as being visited
    visualMaze[currentNode->position[0]][currentNode->position[1]] = 'X';

    // Print the maze
    printf("\nMaze visualization:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c ", visualMaze[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

bool aStar(int maze[ROWS][COLS], int start[2], int end[2]) {
    Node* startNode = createNode(NULL, start[0], start[1]);
    startNode->g = startNode->h = startNode->f = 0;
    
    Node* endNode = createNode(NULL, end[0], end[1]);
    endNode->g = endNode->h = endNode->f = 0;
    
    Node* priorityQueue[ROWS * COLS];
    int queueSize = 0;
    priorityQueue[queueSize++] = startNode;
    
    while (queueSize > 0) {
        int minIndex = 0;
        for (int i = 1; i < queueSize; i++) {
            if (priorityQueue[i]->f < priorityQueue[minIndex]->f) {
                minIndex = i;
            }
        }
        
        Node* currentNode = priorityQueue[minIndex];
        
        for (int i = minIndex; i < queueSize - 1; i++) {
            priorityQueue[i] = priorityQueue[i + 1];
        }
        queueSize--;
        
        if (isDestination(currentNode->position[0], currentNode->position[1], end)) {
            printf("Path:\n");
            printPath(currentNode);
            return true;
        }
        
        // Visualization: print the maze after visiting this node
        printMaze(maze, currentNode, start, end);

        int directions[8][2] = {
            {0, -1}, {0, 1}, {-1, 0}, {1, 0},
            {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
        };
        
        for (int i = 0; i < 8; i++) {
            int newRow = currentNode->position[0] + directions[i][0];
            int newCol = currentNode->position[1] + directions[i][1];
            
            if (isValid(newRow, newCol) && !isObstacle(maze, newRow, newCol)) {
                Node* newNode = createNode(currentNode, newRow, newCol);
                newNode->g = currentNode->g + 1;
                newNode->h = calculateHValue(newNode->position, end);
                newNode->f = newNode->g + newNode->h;
                
                priorityQueue[queueSize++] = newNode;
            }
        }
    }
    
    printf("No path found.\n");
    return false;
}

int main() {
    int maze[ROWS][COLS] = {
        {0, 0, 0, 0, 1},
        {0, 1, 1, 0, 0},
        {0, 0, 1, 0, 1},
        {0, 1, 0, 0, 1},
        {0, 0, 0, 0, 0}
    };
    
    int start[2], end[2];
    
    printf("Enter the start position (row, column): ");
    scanf("%d %d", &start[0], &start[1]);
    
    printf("Enter the end position (row, column): ");
    scanf("%d %d", &end[0], &end[1]);
    
    if (!aStar(maze, start, end)) {
        printf("No path found.\n");
    }
    
    /**
    Enter the start position (row, column): 0 0
    Enter the end position (row, column): 4 4 */

    return 0;
}
