#include<stdio.h>

void print(int a[], int n){
    for(int i=0; i<n; i++){
        printf("%d ",a[i]);
    }
    printf("\n");
}

void InsertionSort(int a[], int n){
    for(int i=1; i<n; i++){
        int key = a[i];
        for(int j=i-1; j>=0; j--){
            if(key < a[j]){
                // int temp = key;
                // key = a[j];
                // a[j] = temp;
                 int temp = a[j+1];
                a[j+1] = a[j];
                a[j] = temp;
            }
        }
    }
    printf("Array after Insertion Sort : ");
    print(a,n);
}


int main(){
    int n;
    printf("Enter the size of arrays\n");
    scanf("%d",&n);
    int a[n];

    printf("Enter the elements in array\n");
    for(int i=0; i<n; i++){
        scanf("%d",&a[i]);
    }

    printf("Original array is : ");
    print(a,n);

    InsertionSort(a,n);
}