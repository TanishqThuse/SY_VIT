#include <bits/stdc++.h>
using namespace std;

struct Process {
    int pid; // Process ID
    int bt;  // Burst Time
    int art; // Arrival Time
};

// Function to find the waiting time for all processes
void findWaitingTime(Process proc[], int n, int wt[]) {
    int rt[n]; // Remaining time

    // Copy the burst time into rt[]
    for (int i = 0; i < n; i++)
        rt[i] = proc[i].bt;

    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    bool check = false;

    // Process until all processes are completed
    while (complete != n) {
        // Find process with minimum remaining time among the processes that arrive till the current time
        for (int j = 0; j < n; j++) {
            if ((proc[j].art <= t) && (rt[j] < minm) && rt[j] > 0) {
                minm = rt[j];
                shortest = j;
                check = true;
            }
        }

        if (check == false) {
            t++;
            continue;
        }

        // Reduce remaining time by one
        rt[shortest]--;

        // Update minimum
        minm = rt[shortest];
        if (minm == 0)
            minm = INT_MAX;

        // If a process gets completely executed
        if (rt[shortest] == 0) {
            // Increment complete
            complete++;
            check = false;

            // Find finish time of the current process
            finish_time = t + 1;

            // Calculate waiting time
            wt[shortest] = finish_time - proc[shortest].bt - proc[shortest].art;
            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }
        // Increment time
        t++;
    }
}

// Function to calculate turn-around time
void findTurnAroundTime(Process proc[], int n, int wt[], int tat[]) {
    // Calculate turnaround time by adding bt[i] + wt[i]
    for (int i = 0; i < n; i++)
        tat[i] = proc[i].bt + wt[i];
}

// Function to calculate average time and print the Gantt chart
void findavgTime(Process proc[], int n) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    vector<int> ganttChart; // To store the Gantt chart process IDs
    vector<int> timeMarkers; // To store the time markers for Gantt chart

    // Function to find waiting time of all processes
    findWaitingTime(proc, n, wt);

    // Function to find turn-around time for all processes
    findTurnAroundTime(proc, n, wt, tat);

    // Calculate total waiting time and total turnaround time
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
    }

    // Display processes along with all details
    cout << " P\t\tBT\t\tWT\t\tTAT\t\t\n";

    // Calculate and print waiting time and turn-around time for each process
    for (int i = 0; i < n; i++) {
        cout << " " << proc[i].pid << "\t\t"
             << proc[i].bt << "\t\t " << wt[i]
             << "\t\t " << tat[i] << endl;
        ganttChart.push_back(proc[i].pid);
        timeMarkers.push_back(wt[i] + proc[i].bt);
    }

    cout << "\nAverage waiting time = " << (float)total_wt / (float)n;
    cout << "\nAverage turn around time = " << (float)total_tat / (float)n << endl;

    // Printing the Gantt chart
    cout << "\nGantt Chart:\n";
    cout << "|";
    for (int i = 0; i < ganttChart.size(); i++) {
        cout << "  P" << ganttChart[i] << "  |";
    }
    cout << endl;

    cout << "0";
    for (int i = 0; i < timeMarkers.size(); i++) {
        cout << "      " << timeMarkers[i];
    }
    cout << endl;
}

// Driver code
int main() {
    Process proc[] = { { 1, 6, 2 }, { 2, 2, 5 }, { 3, 8, 1 }, { 4, 3, 0}, {5, 4, 4} };
    int n = sizeof(proc) / sizeof(proc[0]);

    findavgTime(proc, n);
    return 0;
}

