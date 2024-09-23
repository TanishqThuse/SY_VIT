#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include<limits.h>
using namespace std;
struct Process {
int id;
int arrivalTime;
int burstTime;
int completionTime;
int turnaroundTime;
int waitingTime;
bool isCompleted;
};
bool compareArrival(Process a, Process b) {
return a.arrivalTime < b.arrivalTime;
}
void displayGanttChart(vector<Process> &processes) {
cout << "\nGantt Chart:\n ";for (size_t i = 0; i < processes.size(); i++) {
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
cout << "Enter the number of processes: ";cin >> n;
vector<Process> processes(n);
for (int i = 0; i < n; i++) {
processes[i].id = i + 1;
cout << "Enter arrival time and burst time for process P" << processes[i].id
<< ": ";
cin >> processes[i].arrivalTime >> processes[i].burstTime;
processes[i].isCompleted = false;
}
sort(processes.begin(), processes.end(), compareArrival);
int completed = 0, currentTime = 0;
double totalWaitingTime = 0, totalTurnaroundTime = 0;
vector<Process> ganttChart;
while (completed < n) {
int idx = -1;
int minBurstTime = INT_MAX;
for (int i = 0; i < n; i++) {
if (processes[i].arrivalTime <= currentTime &&
!processes[i].isCompleted) {
if (processes[i].burstTime < minBurstTime) {
minBurstTime = processes[i].burstTime;
idx = i;}
if (processes[i].burstTime == minBurstTime) {
if (processes[i].arrivalTime < processes[idx].arrivalTime) {
idx = i;}}}}
if (idx == -1) {
currentTime++;} else {
processes[idx].completionTime = currentTime +
processes[idx].burstTime;
processes[idx].turnaroundTime = processes[idx].completionTime -
processes[idx].arrivalTime;
processes[idx].waitingTime = processes[idx].turnaroundTime -
processes[idx].burstTime;
totalWaitingTime += processes[idx].waitingTime;
totalTurnaroundTime += processes[idx].turnaroundTime;
processes[idx].isCompleted = true;
currentTime = processes[idx].completionTime;
completed++;
ganttChart.push_back(processes[idx]); }}
cout << "\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
for (auto &p : processes) {
cout << "P" << p.id << "\t" << p.arrivalTime << "\t" << p.burstTime << "\t"
<< p.completionTime << "\t\t" << p.turnaroundTime << "\t\t" <<
p.waitingTime << "\n";
}
displayGanttChart(ganttChart);
cout << fixed << setprecision(2);
cout << "\nAverage Waiting Time: " << totalWaitingTime / n << endl;
cout << "Average Turnaround Time: " << totalTurnaroundTime / n << endl;
return 0;}
