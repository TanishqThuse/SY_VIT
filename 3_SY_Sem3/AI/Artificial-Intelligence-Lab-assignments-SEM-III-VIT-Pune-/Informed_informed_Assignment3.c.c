#include <stdio.h>
#include <stdlib.h>

struct Node {
    int x, y;
    struct Node* parent;
    double g, h, f;
} Node;

    (Node* node, Node* goal) {
    return abs(node->x - goal->x) + abs(node->y - goal->y);
}

void printpath(int x, int y)


int main() {
   
    Node* start = (Node*)malloc(sizeof(Node));
    Node* goal = (Node*)malloc(sizeof(Node));
    
    
    start->g = 0;
    start->h = heuristic(start, goal);
    start->f = start->g + start->h;
    start->parent = NULL;
    
    
    while (open_list_is_not_empty) {
       
        Node* current = get_node_with_least_f(open_list);
        
        
        remove_node_from_open_list(open_list, current);

        if (current == goal) {
            
            Node* path_node = current;
            while (path_node != NULL) {
                path_node = path_node->parent;
            }
            break;  
        }
    }}
    