#include <stdio.h> 
#include <stdlib.h> // For qsort

// Comparison function for sorting
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Function to find the waiting time for all processes 
void findWaitingTime(int processes[], int n, int bt[], int wt[]) 
{ 
    // Waiting time for the first process is 0 
    wt[0] = 0; 
  
    // Calculating waiting time for each process
    for (int i = 1; i < n; i++) 
        wt[i] = bt[i - 1] + wt[i - 1]; 
} 
  
// Function to calculate turn-around time 
void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) 
{ 
    // Calculating turn-around time by adding bt[i] + wt[i] 
    for (int i = 0; i < n; i++) 
        tat[i] = bt[i] + wt[i]; 
} 
  
// Function to calculate average time 
void findavgTime(int processes[], int n, int bt[]) 
{ 
    int wt[n], tat[n], total_wt = 0, total_tat = 0; 
  
    // Sorting processes based on burst time
    int indices[n];
    for (int i = 0; i < n; i++) indices[i] = i;
    qsort(indices, n, sizeof(int), compare); // Sort indices based on burst time

    // Create arrays for sorted processes and burst times
    int sorted_processes[n], sorted_burst_time[n];
    for (int i = 0; i < n; i++) {
        sorted_processes[i] = processes[indices[i]];
        sorted_burst_time[i] = bt[indices[i]];
    }

    // Function to find waiting time of all processes 
    findWaitingTime(sorted_processes, n, sorted_burst_time, wt); 
  
    // Function to find turn-around time for all processes 
    findTurnAroundTime(sorted_processes, n, sorted_burst_time, wt, tat); 
  
    // Display processes along with all details 
    printf("Processes   Burst time   Waiting time   Turn around time\n"); 
  
    // Calculate total waiting time and total turn-around time 
    for (int i = 0; i < n; i++) 
    { 
        total_wt += wt[i]; 
        total_tat += tat[i]; 
        printf("   %d ", sorted_processes[i]);
        printf("       %d ", sorted_burst_time[i] );
        printf("       %d", wt[i] );
        printf("       %d\n", tat[i] ); 
    } 
  
    float avg_wt = (float)total_wt / (float)n;
    float avg_tat = (float)total_tat / (float)n;
    printf("Average waiting time = %f\n", avg_wt);
    printf("Average turn around time = %f\n", avg_tat); 

    // Printing the Gantt chart
    printf("\nGantt Chart:\n");
    
    // Printing the process names
    printf("|");
    for (int i = 0; i < n; i++) 
    {
        printf("  P%d  |", sorted_processes[i]);
    }
    printf("\n");
    
    // Printing the time markers below the Gantt chart
    printf("0"); // Start time for the first process
    for (int i = 0; i < n; i++)
    {
        int finish_time = wt[i] + sorted_burst_time[i];
        printf("      %d", finish_time); // Aligning the numbers below the lines
    }
    printf("\n");
} 
  
// Driver code 
int main() 
{ 
    // Process IDs 
    int processes[] = { 1, 2, 3 }; 
    int n = sizeof(processes) / sizeof(processes[0]); 
  
    // Burst time of all processes 
    int burst_time[] = {10, 5, 8}; 
  
    findavgTime(processes, n, burst_time); 
    return 0; 
}
