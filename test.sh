#!/bin/bash

# Compile the program
cc main.c -o echo_prog

# Function to run a single test
# $1 - Test name
# $2 - Arguments for our echo
# $3 - Expected output
run_test() {
    local name="$1"
    local args="$2"
    local expected="$3"
    
    # Save the output of our program to actual.txt
    eval "./echo_prog $args > actual.txt"
    
    # Save the expected output to expected.txt
    # %b allows printf to interpret \n, \t, etc.
    printf "%b" "$expected" > expected.txt
    
    # Compare files byte by byte
    if cmp -s actual.txt expected.txt; then
        echo "✅ PASS: $name (./echo_prog $args)"
    else
        echo "❌ FAIL: $name (./echo_prog $args)"
        echo "   Expected:"
        cat -e expected.txt | sed 's/^/     /'
        echo "   Got:"
        cat -e actual.txt | sed 's/^/     /'
    fi
}

echo "=== Running echo tests ==="

# Basic checks
run_test "No flags" "Hello" "Hello\n"
run_test "Multiple words" "Hello world" "Hello world\n"

# Test -n flag (no trailing newline)
run_test "Flag -n" "-n Hello" "Hello"

# Test -e flag (interpret escape sequences)
run_test "Flag -e" "-e 'Hello\nWorld'" "Hello\nWorld\n"

# Test -E flag (disable interpretation of escape sequences)
run_test "Flag -E" "-E 'Hello\nWorld'" "Hello\\\\nWorld\n"

# Combined flags -ne / -en
run_test "Flags -ne" "-ne 'Hello\nWorld'" "Hello\nWorld"
run_test "Flags -en" "-en 'Hello\nWorld'" "Hello\nWorld"

# Separate flags
run_test "Flags -n -e" "-n -e 'Hello\nWorld'" "Hello\nWorld"

# Clean up temporary files
rm -f actual.txt expected.txt echo_prog

echo "=========================="
