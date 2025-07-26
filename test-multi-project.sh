#!/bin/bash
# Test script for multi-project KB functionality

echo "🧪 Testing Multi-Project KB System"
echo "=================================="
echo

# Create temp directory for testing
TEST_DIR=$(mktemp -d)
echo "📁 Test directory: $TEST_DIR"
echo

# Source the modules
source modules/kb-multi-project.inc
source modules/output-format.inc

# Test 1: Create two test projects
output_header "Test 1: Create Multiple Projects" "$ICON_FOLDER"

mkdir -p "$TEST_DIR/projectA"
mkdir -p "$TEST_DIR/projectB"

# Initialize project A
cd "$TEST_DIR/projectA"
output_info "Initializing Project A..."
kb_init_project_enhanced
kb_get_current_project
echo

# Initialize project B  
cd "$TEST_DIR/projectB"
output_info "Initializing Project B..."
kb_init_project_enhanced
kb_get_current_project
echo

# Test 2: Project switching
output_header "Test 2: Project Detection" "$ICON_SEARCH"

cd "$TEST_DIR/projectA"
output_info "In projectA directory:"
project_name=$(jq -r '.project_metadata.name' "$(kb_load)")
echo "  Detected project: $project_name"

cd "$TEST_DIR/projectB"
output_info "In projectB directory:"
project_name=$(jq -r '.project_metadata.name' "$(kb_load)")
echo "  Detected project: $project_name"
echo

# Test 3: List projects
output_header "Test 3: List All Projects" "$ICON_FOLDER"
kb_list_projects
echo

# Test 4: Share pattern to central KB
output_header "Test 4: Share Pattern to Central KB" "$ICON_SAVE"
cd "$TEST_DIR/projectA"
kb_share_pattern "architecture" '{"pattern": "MVC with dependency injection", "benefits": "testable and maintainable"}'
output_success "Shared architecture pattern from Project A"
echo

# Test 5: Search central KB
output_header "Test 5: Search Central KB" "$ICON_SEARCH"
kb_search_patterns "MVC" "architecture"
echo

# Test 6: Legacy migration
output_header "Test 6: Legacy KB Migration" "$ICON_PROGRESS"
cd "$TEST_DIR"
mkdir -p "legacyProject"
cd "legacyProject"

# Create legacy KB file
cat > project-kb.json << 'EOF'
{
  "version": "1.0",
  "project_data": {
    "brainstorm": {"sessions": ["test session"]}
  }
}
EOF

output_info "Created legacy project-kb.json"
kb_migrate_legacy "."
output_info "Checking migration result:"
ls -la .hash/
echo

# Test 7: Verify isolation
output_header "Test 7: Verify Project Isolation" "$ICON_SUCCESS"

cd "$TEST_DIR/projectA"
kb_save_session_data "$(kb_load)" "test" "phase1" '{"data": "Project A specific data"}'

cd "$TEST_DIR/projectB"
kb_save_session_data "$(kb_load)" "test" "phase1" '{"data": "Project B specific data"}'

# Check that data is isolated
cd "$TEST_DIR/projectA"
dataA=$(jq -r '.project_data.test.sessions[0].content.data' "$(kb_load)")
output_keyval "Project A data" "$dataA"

cd "$TEST_DIR/projectB"
dataB=$(jq -r '.project_data.test.sessions[0].content.data' "$(kb_load)")
output_keyval "Project B data" "$dataB"

if [[ "$dataA" != "$dataB" ]]; then
    output_success "✅ Projects are properly isolated!"
else
    output_error "❌ Project isolation failed!"
fi
echo

# Cleanup
output_header "Cleanup" "$ICON_DONE"
output_info "Test files in: $TEST_DIR"
output_info "Central KB in: $HOME/.claude/commands/#/kb/"
echo

output_success "All tests completed!"