#!/bin/bash
# Hash Prompts Installation Verification Script
# This script checks if Hash Prompts commands are properly installed

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
print_color "$BLUE" "║      Hash Prompts Installation Verifier          ║"
print_color "$BLUE" "╚══════════════════════════════════════════════════╝"
echo

# Check if Claude CLI is installed
print_color "$YELLOW" "1. Checking Claude CLI..."
if command -v claude &> /dev/null; then
    print_color "$GREEN" "✓ Claude CLI is installed"
    claude --version 2>/dev/null || echo "   Version check not available"
else
    print_color "$RED" "✗ Claude CLI is not installed!"
    print_color "$YELLOW" "  Please install Claude Code: https://claude.ai/code"
    exit 1
fi
echo

# Check for command installation directories
print_color "$YELLOW" "2. Checking installation directories..."
GLOBAL_DIR="$HOME/.claude/commands"
LOCAL_DIR="./.claude/commands"
INSTALL_DIR=""

if [ -d "$GLOBAL_DIR/#" ]; then
    print_color "$GREEN" "✓ Global installation found: $GLOBAL_DIR/#"
    INSTALL_DIR="$GLOBAL_DIR"
fi

if [ -d "$LOCAL_DIR/#" ]; then
    print_color "$GREEN" "✓ Local installation found: $LOCAL_DIR/#"
    if [ -z "$INSTALL_DIR" ]; then
        INSTALL_DIR="$LOCAL_DIR"
    else
        print_color "$YELLOW" "  Note: Both global and local installations exist"
    fi
fi

if [ -z "$INSTALL_DIR" ]; then
    print_color "$RED" "✗ No Hash Prompts installation found!"
    print_color "$YELLOW" "  Expected locations:"
    print_color "$YELLOW" "  - Global: $GLOBAL_DIR/#"
    print_color "$YELLOW" "  - Local: $LOCAL_DIR/#"
    echo
    print_color "$YELLOW" "  To install, run:"
    print_color "$BLUE" "  curl -sSL https://raw.githubusercontent.com/dimitritholen/hash-prompts/feature/kb/scripts/install.sh | bash"
    exit 1
fi
echo

# Check for command files
print_color "$YELLOW" "3. Checking installed commands..."
EXPECTED_COMMANDS=(
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

MISSING_COMMANDS=()
for cmd in "${EXPECTED_COMMANDS[@]}"; do
    if [ -f "$INSTALL_DIR/#/$cmd" ]; then
        print_color "$GREEN" "  ✓ /#:${cmd%.md}"
    else
        print_color "$RED" "  ✗ /#:${cmd%.md} (missing)"
        MISSING_COMMANDS+=("$cmd")
    fi
done
echo

# Check for modules
print_color "$YELLOW" "4. Checking required modules..."
EXPECTED_MODULES=(
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

MISSING_MODULES=()
for module in "${EXPECTED_MODULES[@]}"; do
    if [ -f "$INSTALL_DIR/#/$module" ]; then
        print_color "$GREEN" "  ✓ $module"
    else
        print_color "$RED" "  ✗ $module (missing)"
        MISSING_MODULES+=("$module")
    fi
done
echo

# Check KB files
print_color "$YELLOW" "5. Checking KB system files..."
if [ -f "$INSTALL_DIR/#/kb/hash-prompts-kb.json" ]; then
    print_color "$GREEN" "  ✓ Core KB found"
else
    print_color "$RED" "  ✗ Core KB missing"
fi

if [ -d "$HOME/.claude/commands/#/kb" ]; then
    print_color "$GREEN" "  ✓ Central KB directory exists"
else
    print_color "$YELLOW" "  ⚠ Central KB directory not yet created (will be created on first use)"
fi
echo

# Test command format
print_color "$YELLOW" "6. Testing command file format..."
if [ -f "$INSTALL_DIR/#/pipeline.md" ]; then
    # Check if the file has the proper command header
    if head -n 10 "$INSTALL_DIR/#/pipeline.md" | grep -q "/#:pipeline"; then
        print_color "$GREEN" "  ✓ pipeline.md has correct command format"
    else
        print_color "$RED" "  ✗ pipeline.md may not have correct command format"
        print_color "$YELLOW" "    First few lines:"
        head -n 5 "$INSTALL_DIR/#/pipeline.md" | sed 's/^/    /'
    fi
fi
echo

# Summary
print_color "$BLUE" "╔══════════════════════════════════════════════════╗"
print_color "$BLUE" "║                    SUMMARY                       ║"
print_color "$BLUE" "╚══════════════════════════════════════════════════╝"

if [ ${#MISSING_COMMANDS[@]} -eq 0 ] && [ ${#MISSING_MODULES[@]} -eq 0 ]; then
    print_color "$GREEN" "✓ Installation appears to be complete!"
    echo
    print_color "$YELLOW" "To use Hash Prompts commands:"
    print_color "$BLUE" "  /#:help              - Show all available commands"
    print_color "$BLUE" "  /#:pipeline start    - Start a new project"
    print_color "$BLUE" "  /#:project list      - List all projects"
    echo
    print_color "$YELLOW" "Installation directory: $INSTALL_DIR"
else
    print_color "$RED" "✗ Installation is incomplete!"
    
    if [ ${#MISSING_COMMANDS[@]} -gt 0 ]; then
        echo
        print_color "$RED" "Missing commands: ${#MISSING_COMMANDS[@]}"
    fi
    
    if [ ${#MISSING_MODULES[@]} -gt 0 ]; then
        echo
        print_color "$RED" "Missing modules: ${#MISSING_MODULES[@]}"
    fi
    
    echo
    print_color "$YELLOW" "To fix the installation, run:"
    print_color "$BLUE" "  ./fix-installation.sh"
    echo
    print_color "$YELLOW" "Or reinstall completely:"
    print_color "$BLUE" "  curl -sSL https://raw.githubusercontent.com/dimitritholen/hash-prompts/feature/kb/scripts/install.sh | bash"
fi
echo

# Additional diagnostics
if [ -n "$DEBUG" ]; then
    print_color "$YELLOW" "Debug Information:"
    echo "INSTALL_DIR: $INSTALL_DIR"
    echo "PATH: $PATH"
    echo "Current directory: $(pwd)"
    echo
fi