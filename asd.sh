#!/bin/bash
IFS=" " read -ra pids < <(pgrep -f python)
for pid in "${pids[@]}"; do
    printf '%d: ' "$pid"
    tr '\0' ' ' < "/proc/$pid/cmdline"
    echo
done