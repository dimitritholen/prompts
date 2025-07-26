#!/bin/bash

# Hash Prompts Installer
# This script installs Hash Prompts as Claude commands with /#: prefix
# Repository: https://github.com/dimitritholen/hash-prompts
#
# Usage:
#   bash install.sh                    # Interactive mode (if possible)
#   bash install.sh --global           # Force global installation
#   bash install.sh --local            # Force local installation
#   curl ... | bash -s -- --global     # Force global when piped

set -e

# Parse command line arguments
FORCE_LOCATION=""
for arg in "$@"; do
    case $arg in
        --global)
            FORCE_LOCATION="global"
            ;;
        --local)
            FORCE_LOCATION="local"
            ;;
        --help|-h)
            echo "Hash Prompts Installer"
            echo ""
            echo "Usage:"
            echo "  bash install.sh              # Interactive installation"
            echo "  bash install.sh --global     # Install globally (~/.claude/commands)"
            echo "  bash install.sh --local      # Install locally (./.claude/commands)"
            echo ""
            echo "When piped from curl:"
            echo "  curl -sSL ... | bash -s -- --global"
            echo "  curl -sSL ... | bash -s -- --local"
            exit 0
            ;;
    esac
done

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# GitHub repository information
REPO_OWNER="dimitritholen"
REPO_NAME="hash-prompts"
BRANCH="feature/kb"
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
    "generate-agent.md"
    "help.md"
)

# Module files to install
MODULES=(
    "modules/common.inc"
    "modules/research.inc"
    "modules/slc-validation.inc"
    "modules/agent-generation.inc"
    "modules/handoffs.inc"
    "modules/README.inc"
    "modules/kb-init.inc"
)

# KB files to install
KB_FILES=(
    "kb/hash-prompts-kb.json"
    "kb/project-kb-template.json"
    "kb/kb-generator.js"
    "kb/schemas/command-schema.json"
    "kb/schemas/rules-schema.json"
    "kb/schemas/project-schema.json"
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
    print_color "$BLUE" "       Hash Prompts (#) Installer"
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
    # Check if location was forced via command line
    if [ -n "$FORCE_LOCATION" ]; then
        case $FORCE_LOCATION in
            global)
                INSTALL_DIR="$HOME/.claude/commands"
                INSTALL_TYPE="global"
                print_color "$BLUE" "Installing globally (--global flag specified)"
                ;;
            local)
                INSTALL_DIR="./.claude/commands"
                INSTALL_TYPE="local"
                print_color "$BLUE" "Installing locally (--local flag specified)"
                ;;
        esac
        print_color "$GREEN" "→ Installing to: $INSTALL_DIR"
        return
    fi
    
    echo
    print_color "$YELLOW" "Where would you like to install the commands?"
    echo "1) Global (available in all projects) - ~/.claude/commands [default]"
    echo "2) Local (current project only) - ./.claude/commands"
    echo
    print_color "$YELLOW" "Tip: Use --global or --local flag to skip this prompt"
    echo
    
    # Try to read from terminal even when piped
    choice=""
    if [ -e /dev/tty ]; then
        # We have a terminal available, try to read from it
        printf "Enter your choice (1 or 2) [1]: "
        read -r choice < /dev/tty 2>/dev/null || {
            # If reading from /dev/tty fails, fall back to non-interactive
            echo
            print_color "$YELLOW" "Cannot read input, defaulting to global installation"
            print_color "$BLUE" "Tip: Use 'curl ... | bash -s -- --global' or '--local' to specify"
            choice="1"
        }
    else
        # No terminal available at all
        print_color "$YELLOW" "Running in non-interactive mode, defaulting to global installation"
        print_color "$BLUE" "Tip: Use 'curl ... | bash -s -- --global' or '--local' to specify"
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
    mkdir -p "$INSTALL_DIR/#/modules"
    mkdir -p "$INSTALL_DIR/#/kb"
    mkdir -p "$INSTALL_DIR/#/kb/schemas"
    print_color "$GREEN" "✓ Directories created"
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
    return 0
}

