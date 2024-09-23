#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <iomanip>
using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
};

// Function to print the Gantt Chart
void printGanttChart(const vector<pair<int, int>> &ganttChart) {
    cout << "\nGantt Chart:\n";
    for (auto &p : ganttChart) {
        cout << "| P" << p.first << " ";
    }
    cout << "|\n0";
    for (auto &p : ganttChart) {
        cout << " " << p.second;
    }
    cout << endl;
}

// Function to print the process table and calculate average times
void printProcessTable(const vector<Process> &processes, double avgWT, double avgTAT) {
    cout << "\nProcess Table:\n";
    cout << setw(5) << "ID" 
         << setw(15) << "Arrival Time" 
         << setw(15) << "Burst Time"
         << setw(20) << "Completion Time" 
         << setw(15) << "Waiting Time"
         << setw(20) << "Turnaround Time" 
         << endl;

    for (auto &p : processes) {
        cout << setw(5) << p.id 
             << setw(15) << p.arrivalTime 
             << setw(15) << p.burstTime
             << setw(20) << p.completionTime 
             << setw(15) << p.waitingTime
             << setw(20) << p.turnaroundTime 
             << endl;
    }

    cout << "\nAverage Waiting Time: " << avgWT << endl;
    cout << "Average Turnaround Time: " << avgTAT << endl;
}

// Round Robin Scheduling Function
void roundRobin(vector<Process> &processes, int timeQuantum) {
    int n = processes.size();
    queue<int> q;
    set<int> inQueue; // To keep track of processes already in the queue
    vector<pair<int, int>> ganttChart;
    int currentTime = 0, completed = 0;
    double totalWT = 0, totalTAT = 0;

    // Add initial processes that have arrived at time 0
    for (int i = 0; i < n; ++i) {
        if (processes[i].arrivalTime <= currentTime) {
            q.push(i);
            inQueue.insert(i);
        }
    }

    while (completed < n) {
        if (q.empty()) {
            currentTime++;
            for (int i = 0; i < n; ++i) {
                if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0 && inQueue.find(i) == inQueue.end()) {
                    q.push(i);
                    inQueue.insert(i);
                }
            }
            continue;
        }

        int idx = q.front();
        q.pop();
        inQueue.erase(idx);
        ganttChart.push_back({processes[idx].id, currentTime});

        // Execute the process for time quantum or remaining time, whichever is smaller
        int executionTime = min(timeQuantum, processes[idx].remainingTime);
        currentTime += executionTime;
        processes[idx].remainingTime -= executionTime;

        // Add to the Gantt chart
        ganttChart.push_back({processes[idx].id, currentTime});

        // Check if the process is completed
        if (processes[idx].remainingTime == 0) {
            processes[idx].completionTime = currentTime;
            processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
            processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
            totalWT += processes[idx].waitingTime;
            totalTAT += processes[idx].turnaroundTime;
            completed++;
        }

        // Push the next arrived processes
        for (int i = 0; i < n; ++i) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0 && inQueue.find(i) == inQueue.end()) {
                q.push(i);
                inQueue.insert(i);
            }
        }

        // Reinsert the current process if it is not yet finished
        if (processes[idx].remainingTime > 0) {
            q.push(idx);
            inQueue.insert(idx);
        }
    }

    double avgWT = totalWT / n;
    double avgTAT = totalTAT / n;
    printGanttChart(ganttChart);
    printProcessTable(processes, avgWT, avgTAT);
}

int main() {
    int n, timeQuantum;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        cout << "Enter arrival time and burst time for process P" << i + 1 << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
    }

    cout << "Enter the time quantum: ";
    cin >> timeQuantum;

    roundRobin(processes, timeQuantum);

    return 0;
}
