#include<stdio.h> 

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
  
    // Function to find waiting time of all processes 
    findWaitingTime(processes, n, bt, wt); 
  
    // Function to find turn-around time for all processes 
    findTurnAroundTime(processes, n, bt, wt, tat); 
  
    // Display processes along with all details 
    printf("Processes   Burst time   Waiting time   Turn around time\n"); 
  
    // Calculate total waiting time and total turn-around time 
    for (int i = 0; i < n; i++) 
    { 
        total_wt += wt[i]; 
        total_tat += tat[i]; 
        printf("   %d ", processes[i]);
        printf("       %d ", bt[i] );
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
        printf("  P%d  |", processes[i]);
    }
    printf("\n");
    
    // Printing the time markers below the Gantt chart
    printf("0"); // Start time for the first process
    for (int i = 0; i < n; i++)
    {
        int finish_time = wt[i] + bt[i];
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

/**Code with no Gantt Chart */

// // C program for implementation of FCFS scheduling 
// #include<stdio.h> 
// // Function to find the waiting time for all processes 
// void findWaitingTime(int processes[], int n, int bt[], int wt[]) 
// { 
//     // waiting time for first process is 0 
//     wt[0] = 0; 
  
//     // calculating waiting time 
//     for (int  i = 1; i < n ; i++ ) 
//         wt[i] =  bt[i-1] + wt[i-1] ; 
// } 
  
// // Function to calculate turn around time 
// void findTurnAroundTime( int processes[], int n, int bt[], int wt[], int tat[]) 
// { 
//     // calculating turnaround time by adding 
//     // bt[i] + wt[i] 
//     for (int  i = 0; i < n ; i++) 
//         tat[i] = bt[i] + wt[i]; 
// } 
  
// //Function to calculate average time 
// void findavgTime( int processes[], int n, int bt[]) 
// { 
//     int wt[n], tat[n], total_wt = 0, total_tat = 0; 
  
//     //Function to find waiting time of all processes 
//     findWaitingTime(processes, n, bt, wt); 
  
//     //Function to find turn around time for all processes 
//     findTurnAroundTime(processes, n, bt, wt, tat); 
  
//     //Display processes along with all details 
//     printf("Processes   Burst time   Waiting time   Turn around time\n"); 
  
//     // Calculate total waiting time and total turn  
//     // around time 
//     for (int  i=0; i<n; i++) 
//     { 
//         total_wt = total_wt + wt[i]; 
//         total_tat = total_tat + tat[i]; 
//         printf("   %d ",(i+1));
//         printf("       %d ", bt[i] );
//         printf("       %d",wt[i] );
//         printf("       %d\n",tat[i] ); 
//     } 
//     float s=(float)total_wt / (float)n;
//     float t=(float)total_tat / (float)n;
//     printf("Average waiting time = %f",s);
//     printf("\n");
//     printf("Average turn around time = %f ",t); 
// } 
  
// // Driver code 
// int main() 
// { 
//     //process id's 
//     int processes[] = { 1, 2, 3}; 
//     int n = sizeof processes / sizeof processes[0]; 
  
//     //Burst time of all processes 
//     int  burst_time[] = {10, 5, 8}; 
  
//     findavgTime(processes, n,  burst_time); 
//     return 0; 
// } 
