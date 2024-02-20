#!/bin/sh

THREADS=1
while [ $THREADS -le 48 ]; do
    # Run veccadd and capture the performance
    PERFORMANCE=$(./veccadd $THREADS 10000000)
    # Append the performance result to the results file
    echo "$PERFORMANCE" 
    THREADS=$((THREADS + 1))
done