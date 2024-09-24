#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class ResourceAllocationGraph {
private:
    int numProcesses;
    int numResources;
    vector<vector<int>> allocation; // Allocation matrix
    vector<vector<int>> request;     // Request matrix
    vector<int> available;            // Available resources
    vector<int> maxDemand;            // Maximum demand for resources

public:
    ResourceAllocationGraph(int processes, int resources) {
        numProcesses = processes;
        numResources = resources;
        allocation.resize(processes, vector<int>(resources, 0));
        request.resize(processes, vector<int>(resources, 0));
        available.resize(resources, 0);
        maxDemand.resize(processes, 0);
    }

    void setAvailableResources(vector<int> avail) {
        available = avail;
    }

    void setMaxDemand(int process, vector<int> max) {
        maxDemand[process] = max[process];
    }

    void requestResources(int process, vector<int> req) {
        for (int i = 0; i < numResources; i++) {
            request[process][i] = req[i];
        }
    }

    void allocateResources(int process) {
        for (int i = 0; i < numResources; i++) {
            allocation[process][i] += request[process][i];
            available[i] -= request[process][i];
            request[process][i] = 0;
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
    int processes = 5;
    int resources = 3;

    ResourceAllocationGraph rag(processes, resources);

    // Set available resources
    rag.setAvailableResources({3, 3, 2});

    // Set maximum demand for each process
    rag.setMaxDemand(0, {7, 5, 3});
    rag.setMaxDemand(1, {3, 2, 2});
    rag.setMaxDemand(2, {9, 0, 2});
    rag.setMaxDemand(3, {2, 2, 2});
    rag.setMaxDemand(4, {4, 3, 3});

    // Request resources
    rag.requestResources(0, {0, 1, 0});
    rag.requestResources(1, {2, 0, 0});
    rag.requestResources(2, {3, 0, 2});
    rag.requestResources(3, {2, 1, 1});
    rag.requestResources(4, {0, 0, 2});

    // Allocate resources to processes
    rag.allocateResources(0);
    rag.allocateResources(1);
    rag.allocateResources(2);
    rag.allocateResources(3);
    rag.allocateResources(4);

    // Check for deadlock
    rag.isDeadlock();

    return 0;
}

