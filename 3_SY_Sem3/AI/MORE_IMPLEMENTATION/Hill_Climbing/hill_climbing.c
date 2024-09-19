//Hill climbing

#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

typedef struct {
    int state;      
    int func_value; 
} Node;


int find_best_neighbor(Node neighbors[], int num_neighbors) {
    int best_index = 0;
    for (int i = 1; i < num_neighbors; i++) {
        if (neighbors[i].func_value > neighbors[best_index].func_value) {
            best_index = i;
        }
    }
    return best_index;
}


int hill_climbing(Node nodes[], int num_nodes, int start_index) {
    int current_index = start_index;
    int num_neighbors = 2;
    Node neighbors[2];
    
    while (1) {
       
        int left_index = -1, right_index = -1;
        for (int i = 0; i < num_nodes; i++) {
            if (nodes[i].state == nodes[current_index].state - 1) {
                left_index = i;
            }
            if (nodes[i].state == nodes[current_index].state + 1) {
                right_index = i;
            }
        }
        
        if (left_index == -1 && right_index == -1) {
            return nodes[current_index].state; // No neighbors
        }
        
        int num_valid_neighbors = 0;
        if (left_index != -1) {
            neighbors[num_valid_neighbors++] = nodes[left_index];
        }
        if (right_index != -1) {
            neighbors[num_valid_neighbors++] = nodes[right_index];
        }
        
        if (num_valid_neighbors == 0) {
            return nodes[current_index].state; 
        }
        
        int best_index = find_best_neighbor(neighbors, num_valid_neighbors);
        if (neighbors[best_index].func_value <= nodes[current_index].func_value) {
            return nodes[current_index].state; 
        }
        
        current_index = (neighbors[best_index].state == nodes[current_index].state - 1) ? left_index : right_index;
    }
}

int main() {
    int num_nodes;
    printf("Enter the number of nodes: ");
    scanf("%d", &num_nodes);
    
    if (num_nodes > MAX_NODES) {
        printf("Error: Maximum number of nodes is %d\n", MAX_NODES);
        return 1;
    }

    Node nodes[MAX_NODES];
    
    for (int i = 0; i < num_nodes; i++) {
        printf("Enter state (value) and function value for node %d: ", i);
        scanf("%d %d", &nodes[i].state, &nodes[i].func_value);
    }
    
    int start_index;
    printf("Enter the index of the starting node: ");
    scanf("%d", &start_index);
    
    if (start_index < 0 || start_index >= num_nodes) {
        printf("Error: Invalid starting index\n");
        return 1;
    }

    int result = hill_climbing(nodes, num_nodes, start_index);
    printf("Result: %d\n", result);
    
    return 0;
    /**
     * Enter the number of nodes: 5
    Enter state (value) and function value for node 0: 0 1
    Enter state (value) and function value for node 1: 1 3
    Enter state (value) and function value for node 2: 2 5
    Enter state (value) and function value for node 3: 3 2
    Enter state (value) and function value for node 4: 4 4
    Enter the index of the starting node: 0
     */
}