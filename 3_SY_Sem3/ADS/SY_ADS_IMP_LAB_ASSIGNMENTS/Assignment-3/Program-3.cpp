/**Assignment-3 Q-3
 * WAP to implement multiple stack i.e. More than two stacks using array
and perform following operations on it. A. PUSH, B. POP, C. StackFull
D. StackeEmpty E. Display Stack */

#include<iostream>
#include<vector>
using namespace std;

class Multiple_Stacks{
    vector<int> arr; //array to store elements
    vector<int> top; //Pointers 
    vector<int> next;

    int capacity;
    int stackCount;
    int freeStop;


};