#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Process {
int id; // Process ID
int arrivalTime; // Arrival Time
int burstTime; // Burst Time
int completionTime; // Completion Time
int turnaroundTime; // Turnaround Time
int waitingTime; // Waiting Time

};

bool compareArrival(Process a, Process b) {
return a.arrivalTime < b.arrivalTime;
}

void displayGanttChart(vector<Process> &processes) {
cout << "\nGantt Chart:\n ";

for (size_t i = 0; i < processes.size(); i++) {
cout << "+-------";
}
cout << "+\n";

cout << "|";
for (auto &p : processes) {
cout << " P" << p.id << setw(5) << "|";
}
cout << "\n ";

for (size_t i = 0; i < processes.size(); i++) {
cout << "+-------";
}
cout << "+\n";

cout << "0";
for (auto &p : processes) {
cout << setw(8) << p.completionTime;
}
cout << "\n";
}

int main() {
int n;
cout << "Enter the number of processes: ";
cin >> n;
float avgWT=0;
float avgTAT=0;
vector<Process> processes(n);

// Input process details
for (int i = 0; i < n; i++) {
processes[i].id = i + 1;
cout << "Enter arrival time and burst time for process P" << processes[i].id
<< ": ";
cin >> processes[i].arrivalTime >> processes[i].burstTime;
}

// Sort processes based on arrival time
sort(processes.begin(), processes.end(), compareArrival);

// Calculate Completion, Turnaround, and Waiting times
int currentTime = 0;
for (int i = 0; i < n; i++) {
if (currentTime < processes[i].arrivalTime) {
currentTime = processes[i].arrivalTime; // Idle until the process arrives
}
processes[i].completionTime = currentTime + processes[i].burstTime;

currentTime = processes[i].completionTime;
processes[i].turnaroundTime = processes[i].completionTime -
processes[i].arrivalTime;
processes[i].waitingTime = processes[i].turnaroundTime -
processes[i].burstTime;
}
for(auto &p:processes)
{
avgTAT+=p.turnaroundTime;
avgWT+=p.waitingTime;
}
avgTAT/=n;
avgWT/=n;
// Display Process Information
cout << "\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
for (auto &p : processes) {
cout << "P" << p.id << "\t" << p.arrivalTime << "\t" << p.burstTime << "\t"
<< p.completionTime << "\t\t" << p.turnaroundTime << "\t\t" <<
p.waitingTime << "\n";
}

cout<<"The average Waiting time : "<<avgWT<<"\n";
cout<<"The average turn around time : "<<avgTAT<<"\n";

displayGanttChart(processes);

return 0;}