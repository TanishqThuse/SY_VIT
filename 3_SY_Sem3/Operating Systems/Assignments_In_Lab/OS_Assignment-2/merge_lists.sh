#!/bin/bash

# Function to merge two sorted arrays
merge_sorted_lists() {
    local arr1=("$@")
    local arr2=("${!#}")
    local merged=()
    local i=0
    local j=0

    while [[ $i -lt ${#arr1[@]} && $j -lt ${#arr2[@]} ]]; do
        if [[ ${arr1[$i]} -le ${arr2[$j]} ]]; then
            merged+=("${arr1[$i]}")
            ((i++))
        else
            merged+=("${arr2[$j]}")
            ((j++))
        fi
    done

    while [[ $i -lt ${#arr1[@]} ]]; do
        merged+=("${arr1[$i]}")
        ((i++))
    done

    while [[ $j -lt ${#arr2[@]} ]]; do
        merged+=("${arr2[$j]}")
        ((j++))
    done

    echo "${merged[@]}"
}

# Read the first sorted list
echo "Enter first sorted list (space-separated):"
read -a list1

# Read the second sorted list
echo "Enter second sorted list (space-separated):"
read -a list2

# Merge the two sorted lists
merged_list=($(merge_sorted_lists "${list1[@]}" "${list2[@]}"))

# Print the merged sorted list
echo "Merged list: ${merged_list[@]}"

