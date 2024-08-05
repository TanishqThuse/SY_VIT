/**Assignment-2 , Q-1
 *WAP to search a particular students record in 'n' number of students pool by using Binary search with and without recursive function.
Assume suitable data for student record
 */
#include<iostream>
#include<string>
#include<vector>

using namespace std;

//an example of encapsulation, wrapping up of data(name, RollNo) and methods into a single unit
class Student{
    public:
    string name;
    int RollNo;

    //Default constructor : 
    Student(){
        name = " ";
        // RollNo = 0; //not assignmend
    }

    //Paramterized constructor :
    Student(string name, int id){
        this->name = name; //similar to this in java
        this->RollNo = id;
    }
};

int BinarySearchIterative(vector<Student>& students, int target){
    int left = 0;
    int right = students.size()-1;

    while(left<=right){
        int mid = left + (right-left)/2; //to avoid overflow

        if(students[mid].RollNo == target){
            return mid;
        }
        else if(students[mid].RollNo < target){
            left = mid+1;
        }
        else{
            right = mid-1;
        }
    }
    return -1; // RollNo not found
}

int BinarySearchRecursive(vector<Student>& students, int target, int left, int right){
    if(left<=right){ //here if is used in BinarySearchRecursive instead of while
        int mid = left + (right-left)/2; //to avoid overflow
    
        if(students[mid].RollNo == target){
            return mid;
        }
        else if(students[mid].RollNo < target){
            return BinarySearchRecursive(students, target, mid+1, right);
        }
        else{
            return BinarySearchRecursive(students, target, left, mid-1);
        }
    }
    return -1;
}

int main(){

    //We can also do this in a method if we want to
    vector<Student> students;
    students.push_back(Student("Aditya",1));
    students.push_back(Student("Rahul",2));
    students.push_back(Student("Rohit",3)); 
    students.push_back(Student("Raj",4));
    students.push_back(Student("Ravi",5));
    students.push_back(Student("Tanishq",6));

    cout<<"Enter a target RollNo to search"<<endl;
    int target;
    cin>>target;

    int index = BinarySearchIterative(students, target);
    int index2 = BinarySearchRecursive(students, target, 0, students.size()-1);

    if(index != -1){
        cout<<"RollNo found at index : "<<index<<" through Iterative search"<<endl;
        cout<<"Name : "<<students[index].name<<endl;
    }
    else{
        cout<<"RollNo not found"<<endl;
    }

    if(index2 != -1){
        cout<<"RollNo found at index : "<<index2<<" through Recursive search"<<endl;
        cout<<"Name : "<<students[index].name<<endl;
    }
    else{
        cout<<"RollNo not found"<<endl;
    }

    return 0;
}