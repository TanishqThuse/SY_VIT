#include<iostream>
using namespace std;

int main(){
	int n;
	cout<<"Enter number of elements : "<<endl;
	cin>>n;
	int arr[n];
	cout<<"Enter sorted elements in array : "<<endl;
	for(int i=0; i<n; i++){
		cin>>arr[i];
	}
	cout<<"Enter key"<<endl;
	int key;
	cin>>key;
	int start = 0;
	int end = n-1;
	int flag = 0;
	while(start<=end){
		int mid = (start+end)/2;
		if(arr[mid]==key){
			cout<<"Element found at index : "<<mid<<endl;
			flag = 1;
			break;
		}
		else if(arr[mid]>key){
			end = mid-1;
		}
		else{
			start = mid+1;
		}
	}
	if(flag==0){
		cout<<"Element not found"<<endl;	
	} return 0;
}
