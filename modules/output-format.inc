#!/bin/bash
# Unified Output Formatting System for Hash-Prompts
# Provides consistent, beautiful output across all commands

# Source KB helpers for quiet mode support
source "$(dirname "${BASH_SOURCE[0]}")/kb-helpers.inc" 2>/dev/null || true

# ============================================================================
# Output Control Variables
# ============================================================================
OUTPUT_QUIET="${KB_QUIET_MODE:-false}"
OUTPUT_VERBOSE="${KB_VERBOSE_MODE:-false}"
OUTPUT_GROUP_MODE="${OUTPUT_GROUP_MODE:-false}"
OUTPUT_INDENT_LEVEL=0

# ============================================================================
# Color and Style Definitions
# ============================================================================
# Colors
readonly COLOR_RESET='\033[0m'
readonly COLOR_BOLD='\033[1m'
readonly COLOR_DIM='\033[2m'

# Foreground colors
readonly COLOR_BLACK='\033[30m'
readonly COLOR_RED='\033[31m'
readonly COLOR_GREEN='\033[32m'
readonly COLOR_YELLOW='\033[33m'
readonly COLOR_BLUE='\033[34m'
readonly COLOR_MAGENTA='\033[35m'
readonly COLOR_CYAN='\033[36m'
readonly COLOR_WHITE='\033[37m'

# Background colors
readonly BG_BLACK='\033[40m'
readonly BG_RED='\033[41m'
readonly BG_GREEN='\033[42m'
readonly BG_YELLOW='\033[43m'
readonly BG_BLUE='\033[44m'

# Icons (can be overridden by environment)
readonly ICON_SUCCESS="${ICON_SUCCESS:-✅}"
readonly ICON_ERROR="${ICON_ERROR:-❌}"
readonly ICON_WARNING="${ICON_WARNING:-⚠️}"
readonly ICON_INFO="${ICON_INFO:-ℹ️}"
readonly ICON_PROGRESS="${ICON_PROGRESS:-🔄}"
readonly ICON_DONE="${ICON_DONE:-✓}"
readonly ICON_PENDING="${ICON_PENDING:-⏳}"
readonly ICON_ROCKET="${ICON_ROCKET:-🚀}"
readonly ICON_FOLDER="${ICON_FOLDER:-📁}"
readonly ICON_FILE="${ICON_FILE:-📄}"
readonly ICON_SAVE="${ICON_SAVE:-💾}"
readonly ICON_SEARCH="${ICON_SEARCH:-🔍}"

# ============================================================================
# Basic Output Functions
# ============================================================================

# Check if output should be shown
should_output() {
    [[ "$OUTPUT_QUIET" != "true" ]]
}

# Print with proper indentation
print_indent() {
    local level="${1:-$OUTPUT_INDENT_LEVEL}"
    local spaces=$((level * 2))
    printf "%${spaces}s" ""
}

# Basic output function with color support
output() {
    local message="$1"
    local color="${2:-}"
    
    if should_output; then
        if [[ -n "$color" ]]; then
            echo -e "${color}${message}${COLOR_RESET}"
        else
            echo "$message"
        fi
    fi
}

# ============================================================================
# Formatted Output Functions
# ============================================================================

# Success message
output_success() {
    local message="$1"
    output "$(print_indent)${ICON_SUCCESS} ${message}" "$COLOR_GREEN"
}

# Error message
output_error() {
    local message="$1"
    # Errors always show, even in quiet mode
    echo -e "${COLOR_RED}$(print_indent)${ICON_ERROR} ${message}${COLOR_RESET}" >&2
}

# Warning message
output_warning() {
    local message="$1"
    output "$(print_indent)${ICON_WARNING} ${message}" "$COLOR_YELLOW"
}

# Info message
output_info() {
    local message="$1"
    output "$(print_indent)${ICON_INFO} ${message}" "$COLOR_CYAN"
}

# Progress message
output_progress() {
    local message="$1"
    output "$(print_indent)${ICON_PROGRESS} ${message}" "$COLOR_BLUE"
}

