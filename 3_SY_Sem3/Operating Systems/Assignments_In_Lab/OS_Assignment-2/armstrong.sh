#!/bin/bash

is_armstrong() {
    local num=$1
    local sum=0
    local temp=$num
    local n=${#num}

    while [ $temp -gt 0 ]; do
        digit=$((temp % 10))
        sum=$((sum + digit ** n))
        temp=$((temp / 10))
    done

    if [ $sum -eq $num ]; then
        echo "The number $num is an Armstrong number."
    else
        echo "The number $num is not an Armstrong number."
    fi
}

echo "Enter a number:"
read num
is_armstrong "$num"
