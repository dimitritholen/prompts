#!/bin/bash
# Hash Prompts Installation Fix Script
# This script fixes common installation issues

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Function to print colored output
print_color() {
    color=$1
    message=$2
    echo -e "${color}${message}${NC}"
}

print_color "$BLUE" "╔══════════════════════════════════════════════════╗"
print_color "$BLUE" "║        Hash Prompts Installation Fixer           ║"
print_color "$BLUE" "╚══════════════════════════════════════════════════╝"
echo

# Determine installation directory
GLOBAL_DIR="$HOME/.claude/commands"
LOCAL_DIR="./.claude/commands"
INSTALL_DIR=""

print_color "$YELLOW" "Checking for existing installations..."

if [ -d "$GLOBAL_DIR/#" ]; then
    print_color "$GREEN" "Found global installation: $GLOBAL_DIR"
    INSTALL_DIR="$GLOBAL_DIR"
elif [ -d "$LOCAL_DIR/#" ]; then
    print_color "$GREEN" "Found local installation: $LOCAL_DIR"
    INSTALL_DIR="$LOCAL_DIR"
else
    print_color "$YELLOW" "No existing installation found."
    echo
    echo "Where would you like to install/fix Hash Prompts?"
    echo "1) Global (recommended) - $GLOBAL_DIR"
    echo "2) Local (current project) - $LOCAL_DIR"
    echo
    read -p "Enter choice (1 or 2) [1]: " choice
    
    case ${choice:-1} in
        1)
            INSTALL_DIR="$GLOBAL_DIR"
            print_color "$GREEN" "→ Installing globally to: $INSTALL_DIR"
            ;;
        2)
            INSTALL_DIR="$LOCAL_DIR"
            print_color "$GREEN" "→ Installing locally to: $INSTALL_DIR"
            ;;
        *)
            print_color "$RED" "Invalid choice"
            exit 1
            ;;
    esac
fi
echo

# Create directories
print_color "$YELLOW" "Creating directory structure..."
mkdir -p "$INSTALL_DIR/#/modules"
mkdir -p "$INSTALL_DIR/#/kb/schemas"
print_color "$GREEN" "✓ Directories created"
echo

# GitHub info
REPO_OWNER="dimitritholen"
REPO_NAME="hash-prompts"
BRANCH="feature/kb"
BASE_URL="https://raw.githubusercontent.com/${REPO_OWNER}/${REPO_NAME}/${BRANCH}"

# Function to download a file
download_file() {
    local source_path=$1
    local dest_path=$2
    local file_type=$3
    
    local source_url="${BASE_URL}/${source_path}"
    
    if command -v curl &> /dev/null; then
        if curl -sSL "$source_url" -o "$dest_path" 2>/dev/null; then
            print_color "$GREEN" "  ✓ Downloaded $file_type: $(basename "$source_path")"
            return 0
        else
            print_color "$RED" "  ✗ Failed to download: $(basename "$source_path")"
            return 1
        fi
    elif command -v wget &> /dev/null; then
        if wget -q "$source_url" -O "$dest_path" 2>/dev/null; then
            print_color "$GREEN" "  ✓ Downloaded $file_type: $(basename "$source_path")"
            return 0
        else
            print_color "$RED" "  ✗ Failed to download: $(basename "$source_path")"
            return 1
        fi
    else
        print_color "$RED" "Neither curl nor wget is available!"
        exit 1
    fi
}

# Function to fix command file format
fix_command_format() {
    local cmd_file=$1
    local cmd_name=$(basename "$cmd_file" .md)
    
    # Check if file needs the Claude command header
    if ! head -n 5 "$cmd_file" | grep -q "/#:$cmd_name"; then
        print_color "$YELLOW" "  Fixing format for: $cmd_name"
        
        # Create temp file with proper header
        local temp_file=$(mktemp)
        {
            echo "# /#:${cmd_name} Command"
            echo ""
            echo "This command activates the ${cmd_name} mode for your AI assistant."
            echo ""
            echo "Usage: /#:${cmd_name} \$ARGUMENTS"
            echo ""
            echo "---"
            echo ""
            cat "$cmd_file"
        } > "$temp_file"
        
        mv "$temp_file" "$cmd_file"
        print_color "$GREEN" "  ✓ Fixed format for: $cmd_name"
    fi
}

