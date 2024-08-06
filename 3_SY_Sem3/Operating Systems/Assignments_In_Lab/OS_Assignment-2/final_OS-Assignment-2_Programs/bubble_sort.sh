#!/bin/bash

#bubble sorting function in shell scripting
bubble_sort() {
    local arr=("$@")
    local n=${#arr[@]}
    for ((i = 0; i < n-1; i++)); do
        for ((j = 0; j < n-i-1; j++)); do
            if [ ${arr[j]} -gt ${arr[j+1]} ]; then
                temp=${arr[j]}
                arr[j]=${arr[j+1]}
                arr[j+1]=$temp
            fi
        done
    done
    echo "Sorted Array: ${arr[*]}"
}

#Main functions
echo "Enter the array elements separated by space:"
read -a array
bubble_sort "${array[@]}"
