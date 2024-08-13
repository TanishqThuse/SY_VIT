#!/bin/bash

reverse_string() {
    local str=$1
    local len=${#str}
    local rev=""
    for ((i = len - 1; i >= 0; i--)); do
        rev="$rev${str:i:1}"
    done
    echo "Reversed String: $rev"
}

echo "Enter a string:"
read str
reverse_string "$str"