# Commands to check/download
COMMANDS=(
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
    "project.md"
    "help.md"
)

# Modules to check/download
MODULES=(
    "modules/common.inc"
    "modules/research.inc"
    "modules/slc-validation.inc"
    "modules/agent-generation.inc"
    "modules/handoffs.inc"
    "modules/README.inc"
    "modules/kb-init.inc"
    "modules/output-helpers.inc"
    "modules/kb-helpers.inc"
    "modules/kb-multi-project.inc"
    "modules/output-format.inc"
)

# KB files to check/download
KB_FILES=(
    "kb/hash-prompts-kb.json"
    "kb/project-kb-template.json"
    "kb/kb-generator.js"
    "kb/schemas/command-schema.json"
    "kb/schemas/rules-schema.json"
    "kb/schemas/project-schema.json"
)

# Download missing commands
print_color "$YELLOW" "Checking and fixing commands..."
for cmd in "${COMMANDS[@]}"; do
    dest_file="$INSTALL_DIR/#/$cmd"
    if [ ! -f "$dest_file" ]; then
        download_file "$cmd" "$dest_file" "command"
    else
        print_color "$GREEN" "  ✓ Exists: $cmd"
    fi
    
    # Fix format if needed
    if [ -f "$dest_file" ]; then
        fix_command_format "$dest_file"
    fi
done
echo

# Download missing modules
print_color "$YELLOW" "Checking and fixing modules..."
for module in "${MODULES[@]}"; do
    dest_file="$INSTALL_DIR/#/$module"
    if [ ! -f "$dest_file" ]; then
        download_file "$module" "$dest_file" "module"
    else
        print_color "$GREEN" "  ✓ Exists: $module"
    fi
done
echo

# Download missing KB files
print_color "$YELLOW" "Checking and fixing KB files..."
for kb_file in "${KB_FILES[@]}"; do
    dest_file="$INSTALL_DIR/#/$kb_file"
    if [ ! -f "$dest_file" ]; then
        download_file "$kb_file" "$dest_file" "KB file"
    else
        print_color "$GREEN" "  ✓ Exists: $kb_file"
    fi
done
echo

# Create central KB directory
print_color "$YELLOW" "Setting up central KB system..."
CENTRAL_KB_DIR="$HOME/.claude/commands/#/kb"
if [ ! -d "$CENTRAL_KB_DIR" ]; then
    mkdir -p "$CENTRAL_KB_DIR"
    print_color "$GREEN" "✓ Created central KB directory"
else
    print_color "$GREEN" "✓ Central KB directory exists"
fi
echo

# Test the installation
print_color "$YELLOW" "Testing installation..."
if [ -f "$INSTALL_DIR/#/pipeline.md" ] && [ -f "$INSTALL_DIR/#/modules/kb-helpers.inc" ]; then
    print_color "$GREEN" "✓ Core files are in place"
else
    print_color "$RED" "✗ Some core files are still missing"
fi
echo

# Final summary
print_color "$BLUE" "╔══════════════════════════════════════════════════╗"
print_color "$BLUE" "║              INSTALLATION FIXED                  ║"
print_color "$BLUE" "╚══════════════════════════════════════════════════╝"
echo
print_color "$GREEN" "Installation directory: $INSTALL_DIR"
echo
print_color "$YELLOW" "Next steps:"
print_color "$BLUE" "1. Restart your terminal or reload your shell"
print_color "$BLUE" "2. Try: /#:help"
print_color "$BLUE" "3. Start a project: /#:pipeline start"
echo
print_color "$YELLOW" "If commands still don't work:"
print_color "$BLUE" "1. Make sure you're using Claude Code (not regular Claude)"
print_color "$BLUE" "2. Try the command in a new conversation"
print_color "$BLUE" "3. Check that the installation directory is correct"
echo
print_color "$GREEN" "Run ./verify-installation.sh to check the installation"
echo