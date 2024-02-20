#!/bin/sh

# Output file
OUTPUT_FILE="results.txt"

# Ensure the output file is empty
> "$OUTPUT_FILE"

# Loop from 1 to 48 threads using a POSIX-compliant way
THREADS=1
while [ $THREADS -le 48 ]; do
    # Run veccadd and capture the performance
    PERFORMANCE=$(./veccadd $THREADS 100000)
    # Append the performance result to the results file
    echo "$PERFORMANCE" >> "$OUTPUT_FILE"
    THREADS=$((THREADS + 1))
done