# Header (large, bold)
output_header() {
    local title="$1"
    local icon="${2:-}"
    
    if should_output; then
        echo
        echo -e "${COLOR_BOLD}${icon} ${title}${COLOR_RESET}"
        echo -e "${COLOR_DIM}$(printf '%.0s=' {1..50})${COLOR_RESET}"
    fi
}

# Section header (medium)
output_section() {
    local title="$1"
    local icon="${2:-}"
    
    if should_output; then
        echo
        echo -e "${COLOR_BOLD}${icon} ${title}${COLOR_RESET}"
    fi
}

# Subsection (small)
output_subsection() {
    local title="$1"
    output "$(print_indent)### ${title}" "$COLOR_DIM"
}

# List item
output_list_item() {
    local item="$1"
    local symbol="${2:--}"
    output "$(print_indent)  ${symbol} ${item}"
}

# Key-value pair
output_keyval() {
    local key="$1"
    local value="$2"
    local key_color="${3:-$COLOR_CYAN}"
    
    if should_output; then
        echo -e "$(print_indent)${key_color}${key}:${COLOR_RESET} ${value}"
    fi
}

# ============================================================================
# Progress and Status Functions
# ============================================================================

# Spinner for long operations
show_spinner() {
    local pid=$1
    local message="${2:-Processing}"
    local spinstr='⠋⠙⠹⠸⠼⠴⠦⠧⠇⠏'
    
    if should_output; then
        while kill -0 $pid 2>/dev/null; do
            local temp=${spinstr#?}
            printf "\r$(print_indent)%s %s" "${spinstr:0:1}" "$message"
            spinstr=$temp${spinstr%"$temp"}
            sleep 0.1
        done
        printf "\r$(print_indent)${ICON_DONE} %s\n" "$message"
    else
        wait $pid
    fi
}

# Progress bar
show_progress_bar() {
    local current="$1"
    local total="$2"
    local width="${3:-30}"
    local title="${4:-Progress}"
    
    if should_output; then
        local percent=$((current * 100 / total))
        local filled=$((width * current / total))
        local empty=$((width - filled))
        
        printf "\r$(print_indent)%s [" "$title"
        printf "%${filled}s" | tr ' ' '█'
        printf "%${empty}s" | tr ' ' '░'
        printf "] %d%%" "$percent"
        
        if [[ $current -eq $total ]]; then
            echo
        fi
    fi
}

# Status indicator with color
show_status() {
    local status="$1"
    local message="$2"
    
    case "$status" in
        "success")
            output_success "$message"
            ;;
        "error")
            output_error "$message"
            ;;
        "warning")
            output_warning "$message"
            ;;
        "info")
            output_info "$message"
            ;;
        "progress")
            output_progress "$message"
            ;;
        *)
            output "$message"
            ;;
    esac
}

# ============================================================================
# Grouped Output Functions
# ============================================================================

# Start output group (collapsible section)
start_output_group() {
    local title="$1"
    OUTPUT_GROUP_MODE=true
    ((OUTPUT_INDENT_LEVEL++))
    
    if should_output; then
        echo
        echo -e "${COLOR_BOLD}▼ ${title}${COLOR_RESET}"
    fi
}

# End output group
end_output_group() {
    ((OUTPUT_INDENT_LEVEL--))
    OUTPUT_GROUP_MODE=false
    
    if should_output; then
        echo
    fi
}

# ============================================================================
# Summary and Report Functions
# ============================================================================

# Show summary box
show_summary() {
    local title="$1"
    shift
    local items=("$@")
    
    if should_output; then
        echo
        echo -e "${COLOR_BOLD}┌─ ${title} ─┐${COLOR_RESET}"
        for item in "${items[@]}"; do
            echo -e "│ ${item}"
        done
        echo -e "${COLOR_BOLD}└──────────────┘${COLOR_RESET}"
        echo
    fi
}

