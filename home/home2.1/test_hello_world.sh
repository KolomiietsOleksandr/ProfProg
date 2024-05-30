#!/bin/bash

check_output() {
    local expected_output="$1"
    shift
    local output=$(../../class/class2.1/HelloWorld "$@")
    if [[ "$output" == "$expected_output" ]]; then
        echo "Test passed."
    else
        echo "Test failed. Expected: '$expected_output', but got: '$output'"
        exit 1
    fi
}

touch user_data.txt

# Test Case 1: First Run with a New Name
> user_data.txt
check_output "Welcome, Alice!" "Alice"
check_output "Hello again(x=2), Alice!" "Alice"
check_output "Hello again(x=3), Alice!" "Alice"

# Test Case 2: Handling of Multiple Names
> user_data.txt
check_output "Welcome, Bob!" "Bob"
check_output "Welcome, Alice!" "Alice"
check_output "Hello again(x=2), Alice!" "Alice"
check_output "Hello again(x=2), Bob!" "Bob"

# Test Case 3: Reset Statistics for a Given Name
> user_data.txt
check_output "Welcome, Charlie!" "Charlie"
check_output "Hello again(x=2), Charlie!" "Charlie"
check_output "Statistics for Charlie have been reset." "Charlie" "delete"
check_output "Welcome, Charlie!" "Charlie"

# Test Case 4: Clear All History with Secret Word
> user_data.txt
check_output "Welcome, David!" "David"
check_output "Welcome, Eve!" "Eve"
check_output "Welcome, bread!" "bread"
check_output "Welcome, David!" "David"
check_output "Welcome, Eve!" "Eve"

# Test Case 5: Invalid Arguments Handling
> user_data.txt
check_output "Usage: <program> <name> [delete]"
check_output "Usage: <program> <name> [delete]" "Alice" "extra_argument"
check_output "Usage: <program> <name> [delete]" "Frank" "invalid"

echo "All tests passed."
