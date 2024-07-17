#include <iostream>
#include <stdio.h>
using namespace std;
#include <cstring>

void print(int a[], int n){
    // int n = sizeof(a)/sizeof(a[0]);
    for(int i=0; i<n; i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
}
    
void BubbleSort(int a[], int n){
    int comparisons = 0;
    for(int i=0 ; i<n; i++){
        int flag = 0;
        //IMP : j < n-1-i (instead of j<n-1) is a very important condition otherwise the array is comparing the sorted part of array and it increases the number of comparisons from 10 -> 20 in worst case
        for(int j=0; j<n-1-i; j++){
            if(a[j] > a[j+1]){
                int temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp; 
                flag = 1; //make sure it works in O(n) for sorted array
            }
            comparisons++;
        }
        if(flag == 0){
            //it means array is already sorted
            break;
        }
    }
    cout<<"Sorted array is : ";
    print(a,n);
    cout<<"Total comparisons : "<<comparisons<<endl;
}

int main(){
    int n;
    cout<<"Enter size of array"<<endl;
    cin>>n;
    int a[n];
    cout<<"Enter no. of cases to execute"<<endl;
    int cases;
    cin>>cases;
    int count = 1;
    while(cases>0){
        cout<<"Case "<<count++<<endl;
        cout<<"Enter elements of array"<<endl;
        for(int i=0; i<n; i++){
            cin>>a[i];
        }
        cout<<"Original array is : ";
        print(a,n);
        BubbleSort(a,n);
        cases--;
    }
}