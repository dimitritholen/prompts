#!/bin/bash
# Hash Prompts Command Test Script
# This script helps test if commands are working properly

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
print_color "$BLUE" "║         Hash Prompts Command Tester              ║"
print_color "$BLUE" "╚══════════════════════════════════════════════════╝"
echo

# Find installation directory
GLOBAL_DIR="$HOME/.claude/commands"
LOCAL_DIR="./.claude/commands"
INSTALL_DIR=""

if [ -d "$GLOBAL_DIR/#" ]; then
    INSTALL_DIR="$GLOBAL_DIR"
elif [ -d "$LOCAL_DIR/#" ]; then
    INSTALL_DIR="$LOCAL_DIR"
else
    print_color "$RED" "❌ No Hash Prompts installation found!"
    print_color "$YELLOW" "Run ./verify-installation.sh first"
    exit 1
fi

print_color "$GREEN" "✓ Using installation at: $INSTALL_DIR"
echo

# Test 1: Check command file structure
print_color "$YELLOW" "Test 1: Command File Structure"
print_color "$BLUE" "Checking if pipeline.md has correct format..."

if [ -f "$INSTALL_DIR/#/pipeline.md" ]; then
    # Check for command header
    if head -n 10 "$INSTALL_DIR/#/pipeline.md" | grep -q "# /#:pipeline Command"; then
        print_color "$GREEN" "✓ pipeline.md has correct command header"
    else
        print_color "$RED" "✗ pipeline.md missing command header"
        print_color "$YELLOW" "First 5 lines:"
        head -n 5 "$INSTALL_DIR/#/pipeline.md" | sed 's/^/  /'
    fi
    
    # Check for usage line
    if head -n 10 "$INSTALL_DIR/#/pipeline.md" | grep -q "Usage: /#:pipeline"; then
        print_color "$GREEN" "✓ pipeline.md has usage documentation"
    else
        print_color "$RED" "✗ pipeline.md missing usage line"
    fi
else
    print_color "$RED" "✗ pipeline.md not found"
fi
echo

# Test 2: Module availability
print_color "$YELLOW" "Test 2: Module Availability"
print_color "$BLUE" "Checking if modules can be sourced..."

# Create a test script that sources modules
TEST_SCRIPT=$(mktemp)
cat > "$TEST_SCRIPT" << 'EOF'
#!/bin/bash
cd "$1"
source modules/kb-helpers.inc 2>/dev/null && echo "KB_HELPERS=OK" || echo "KB_HELPERS=FAIL"
source modules/output-format.inc 2>/dev/null && echo "OUTPUT_FORMAT=OK" || echo "OUTPUT_FORMAT=FAIL"
source modules/kb-init.inc 2>/dev/null && echo "KB_INIT=OK" || echo "KB_INIT=FAIL"
EOF

chmod +x "$TEST_SCRIPT"
RESULT=$("$TEST_SCRIPT" "$INSTALL_DIR/#")
rm -f "$TEST_SCRIPT"

if echo "$RESULT" | grep -q "KB_HELPERS=OK"; then
    print_color "$GREEN" "✓ kb-helpers.inc can be sourced"
else
    print_color "$RED" "✗ kb-helpers.inc cannot be sourced"
fi

if echo "$RESULT" | grep -q "OUTPUT_FORMAT=OK"; then
    print_color "$GREEN" "✓ output-format.inc can be sourced"
else
    print_color "$RED" "✗ output-format.inc cannot be sourced"
fi

if echo "$RESULT" | grep -q "KB_INIT=OK"; then
    print_color "$GREEN" "✓ kb-init.inc can be sourced"
else
    print_color "$RED" "✗ kb-init.inc cannot be sourced"
fi
echo

# Test 3: Implementation section
print_color "$YELLOW" "Test 3: Implementation Section"
print_color "$BLUE" "Checking if pipeline.md has implementation..."

if [ -f "$INSTALL_DIR/#/pipeline.md" ]; then
    if grep -q "## Implementation" "$INSTALL_DIR/#/pipeline.md"; then
        print_color "$GREEN" "✓ pipeline.md has Implementation section"
        
        # Check for command routing
        if grep -q 'case "$COMMAND" in' "$INSTALL_DIR/#/pipeline.md"; then
            print_color "$GREEN" "✓ pipeline.md has command routing"
        else
            print_color "$RED" "✗ pipeline.md missing command routing"
        fi
    else
        print_color "$RED" "✗ pipeline.md missing Implementation section"
    fi
fi
echo

# Test 4: Project command
print_color "$YELLOW" "Test 4: Project Command"
print_color "$BLUE" "Checking project.md..."

if [ -f "$INSTALL_DIR/#/project.md" ]; then
    print_color "$GREEN" "✓ project.md exists"
    
    if grep -q "## Implementation" "$INSTALL_DIR/#/project.md"; then
        print_color "$GREEN" "✓ project.md has implementation"
    else
        print_color "$RED" "✗ project.md missing implementation"
    fi
else
    print_color "$RED" "✗ project.md not found"
fi
echo

# Summary
print_color "$BLUE" "╔══════════════════════════════════════════════════╗"
print_color "$BLUE" "║                  TEST SUMMARY                    ║"
print_color "$BLUE" "╚══════════════════════════════════════════════════╝"
echo

print_color "$YELLOW" "How to use Hash Prompts commands:"
echo
print_color "$BLUE" "1. Make sure you're using Claude Code (not regular Claude)"
print_color "$BLUE" "2. Type commands exactly as shown:"
print_color "$GREEN" "   /#:help"
print_color "$GREEN" "   /#:pipeline start"
print_color "$GREEN" "   /#:project list"
echo
print_color "$YELLOW" "If commands aren't recognized:"
print_color "$BLUE" "1. Try in a new Claude conversation"
print_color "$BLUE" "2. Make sure there's no space between /# and :"
print_color "$BLUE" "3. Commands are case-sensitive"
echo
print_color "$YELLOW" "Installation directory: $INSTALL_DIR"
echo

# Create a sample command for testing
print_color "$YELLOW" "Creating test command file for manual verification..."
TEST_CMD_FILE="$INSTALL_DIR/#/test-hello.md"
cat > "$TEST_CMD_FILE" << 'EOF'
# /#:test-hello Command

This is a simple test command to verify Claude commands are working.

Usage: /#:test-hello

---

When the user types `/#:test-hello`, respond with:

```
🎉 Hello from Hash Prompts!

If you see this message, Claude commands are working correctly.

Try these commands next:
- /#:help - See all available commands
- /#:pipeline start - Start a new project
- /#:project list - List your projects
```
EOF

print_color "$GREEN" "✓ Created test command: /#:test-hello"
print_color "$YELLOW" "Try typing: /#:test-hello"
echo