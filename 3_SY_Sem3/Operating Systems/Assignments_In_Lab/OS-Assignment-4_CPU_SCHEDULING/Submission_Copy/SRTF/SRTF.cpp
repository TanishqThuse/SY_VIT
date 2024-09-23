#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>

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

void printGanttChart(const vector<int> &ganttChart, int totalTime) {
    cout << "\nGantt Chart:\n";
    for (int i = 0; i < totalTime; i++) {
        cout << "| P" << ganttChart[i] << " ";
    }
    cout << "|\n0";
    for (int i = 1; i <= totalTime; i++) {
        cout << " " << i;
    }
    cout << endl;
}

void printProcessTable(const vector<Process> &processes, double avgWT, double avgTAT) {
    cout << "\nProcess Table:\n";
    cout << setw(5) << "ID" << setw(15) << "Arrival Time" 
         << setw(15) << "Burst Time" << setw(20) << "Completion Time" 
         << setw(15) << "Waiting Time" << setw(20) << "Turnaround Time" << endl;

    for (const auto &p : processes) {
        cout << setw(5) << p.id << setw(15) << p.arrivalTime 
             << setw(15) << p.burstTime << setw(20) << p.completionTime 
             << setw(15) << p.waitingTime << setw(20) << p.turnaroundTime << endl;
    }
    cout << "\nAverage Waiting Time: " << avgWT << endl;
    cout << "Average Turnaround Time: " << avgTAT << endl;
}

void srtf(vector<Process> &processes) {
    int n = processes.size();
    vector<int> ganttChart;
    int completed = 0, currentTime = 0;
    double totalWT = 0, totalTAT = 0;

    while (completed < n) {
        int idx = -1;
        int minTime = numeric_limits<int>::max();

        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && 
                processes[i].remainingTime > 0 && 
                processes[i].remainingTime < minTime) {
                minTime = processes[i].remainingTime;
                idx = i;
            }
        }

        if (idx != -1) {
            ganttChart.push_back(processes[idx].id);
            processes[idx].remainingTime--;
            currentTime++;
            if (processes[idx].remainingTime == 0) {
                processes[idx].completionTime = currentTime;
                processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
                processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
                totalWT += processes[idx].waitingTime;
                totalTAT += processes[idx].turnaroundTime;
                completed++;
            }
        } else {
            ganttChart.push_back(0); // 0 represents idle time
            currentTime++;
        }
    }

    double avgWT = totalWT / n;
    double avgTAT = totalTAT / n;
    printGanttChart(ganttChart, currentTime);
    printProcessTable(processes, avgWT, avgTAT);
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        cout << "Enter arrival time and burst time for process P" << i + 1 << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
    }

    srtf(processes);
    return 0;
}

