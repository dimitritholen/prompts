#!/bin/bash
# Output Helper Functions for Pipeline Commands

# Progress spinner for long operations
spinner() {
    local pid=$1
    local delay=0.1
    local spinstr='|/-\'
    while [ "$(ps a | awk '{print $1}' | grep $pid)" ]; do
        local temp=${spinstr#?}
        if [[ "$QUIET_MODE" == "true" ]]; then
            printf " [%c]  " "$spinstr" >&2
        fi
        local spinstr=$temp${spinstr%"$temp"}
        sleep $delay
        printf "\b\b\b\b\b\b" >&2
    done
    printf "    \b\b\b\b" >&2
}

# Run command with progress indicator
run_with_progress() {
    local desc="$1"
    shift
    
    if [[ "$QUIET_MODE" == "true" ]]; then
        show_progress "$desc"
        "$@" >/dev/null 2>&1 &
        spinner $!
        wait $!
        local result=$?
        if [ $result -eq 0 ]; then
            complete_progress
        else
            echo " ❌"
        fi
        return $result
    else
        "$@"
    fi
}

# Export functions
export -f spinner
export -f run_with_progress