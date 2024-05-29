#!/bin/bash

run_test() {
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

> user_data.txt

# Test Case 1: First Run with a New Name
run_test "Welcome, Alice!" "Alice"
run_test "Hello again(x=2), Alice!" "Alice"
run_test "Hello again(x=3), Alice!" "Alice"

> user_data.txt

# Test Case 2: Handling of Multiple Names
run_test "Welcome, Bob!" "Bob"
run_test "Welcome, Alice!" "Alice"
run_test "Hello again(x=2), Alice!" "Alice"
run_test "Hello again(x=2), Bob!" "Bob"

> user_data.txt

# Test Case 3: Reset Statistics for a Given Name
run_test "Welcome, Charlie!" "Charlie"
run_test "Hello again(x=2), Charlie!" "Charlie"
run_test "Statistics for Charlie have been reset." "Charlie" "delete"
run_test "Welcome, Charlie!" "Charlie"
> user_data.txt

# Test Case 4: Clear All History with Secret Word
run_test "Welcome, David!" "David"
run_test "Welcome, Eve!" "Eve"
run_test "Welcome, bread!" "bread"
run_test "Welcome, David!" "David"
run_test "Welcome, Eve!" "Eve"

# Test Case 5: Invalid Arguments Handling
run_test "Usage: <program> <name> [delete]"
run_test "Usage: <program> <name> [delete]" "Alice" "extra_argument"
run_test "Usage: <program> <name> [delete]" "Frank" "invalid"

echo "All tests passed."
