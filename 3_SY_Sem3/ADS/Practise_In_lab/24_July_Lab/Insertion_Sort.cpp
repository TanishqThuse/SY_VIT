#include<iostream>
using namespace std;

// insertionSort()

void printArray(int arr[], int n){
    for(int i=0; i<n; i++){
        cout<<arr[i];
    }
    cout<<endl;
}

void InsertionSort(int arr[], int n){
    //Code for insertion sort
    for(int i=1; i<n; i++){
        int key = arr[i];
        for(int j=i-1; j>=0; j--){
            if(arr[j] > key){
                int temp = arr[j+1];
                arr[j+1] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main(){
    int n;
    cout<<"Enter the number of elements in array"<<endl;
    cin>>n;
    int arr[n];

    cout<<"Enter the elements in array"<<endl;
    for(int i=0; i<n; i++){
        cin>>arr[i];
    }

    cout<<"Original Array : ";
    printArray(arr,n);
    InsertionSort(arr, n);

    cout<<"Final Array : ";
    printArray(arr,n);
    return 0;
}