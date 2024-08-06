#!/bin/bash

if [ -z "$1" ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

declare -A word_count
while read -r line; do
    for word in $line; do
        word_count["$word"]=$((word_count["$word"] + 1))
    done
done < "$1"

max_count=0
most_frequent_word=""
for word in "${!word_count[@]}"; do
    if [ ${word_count["$word"]} -gt $max_count ]; then
        max_count=${word_count["$word"]}
        most_frequent_word="$word"
    fi
done

echo "Most frequent word: $most_frequent_word"
echo "Frequency: $max_count"

