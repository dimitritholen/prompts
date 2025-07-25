#!/bin/bash

# Claude Prompts Collection Installer
# This script installs AI prompts as Claude commands
# Repository: https://github.com/dimitritholen/prompts

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# GitHub repository information
REPO_OWNER="dimitritholen"
REPO_NAME="prompts"
BRANCH="features/add_pipeline"
BASE_URL="https://raw.githubusercontent.com/${REPO_OWNER}/${REPO_NAME}/${BRANCH}"

# Prompt files to install
PROMPTS=(
    "brainstorm.md"
    "prd.md"
    "architect.md"
    "tasks.md"
    "plan.md"
    "code.md"
    "feature.md"
    "test.md"
    "deploy.md"
    "pipeline.md"
)

# Function to print colored output
print_color() {
    color=$1
    message=$2
    echo -e "${color}${message}${NC}"
}

# Function to print header
print_header() {
    echo
    print_color "$BLUE" "════════════════════════════════════════════════════"
    print_color "$BLUE" "    Claude Prompts Collection Installer"
    print_color "$BLUE" "════════════════════════════════════════════════════"
    echo
}

# Function to check if Claude CLI is installed
check_claude_cli() {
    if ! command -v claude &> /dev/null; then
        print_color "$RED" "❌ Claude CLI is not installed!"
        print_color "$YELLOW" "Please install Claude Code first: https://claude.ai/code"
        exit 1
    fi
    print_color "$GREEN" "✓ Claude CLI detected"
}

# Function to prompt for installation type
get_install_location() {
    echo
    print_color "$YELLOW" "Where would you like to install the commands?"
    echo "1) Global (available in all projects) - ~/.claude/commands [default]"
    echo "2) Local (current project only) - ./.claude/commands"
    echo
    
    # Check if running interactively
    if [ -t 0 ]; then
        read -p "Enter your choice (1 or 2) [1]: " choice
    else
        # Non-interactive mode - default to global
        print_color "$BLUE" "Running in non-interactive mode, defaulting to global installation"
        choice="1"
    fi
    
    # Default to option 1 if empty
    if [ -z "$choice" ]; then
        choice="1"
    fi
    
    case $choice in
        1)
            INSTALL_DIR="$HOME/.claude/commands"
            INSTALL_TYPE="global"
            ;;
        2)
            INSTALL_DIR="./.claude/commands"
            INSTALL_TYPE="local"
            ;;
        *)
            print_color "$RED" "Invalid choice. Exiting."
            exit 1
            ;;
    esac
    
    print_color "$GREEN" "→ Installing to: $INSTALL_DIR"
}

# Function to create directory structure
create_directories() {
    print_color "$BLUE" "Creating directory structure..."
    mkdir -p "$INSTALL_DIR/#"
    print_color "$GREEN" "✓ Directory created"
}

# Function to download and install a prompt
install_prompt() {
    local prompt_file=$1
    local command_name=${prompt_file%.md}
    local source_url="${BASE_URL}/${prompt_file}"
    local dest_file="${INSTALL_DIR}/#/${command_name}.md"
    
    print_color "$BLUE" "Installing /#:${command_name}..."
    
    # Create a temporary file
    local temp_file=$(mktemp)
    
    # Download the prompt file
    if command -v curl &> /dev/null; then
        if ! curl -sSL "$source_url" -o "$temp_file"; then
            print_color "$RED" "❌ Failed to download ${prompt_file} from $source_url"
            rm -f "$temp_file"
            return 1
        fi
    elif command -v wget &> /dev/null; then
        if ! wget -q "$source_url" -O "$temp_file"; then
            print_color "$RED" "❌ Failed to download ${prompt_file} from $source_url"
            rm -f "$temp_file"
            return 1
        fi
    else
        print_color "$RED" "❌ Neither curl nor wget is available"
        exit 1
    fi
    
    # Convert to Claude command format
    {
        echo "# /#:${command_name} Command"
        echo ""
        echo "This command activates the ${command_name} mode for your AI assistant."
        echo ""
        echo "Usage: /#:${command_name} \$ARGUMENTS"
        echo ""
        echo "---"
        echo ""
        cat "$temp_file"
    } > "$dest_file"
    
    # Clean up temp file
    rm -f "$temp_file"
    
    print_color "$GREEN" "✓ Installed /#:${command_name}"
}

# Function to install all prompts
install_all_prompts() {
    print_color "$BLUE" "\nInstalling prompts as Claude commands..."
    
    local installed=0
    local failed=0
    
    for prompt in "${PROMPTS[@]}"; do
        if install_prompt "$prompt"; then
            ((installed++))
        else
            ((failed++))
        fi
    done
    
    echo
    print_color "$GREEN" "✓ Successfully installed: $installed commands"
    if [ $failed -gt 0 ]; then
        print_color "$YELLOW" "⚠ Failed to install: $failed commands"
    fi
}

# Function to show usage instructions
show_usage() {
    echo
    print_color "$BLUE" "════════════════════════════════════════════════════"
    print_color "$GREEN" "✨ Installation Complete!"
    print_color "$BLUE" "════════════════════════════════════════════════════"
    echo
    print_color "$YELLOW" "Available Commands:"
    for prompt in "${PROMPTS[@]}"; do
        command_name=${prompt%.md}
        echo "  /#:${command_name}"
    done
    echo
    print_color "$YELLOW" "Usage Examples:"
    echo "  /#:brainstorm I want to build a task management app"
    echo "  /#:architect Design a microservices architecture"
    echo "  /#:pipeline start"
    echo
    if [ "$INSTALL_TYPE" = "local" ]; then
        print_color "$BLUE" "Note: These commands are only available in this project."
    else
        print_color "$BLUE" "Note: These commands are available globally in all projects."
    fi
    echo
}

# Function to handle errors
handle_error() {
    print_color "$RED" "❌ An error occurred during installation"
    exit 1
}

# Set error handler
trap handle_error ERR

# Main installation flow
main() {
    print_header
    check_claude_cli
    get_install_location
    create_directories
    install_all_prompts
    show_usage
}

# Run main function
main

# Exit successfully
exit 0