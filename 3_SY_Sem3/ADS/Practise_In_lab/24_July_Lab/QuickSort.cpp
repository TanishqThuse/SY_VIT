#include<iostream>
using namespace std;

void takeInput(int arr[], int n){
    for(int i=0; i<n; i++){
        cin>>arr[i];
    }
}

void print(int a[], int n){
    for(int i=0; i<n; i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
}

int partition(int lb, int ub, int arr[]){
    int pivot = arr[lb];
    int start = lb;
    int end = ub;

    while(start < end){
        while(arr[start] <= pivot) start++;
        while(arr[end] > pivot) end--;
        if(start < end){
            swap(arr[start], arr[end]);
        }
    }
    swap(arr[lb], arr[end]);
    return end;
}

void QuickSort(int LowerBound, int UpperBound, int arr[]){
    if(LowerBound < UpperBound){
        int k = partition(LowerBound, UpperBound, arr);
        QuickSort(LowerBound, k-1, arr);
        QuickSort(k+1, UpperBound, arr);
    }
}

int main(){
    int n;
    cout<<"Enter the number of integers"<<endl;
    cin>>n;
    int arr[n];
    cout<<"Enter the elements in array"<<endl;
    takeInput(arr,n);

    cout<<"Before Quick Sort"<<endl;
    print(arr,n);

    //Applying Quick Sort
    QuickSort(0,n-1,arr);

    cout<<"After Quick Sort"<<endl;
    print(arr,n);
}



// #include<iostream>
// using namespace std;

// void takeInput(int arr[], int n){
//     for(int i=0; i<n; i++){
//         cin>>arr[i];
//     }
// }

// void print(int a[], int n){
//     for(int i=0; i<n; i++){
//         cout<<a[i];
//     }
//     cout<<endl;
// }

// int partition(int lb, int ub, int arr[]){
//     int pivot = lb;
//     //lb is lower bound, ub is upper bound
//     j = ub;
// }

// void QuickSort(int LowerBound, int UpperBound, int arr[]){
//     if(LowerBound < UpperBound){
//         int k = partition(LowerBound, UpperBound, arr);
//         //k returns the index where the pivot is placed
//         QuickSort(LowerBound, k-1, arr);
//         QuickSort(k+1, UpperBound, arr);
//     }
// }

// int main(){
//     int n;
//     cout<<"Enter the number of integers"<<endl;
//     cin>>n;
//     int arr[n];
//     cout<<"Enter the elements in array"<<endl;
//     takeInput(arr,n);

//     cout<<"Before Quick Sort"<<endl;
//     print(arr,n);

//     //Applying Quick Sort
//     QuickSort(0,n-1,arr);

//     cout<<"After Quick Sort"<<endl;
//     print(arr,n);
// }