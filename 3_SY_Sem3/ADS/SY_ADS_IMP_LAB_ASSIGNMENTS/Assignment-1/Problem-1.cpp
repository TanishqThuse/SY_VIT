/**Assignment-1 : Problem-1
 * Sorting & Searching
WAP to implement Bubble sort and Quick Sort on 1D array of Student
structure (contains student_name, student_roll_no, total_marks), with
key as student_roll_no. And count the number of swap performe */

#include <iostream>
#include <string>
using namespace std;

class Student {
    public:
        string student_name;
        int student_roll_no;
        int total_marks;
    
        //Parametarised constructor
        Student(string name, int rollNo, int marks){
            student_name = name;
            student_roll_no = rollNo;
            total_marks = marks;
        }

        void print(){
            cout << student_name << " " << student_roll_no << " " << total_marks << endl; 
        }
};

int bubbleSort(Student arr[], int n){
    int swapCount = 0;
    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-i-1; j++){
            if(arr[j].student_roll_no > arr[j+1].student_roll_no){
                //Swap arr[j] and arr[j+1]
                Student temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                swapCount++;
            }
        }
    }
    return swapCount;
}

//Implementing Quick Sort
int partition(Student arr[], int low, int high){
    int pivot = arr[high].student_roll_no;
    int i=low-1;
    for(int j=low; j<high; j++){
        if(arr[j].student_roll_no < pivot){
            i++;
            //Now we can swap arr[i] and arr[j]
            Student temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    //Now we can swap arr[i+1] and arr[high]
    Student temp = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = temp;
    return i+1;
}

//Now we can write code for quicksort
int quickSort(Student arr[], int low, int high){
    int swapCount = 0;
    if(low < high){
        
    }
}