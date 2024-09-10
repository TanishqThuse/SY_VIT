#include <stdio.h> 

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
  
    // Hardcoding burst time of all processes for output directly
    int burst_time[] = {10, 5, 8}; 
  
    // Calling the function to calculate and display average time and Gantt chart
    findavgTime(processes, n, burst_time); 
    return 0; 
}
	

// #include <iostream>
// using namespace std;

// int main() {

// 	// Matrix for storing Process Id, Burst
// 	// Time, Average Waiting Time & Average
// 	// Turn Around Time.
// 	int A[100][4];
// 	int i, j, n, total = 0, index, temp;
// 	float avg_wt, avg_tat;

// 	cout << "Enter number of process: ";
// 	cin >> n;

// 	cout << "Enter Burst Time:" << endl;

// 	// User Input Burst Time and alloting Process Id.
// 	for (i = 0; i < n; i++) {
// 		cout << "P" << i + 1 << ": ";
// 		cin >> A[i][1];
// 		A[i][0] = i + 1;
// 	}

// 	// Sorting process according to their Burst Time.
// 	for (i = 0; i < n; i++) {
// 		index = i;
// 		for (j = i + 1; j < n; j++)
// 			if (A[j][1] < A[index][1])
// 				index = j;
// 		temp = A[i][1];
// 		A[i][1] = A[index][1];
// 		A[index][1] = temp;

// 		temp = A[i][0];
// 		A[i][0] = A[index][0];
// 		A[index][0] = temp;
// 	}

// 	A[0][2] = 0;
// 	// Calculation of Waiting Times
// 	for (i = 1; i < n; i++) {
// 		A[i][2] = 0;
// 		for (j = 0; j < i; j++)
// 			A[i][2] += A[j][1];
// 		total += A[i][2];
// 	}

// 	avg_wt = (float)total / n;
// 	total = 0;
// 	cout << "P	 BT	 WT	 TAT" << endl;

// 	// Calculation of Turn Around Time and printing the
// 	// data.
// 	for (i = 0; i < n; i++) {
// 		A[i][3] = A[i][1] + A[i][2];
// 		total += A[i][3];
// 		cout << "P" << A[i][0] << "	 " << A[i][1] << "	 " << A[i][2] << "	 " << A[i][3] << endl;
// 	}

// 	avg_tat = (float)total / n;
// 	cout << "Average Waiting Time= " << avg_wt << endl;
// 	cout << "Average Turnaround Time= " << avg_tat << endl;
// }

