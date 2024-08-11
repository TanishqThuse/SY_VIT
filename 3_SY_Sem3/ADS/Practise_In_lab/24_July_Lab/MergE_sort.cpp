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

void merge(int arr[], int lb, int mid, int ub){
    int n1 = mid - lb + 1;
    int n2 = ub - mid;

    int left[n1], right[n2];

    for(int i = 0; i < n1; i++)
        left[i] = arr[lb + i];
    for(int j = 0; j < n2; j++)
        right[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = lb;
    while(i < n1 && j < n2){
        if(left[i] <= right[j]){
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while(i < n1){
        arr[k] = left[i];
        i++;
        k++;
    }

    while(j < n2){
        arr[k] = right[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int lb, int ub){
    if(lb < ub){
        int mid = lb + (ub - lb) / 2;
        mergeSort(arr, lb, mid);
        mergeSort(arr, mid + 1, ub);
        merge(arr, lb, mid, ub);
    }
}

int main(){
    int n;
    cout<<"Enter the number of integers"<<endl;
    cin>>n;
    int arr[n];
    cout<<"Enter the elements in array"<<endl;
    takeInput(arr,n);

    cout<<"Before Merge Sort"<<endl;
    print(arr,n);

    //Applying Merge Sort
    mergeSort(arr, 0, n-1);

    cout<<"After Merge Sort"<<endl;
    print(arr,n);
}
