#include <iostream>
using namespace std;

int main()
{
    int n, m, i, j, k;
    
    // Input the number of processes and resources
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the number of resources: ";
    cin >> m;

    // Declare matrices and arrays
    int alloc[n][m], max[n][m], avail[m], f[n], ans[n], ind = 0;

    // Input Allocation Matrix
    cout << "Enter the allocation matrix (row by row):\n";
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            cin >> alloc[i][j];
        }
    }

    // Input Maximum Matrix
    cout << "Enter the maximum matrix (row by row):\n";
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            cin >> max[i][j];
        }
    }

    // Input Available Resources
    cout << "Enter the available resources:\n";
    for (i = 0; i < m; i++) {
        cin >> avail[i];
    }

    // Initialize flags array
    for (k = 0; k < n; k++) {
        f[k] = 0;
    }

    // Calculate the need matrix
    int need[n][m];
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Banker's Algorithm to find the safe sequence
    int y = 0;
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            if (f[i] == 0) {
                int flag = 0;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]){
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0) {
                    ans[ind++] = i;
                    for (y = 0; y < m; y++) {
                        avail[y] += alloc[i][y];
                    }
                    f[i] = 1;
                }
            }
        }
    }

    // Check if the system is in a safe state
    int flag = 1;
    for (i = 0; i < n; i++) {
        if (f[i] == 0) {
            flag = 0;
            cout << "The given sequence is not safe\n";
            break;
        }
    }

    // Print the safe sequence if it exists
    if (flag == 1) {
        cout << "Following is the SAFE Sequence:\n";
        for (i = 0; i < n - 1; i++) {
            cout << " P" << ans[i] << " ->";
        }
        cout << " P" << ans[n - 1] << endl;
    }

    return 0;
}

/*Input : 
Enter the number of processes: 5
Enter the number of resources: 3
Enter the allocation matrix (row by row):
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
Enter the maximum matrix (row by row):
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
Enter the available resources:
3 3 2
Following is the SAFE Sequence:
 P1 -> P3 -> P4 -> P0 -> P2*/

