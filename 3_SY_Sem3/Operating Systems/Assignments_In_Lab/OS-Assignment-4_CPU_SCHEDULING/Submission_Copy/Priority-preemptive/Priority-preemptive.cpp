#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int priority;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
};

// Function to print the process table and calculate average times
void printProcessTable(const vector<Process> &processes, double avgWT, double avgTAT) {
    cout << "\nProcess Table:\n";
    cout << setw(5) << "ID" 
         << setw(15) << "Arrival Time" 
         << setw(15) << "Burst Time"
         << setw(10) << "Priority" 
         << setw(20) << "Completion Time"
         << setw(15) << "Waiting Time" 
         << setw(20) << "Turnaround Time" 
         << endl;

    for (const auto &p : processes) {
        cout << setw(5) << p.id 
             << setw(15) << p.arrivalTime 
             << setw(15) << p.burstTime
             << setw(10) << p.priority 
             << setw(20) << p.completionTime
             << setw(15) << p.waitingTime 
             << setw(20) << p.turnaroundTime 
             << endl;
    }

    cout << "\nAverage Waiting Time: " << avgWT << endl;
    cout << "Average Turnaround Time: " << avgTAT << endl;
}

// Priority Preemptive Scheduling Function
void priorityPreemptive(vector<Process> &processes) {
    int n = processes.size();
    vector<int> isCompleted(n, 0);
    double totalWT = 0, totalTAT = 0;
    int currentTime = 0, completed = 0;
    int lastExecution = -1;

    while (completed < n) {
        int idx = -1;
        int highestPriority = -1;

        // Find the highest priority process that has arrived and is not completed
        for (int i = 0; i < n; ++i) {
            if (processes[i].arrivalTime <= currentTime && !isCompleted[i]) {
                if (processes[i].priority > highestPriority) {
                    highestPriority = processes[i].priority;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            if (lastExecution != idx) {
                lastExecution = idx;
            }

            processes[idx].remainingTime--;
            currentTime++;

            // If the process is completed
            if (processes[idx].remainingTime == 0) {
                processes[idx].completionTime = currentTime;
                processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
                processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
                totalWT += processes[idx].waitingTime;
                totalTAT += processes[idx].turnaroundTime;
                isCompleted[idx] = 1;
                completed++;
            }
        } else {
            currentTime++;
        }
    }

    double avgWT = totalWT / n;
    double avgTAT = totalTAT / n;
    printProcessTable(processes, avgWT, avgTAT);
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        cout << "Enter arrival time, burst time, and priority for process P" << i + 1 << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime >> processes[i].priority;
        processes[i].remainingTime = processes[i].burstTime;
    }

    priorityPreemptive(processes);

    return 0;
}