# Show stats table
show_stats_table() {
    local title="$1"
    shift
    
    if should_output; then
        output_section "$title" "📊"
        echo
        while [[ $# -gt 0 ]]; do
            local key="$1"
            local value="$2"
            printf "  %-20s : %s\n" "$key" "$value"
            shift 2
        done
    fi
}

# ============================================================================
# Animation Functions
# ============================================================================

# Typewriter effect
typewriter_effect() {
    local text="$1"
    local delay="${2:-0.05}"
    
    if should_output && [[ "$OUTPUT_QUIET" != "true" ]]; then
        for (( i=0; i<${#text}; i++ )); do
            echo -n "${text:$i:1}"
            sleep "$delay"
        done
        echo
    else
        echo "$text"
    fi
}

# Success animation
animate_success() {
    local message="$1"
    
    if should_output && [[ "$OUTPUT_QUIET" != "true" ]]; then
        echo -ne "\r$(print_indent)⠋ ${message}"
        sleep 0.1
        echo -ne "\r$(print_indent)⠙ ${message}"
        sleep 0.1
        echo -ne "\r$(print_indent)⠹ ${message}"
        sleep 0.1
        echo -ne "\r$(print_indent)⠸ ${message}"
        sleep 0.1
        echo -ne "\r$(print_indent)${ICON_SUCCESS} ${message}\n"
    else
        output_success "$message"
    fi
}

# ============================================================================
# Error Handling Functions
# ============================================================================

# Show friendly error with suggestions
show_error_with_help() {
    local error_msg="$1"
    local suggestion="$2"
    
    output_error "$error_msg"
    if [[ -n "$suggestion" ]]; then
        echo -e "${COLOR_YELLOW}  💡 Suggestion: ${suggestion}${COLOR_RESET}" >&2
    fi
}

# Show validation error
show_validation_error() {
    local field="$1"
    local issue="$2"
    local expected="$3"
    
    output_error "Validation failed for ${field}"
    echo -e "  ${COLOR_DIM}Issue: ${issue}${COLOR_RESET}" >&2
    echo -e "  ${COLOR_DIM}Expected: ${expected}${COLOR_RESET}" >&2
}

# ============================================================================
# Smart Output Functions
# ============================================================================

# Auto-detect and format output based on content
smart_output() {
    local content="$1"
    local context="${2:-general}"
    
    case "$context" in
        "path")
            output_keyval "Path" "$content" "$COLOR_BLUE"
            ;;
        "command")
            output "$(print_indent)$ ${content}" "$COLOR_GREEN"
            ;;
        "code")
            output "$(print_indent)${content}" "$COLOR_DIM"
            ;;
        "url")
            output_keyval "URL" "$content" "$COLOR_MAGENTA"
            ;;
        *)
            output "$content"
            ;;
    esac
}

# Batch output with smart grouping
batch_output() {
    local title="$1"
    shift
    local items=("$@")
    local count=${#items[@]}
    
    if [[ $count -gt 5 ]] && should_output; then
        # Group if more than 5 items
        start_output_group "$title (${count} items)"
        for item in "${items[@]}"; do
            output_list_item "$item"
        done
        end_output_group
    else
        # Show inline if few items
        output_section "$title"
        for item in "${items[@]}"; do
            output_list_item "$item"
        done
    fi
}

# ============================================================================
# Pipeline-Specific Output Functions
# ============================================================================

# Show pipeline stage transition
show_stage_transition() {
    local from="$1"
    local to="$2"
    
    if should_output; then
        echo
        echo -e "${COLOR_BOLD}${from} ${COLOR_GREEN}→${COLOR_RESET} ${COLOR_BOLD}${to}${COLOR_RESET}"
        echo
    fi
}

# Show handoff message
show_handoff() {
    local from="$1"
    local to="$2"
    local message="${3:-Handoff complete}"
    
    output_success "${message}: ${from} → ${to}"
}

# ============================================================================
# Export All Functions
# ============================================================================
export -f should_output print_indent output
export -f output_success output_error output_warning output_info output_progress
export -f output_header output_section output_subsection output_list_item output_keyval
export -f show_spinner show_progress_bar show_status
export -f start_output_group end_output_group
export -f show_summary show_stats_table
export -f typewriter_effect animate_success
export -f show_error_with_help show_validation_error
export -f smart_output batch_output
export -f show_stage_transition show_handoff

# Confirmation message (respects quiet mode)
if should_output; then
    echo "✅ Output formatting system loaded"
fi