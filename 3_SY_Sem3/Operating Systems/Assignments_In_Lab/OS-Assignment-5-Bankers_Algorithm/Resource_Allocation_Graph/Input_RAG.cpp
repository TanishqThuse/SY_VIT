#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class ResourceAllocationGraph {
private:
    int numProcesses;
    int numResources;
    vector<vector<int>> allocation; // Allocation matrix
    vector<vector<int>> request;    // Request matrix
    vector<int> available;          // Available resources
    vector<vector<int>> maxDemand;  // Maximum demand for resources

public:
    ResourceAllocationGraph(int processes, int resources) {
        numProcesses = processes;
        numResources = resources;
        allocation.resize(processes, vector<int>(resources, 0));
        request.resize(processes, vector<int>(resources, 0));
        available.resize(resources, 0);
        maxDemand.resize(processes, vector<int>(resources, 0));
    }

    void setAvailableResources() {
        cout << "Enter available resources for " << numResources << " resources: ";
        for (int i = 0; i < numResources; i++) {
            cin >> available[i];
        }
    }

    void setMaxDemand() {
        cout << "Enter the maximum demand for each process and each resource:\n";
        for (int i = 0; i < numProcesses; i++) {
            cout << "Process P" << i << ": ";
            for (int j = 0; j < numResources; j++) {
                cin >> maxDemand[i][j];
            }
        }
    }

    void requestResources() {
        for (int i = 0; i < numProcesses; i++) {
            cout << "Enter the resource request for process P" << i << ": ";
            for (int j = 0; j < numResources; j++) {
                cin >> request[i][j];
            }
        }
    }

    void allocateResources() {
        for (int i = 0; i < numProcesses; i++) {
            for (int j = 0; j < numResources; j++) {
                allocation[i][j] += request[i][j];
                available[j] -= request[i][j];
                request[i][j] = 0;
            }
        }
    }

    bool isDeadlock() {
        vector<bool> finish(numProcesses, false);
        vector<int> work = available;
        queue<int> q;

        for (int i = 0; i < numProcesses; i++) {
            if (!finish[i]) {
                bool canProceed = true;
                for (int j = 0; j < numResources; j++) {
                    if (request[i][j] > work[j]) {
                        canProceed = false;
                        break;
                    }
                }
                if (canProceed) {
                    finish[i] = true;
                    q.push(i);
                    for (int j = 0; j < numResources; j++) {
                        work[j] += allocation[i][j];
                    }
                }
            }
        }

        // Check if there is any process that could not finish
        for (int i = 0; i < numProcesses; i++) {
            if (!finish[i]) {
                cout << "Deadlock detected involving process P" << i << endl;
                return true;
            }
        }

        cout << "No deadlock detected." << endl;
        return false;
    }
};

int main() {
    int processes, resources;

    cout << "Enter the number of processes: ";
    cin >> processes;
    cout << "Enter the number of resources: ";
    cin >> resources;

    ResourceAllocationGraph rag(processes, resources);

    // Set available resources
    rag.setAvailableResources();

    // Set maximum demand for each process
    rag.setMaxDemand();

    // Request resources for each process
    rag.requestResources();

    // Allocate resources to processes
    rag.allocateResources();

    // Check for deadlock
    rag.isDeadlock();

    return 0;
}

/**List of input :
 * Enter the number of processes: 5
Enter the number of resources: 3
Enter available resources for 3 resources: 3 3 2
Enter the maximum demand for each process and each resource:
Process P0: 7 5 3
Process P1: 3 2 2
Process P2: 9 0 2
Process P3: 2 2 2
Process P4: 4 3 3
Enter the resource request for process P0: 0 1 0
Enter the resource request for process P1: 2 0 0
Enter the resource request for process P2: 3 0 2
Enter the resource request for process P3: 2 1 1
Enter the resource request for process P4: 0 0 2
Deadlock detected involving process P0clear

 */