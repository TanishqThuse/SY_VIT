#include<stdio.h>

static int mark[20];
int i, j, np, nr;

int main() {
    int alloc[10][10], request[10][10], avail[10], r[10], w[10];

    printf("\nEnter the no of process: ");
    scanf("%d", &np);

    printf("\nEnter the no of resources: ");
    scanf("%d", &nr);

    // Arrays alloc[10][10] and request[10][10] store the allocation and request matrices for each process, respectively.
    // avail[10] stores the number of available resources of each type.
    // r[10] stores the total amount of each resource type.
    // w[10] is a working array used to track the available resources during the deadlock detection process.

    // Input total resources
    for(i = 0; i < nr; i++) {
        printf("\nTotal Amount of the Resource R%d: ", i + 1);
        scanf("%d", &r[i]);
    }

    // Input request matrix
    printf("\nEnter the request matrix:\n");
    for(i = 0; i < np; i++) {
        for(j = 0; j < nr; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    // Input allocation matrix
    printf("\nEnter the allocation matrix:\n");
    for(i = 0; i < np; i++) {
        for(j = 0; j < nr; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Calculate available resources
    for(j = 0; j < nr; j++) {
        avail[j] = r[j];
        for(i = 0; i < np; i++) {
            avail[j] -= alloc[i][j];
        }
    }

    // Mark processes with zero allocation
    for(i = 0; i < np; i++) {
        int count = 0;
        for(j = 0; j < nr; j++) {
            if(alloc[i][j] == 0) {
                count++;
            } else {
                break;
            }
        }
        if(count == nr) {
            mark[i] = 1;
        }
    }

    // Initialize work array with available resources
    for(j = 0; j < nr; j++) {
        w[j] = avail[j];
    }

    // Mark processes whose requests can be satisfied
    for(i = 0; i < np; i++) {
        int canbeprocessed = 0;
        if(mark[i] != 1) {
            for(j = 0; j < nr; j++) {
                if(request[i][j] <= w[j]) {
                    canbeprocessed = 1;
                } else {
                    canbeprocessed = 0;
                    break;
                }
            }
            if(canbeprocessed) {
                mark[i] = 1;
                for(j = 0; j < nr; j++) {
                    w[j] += alloc[i][j];
                }
            }
        }
    }

    // Check for unmarked processes (deadlock detection)
    int deadlock = 0;
    for(i = 0; i < np; i++) {
        if(mark[i] != 1) {
            deadlock = 1;
        }
    }

    // Output result
    if(deadlock) {
        printf("\nDeadlock detected");
    } else {
        printf("\nNo Deadlock possible");
    }

    return 0;
}

/*
 * Enter the no of process: 4

Enter the no of resources: 5

Total Amount of the Resource R1:
2

Total Amount of the Resource R2: 1

Total Amount of the Resource R3: 1

Total Amount of the Resource R4: 2

Total Amount of the Resource R5: 1

Enter the request matrix:0 1 0 0 1
0 0 1 0 1
0 0 0 0 1
1 0 1 0 1

Enter the allocation matrix:1 0 1 1 0
1 1 0 0 0
0 0 0 1 0
0 0 0 0 0

 Deadlock detected
 * */
