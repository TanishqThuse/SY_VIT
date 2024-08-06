#!/bin/bash

# Function for arithmetic operations
arithmetic_operations() {
    echo "Enter first number:"
    read num1
    echo "Enter second number:"
    read num2
    echo "Choose an operation (+, -, *, /):"
    read op

    case $op in
        +) result=$((num1 + num2)) ;;
        -) result=$((num1 - num2)) ;;
        \*) result=$((num1 * num2)) ;;
        /) result=$((num1 / num2)) ;;
        *) echo "Invalid operation" ;;
    esac

    echo "Result: $result"
}

# Function for file operations
file_operations() {
    echo "Choose a file operation:"
    echo "1. Create a file"
    echo "2. Delete a file"
    echo "3. List files in directory"
    read file_op

    case $file_op in
        1) echo "Enter filename to create:"
           read filename
           touch "$filename"
           echo "File '$filename' created." ;;
        2) echo "Enter filename to delete:"
           read filename
           rm "$filename"
           echo "File '$filename' deleted." ;;
        3) echo "Enter directory to list files:"
           read dir
           ls "$dir" ;;
        *) echo "Invalid file operation" ;;
    esac
}

# Function for text processing
text_processing() {
    echo "Choose a text processing operation:"
    echo "1. Count lines in a file"
    echo "2. Count words in a file"
    echo "3. Search for a word in a file"
    read text_op

    case $text_op in
        1) echo "Enter filename to count lines:"
           read filename
           line_count=$(wc -l < "$filename")
           echo "Number of lines in $filename: $line_count" ;;
        2) echo "Enter filename to count words:"
           read filename
           word_count=$(wc -w < "$filename")
           echo "Number of words in $filename: $word_count" ;;
        3) echo "Enter filename to search in:"
           read filename
           echo "Enter word to search for:"
           read word
           grep -o -i "$word" "$filename" | wc -l
           echo "Number of occurrences of '$word' in $filename: $(grep -o -i "$word" "$filename" | wc -l)" ;;
        *) echo "Invalid text processing operation" ;;
    esac
}

# Main menu
while true; do
    echo "Main Menu"
    echo "1. Arithmetic Operations"
    echo "2. File Operations"
    echo "3. Text Processing"
    echo "4. Exit"
    echo "Enter your choice:"
    read choice

    case $choice in
        1) arithmetic_operations ;;
        2) file_operations ;;
        3) text_processing ;;
        4) echo "Exiting..."; exit 0 ;;
        *) echo "Invalid choice. Please enter a number between 1 and 4." ;;
    esac
done
