#include<iostream>
using namespace std;

int main(){
	//Accept input
	cout<<"Enter size of array"<<endl;
	int n ;
	cin>>n;
	int arr[n];
	cout<<"Enter elements in array"<<endl;
	for(int i=0; i<n; i++){
		cin>>arr[i];
	}

	cout<<"Enter element to search"<<endl;
	int key;
	cin>>key;
	for(int i = 0 ; i<n; i++){
		if(arr[i]==key){
			cout<<"Element found at index : "<<i<<endl;
			return 0;
		}
	}
	cout<<"Element not found"<<endl;
	return 0;
}
