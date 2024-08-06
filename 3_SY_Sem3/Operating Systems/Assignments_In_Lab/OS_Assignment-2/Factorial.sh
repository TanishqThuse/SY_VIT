#!/bin/bash
echo "Enter a number: "
read num

factorial() {
  if [ "$1" -eq 0 ] || [ "$1" -eq 1 ]; then
    echo 1
  else
    echo "$((1 * $1 * $(factorial "$((1 * $1 - 1))")))";
  fi
}

result=$(factorial "$num")

echo "The factorial of $num is: $result"