# Function to download and install a module
install_module() {
    local module_file=$1
    local module_name=$(basename "$module_file")
    local source_url="${BASE_URL}/${module_file}"
    local dest_file="${INSTALL_DIR}/#/${module_file}"
    
    print_color "$BLUE" "Installing module: ${module_name}..."
    
    # Download the module file
    if command -v curl &> /dev/null; then
        if ! curl -sSL "$source_url" -o "$dest_file"; then
            print_color "$RED" "❌ Failed to download ${module_file}"
            return 1
        fi
    elif command -v wget &> /dev/null; then
        if ! wget -q "$source_url" -O "$dest_file"; then
            print_color "$RED" "❌ Failed to download ${module_file}"
            return 1
        fi
    else
        print_color "$RED" "❌ Neither curl nor wget is available"
        exit 1
    fi
    
    print_color "$GREEN" "✓ Installed module: ${module_name}"
    return 0
}

# Function to install all prompts
install_all_prompts() {
    print_color "$BLUE" "\nInstalling Hash Prompts commands..."
    
    local installed=0
    local failed=0
    
    for prompt in "${PROMPTS[@]}"; do
        if install_prompt "$prompt"; then
            installed=$((installed + 1))
        else
            failed=$((failed + 1))
            print_color "$RED" "Failed to install: $prompt"
        fi
    done
    
    echo
    print_color "$GREEN" "✓ Successfully installed: $installed commands"
    if [ $failed -gt 0 ]; then
        print_color "$YELLOW" "⚠ Failed to install: $failed commands"
    fi
}

# Function to install all modules
install_all_modules() {
    print_color "$BLUE" "\nInstalling modules..."
    
    local installed=0
    local failed=0
    
    for module in "${MODULES[@]}"; do
        if install_module "$module"; then
            installed=$((installed + 1))
        else
            failed=$((failed + 1))
            print_color "$RED" "Failed to install: $module"
        fi
    done
    
    echo
    print_color "$GREEN" "✓ Successfully installed: $installed modules"
    if [ $failed -gt 0 ]; then
        print_color "$YELLOW" "⚠ Failed to install: $failed modules"
    fi
}

# Function to install KB file
install_kb_file() {
    local kb_file=$1
    local kb_name=$(basename "$kb_file")
    local source_url="${BASE_URL}/${kb_file}"
    local dest_file="${INSTALL_DIR}/#/${kb_file}"
    
    print_color "$BLUE" "Installing KB file: ${kb_name}..."
    
    # Download the KB file
    if command -v curl &> /dev/null; then
        if ! curl -sSL "$source_url" -o "$dest_file"; then
            print_color "$RED" "❌ Failed to download ${kb_file}"
            return 1
        fi
    elif command -v wget &> /dev/null; then
        if ! wget -q "$source_url" -O "$dest_file"; then
            print_color "$RED" "❌ Failed to download ${kb_file}"
            return 1
        fi
    else
        print_color "$RED" "❌ Neither curl nor wget is available"
        exit 1
    fi
    
    print_color "$GREEN" "✓ Installed KB file: ${kb_name}"
    return 0
}

# Function to install all KB files
install_all_kb_files() {
    print_color "$BLUE" "\nInstalling Knowledge Base files..."
    
    local installed=0
    local failed=0
    
    for kb_file in "${KB_FILES[@]}"; do
        if install_kb_file "$kb_file"; then
            installed=$((installed + 1))
        else
            failed=$((failed + 1))
            print_color "$RED" "Failed to install: $kb_file"
        fi
    done
    
    echo
    print_color "$GREEN" "✓ Successfully installed: $installed KB files"
    if [ $failed -gt 0 ]; then
        print_color "$YELLOW" "⚠ Failed to install: $failed KB files"
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
    echo "  /#:generate-agent Qiskit 2026 quantum"
    echo "  /#:pipeline start"
    echo
    print_color "$GREEN" "✓ Modular Architecture:"
    echo "  Shared patterns are now in modules/ for better maintainability"
    echo
    print_color "$GREEN" "✓ Knowledge Base System:"
    echo "  JSON-based KB for intelligent command execution and data persistence"
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

# Set error handler - disabled during download attempts
# trap handle_error ERR

# Main installation flow
main() {
    print_header
    check_claude_cli
    get_install_location
    create_directories
    install_all_prompts
    install_all_modules
    install_all_kb_files
    show_usage
}

# Run main function
main

# Exit successfully
exit 0