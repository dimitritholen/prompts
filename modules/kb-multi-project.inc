#!/bin/bash
# Multi-Project Knowledge Base System
# Provides project isolation and central knowledge repository

# Source base KB module
source "$(dirname "${BASH_SOURCE[0]}")/kb-init.inc" 2>/dev/null || source modules/kb-init.inc

# ============================================================================
# Configuration
# ============================================================================
readonly KB_PROJECT_DIR=".hash"
readonly KB_PROJECT_FILE="project.kb.json"
readonly KB_CENTRAL_DIR="$HOME/.claude/commands/#/kb"
readonly KB_CENTRAL_FILE="central.kb.json"
readonly KB_PROJECTS_REGISTRY="$KB_CENTRAL_DIR/projects.json"

# ============================================================================
# Project Detection Functions
# ============================================================================

# Find project root by looking for .hash directory or .git
find_project_root() {
    local dir="$PWD"
    
    while [[ "$dir" != "/" ]]; do
        if [[ -d "$dir/$KB_PROJECT_DIR" ]] || [[ -d "$dir/.git" ]]; then
            echo "$dir"
            return 0
        fi
        dir="$(dirname "$dir")"
    done
    
    # If no project root found, use current directory
    echo "$PWD"
}

# Get project name from directory
get_project_name() {
    local project_root="${1:-$(find_project_root)}"
    basename "$project_root"
}

# Generate project ID from path
generate_project_id() {
    local project_path="$1"
    echo "$project_path" | sha256sum | cut -c1-12
}

# ============================================================================
# Enhanced KB Initialization
# ============================================================================

# Initialize project KB with new structure
kb_init_project_enhanced() {
    local project_root="${1:-$(find_project_root)}"
    local kb_dir="$project_root/$KB_PROJECT_DIR"
    local kb_file="$kb_dir/$KB_PROJECT_FILE"
    
    # Create .hash directory if it doesn't exist
    if [[ ! -d "$kb_dir" ]]; then
        mkdir -p "$kb_dir"
        kb_log "📁 Created $KB_PROJECT_DIR directory"
        
        # Add .gitignore to keep KB files local
        cat > "$kb_dir/.gitignore" << 'EOF'
# Keep KB files local
*.kb.json
*.kb.json.bak
*.kb.json.log
EOF
    fi
    
    if [[ ! -f "$kb_file" ]]; then
        kb_log "🔧 Initializing project Knowledge Base in $KB_PROJECT_DIR/"
        
        local project_name=$(get_project_name "$project_root")
        local project_id=$(generate_project_id "$project_root")
        local timestamp=$(date -u +%Y-%m-%dT%H:%M:%SZ)
        
        # Create project KB with metadata
        cat > "$kb_file" << EOF
{
  "version": "2.0",
  "project_metadata": {
    "name": "$project_name",
    "id": "$project_id",
    "path": "$project_root",
    "created": "$timestamp",
    "last_accessed": "$timestamp"
  },
  "project_data": {
    "brainstorm": {"sessions": []},
    "prd": {"requirements": {}, "features": [], "constraints": []},
    "architect": {"design": {}, "decisions": []},
    "tasks": {"breakdown": []},
    "plan": {"schedule": {}},
    "code": {"implementations": []},
    "test": {"test_results": []},
    "deploy": {"deployments": []},
    "feature": {"integrations": []}
  },
  "pipeline_status": {},
  "research_cache": {},
  "agents_generated": {},
  "decision_log": [],
  "metrics": {}
}
EOF
        kb_log "✅ Created project KB for: $project_name (ID: $project_id)"
        
        # Register project in central KB
        register_project "$project_root" "$project_name" "$project_id"
    else
        # Update last accessed time
        local temp_file=$(mktemp)
        jq ".project_metadata.last_accessed = \"$(date -u +%Y-%m-%dT%H:%M:%SZ)\"" "$kb_file" > "$temp_file" && mv "$temp_file" "$kb_file"
    fi
}

# ============================================================================
# Central KB Functions
# ============================================================================

# Initialize central KB system
kb_init_central() {
    if [[ ! -d "$KB_CENTRAL_DIR" ]]; then
        mkdir -p "$KB_CENTRAL_DIR"
        kb_log "📁 Created central KB directory"
    fi
    
    # Initialize central KB if it doesn't exist
    if [[ ! -f "$KB_CENTRAL_DIR/$KB_CENTRAL_FILE" ]]; then
        cat > "$KB_CENTRAL_DIR/$KB_CENTRAL_FILE" << 'EOF'
{
  "version": "1.0",
  "created": "$(date -u +%Y-%m-%dT%H:%M:%SZ)",
  "patterns": {
    "architecture": [],
    "implementation": [],
    "testing": [],
    "deployment": []
  },
  "technology_insights": {},
  "common_solutions": [],
  "performance_benchmarks": {},
  "agent_templates": {},
  "shared_research": {}
}
EOF
        kb_log "✅ Initialized central Knowledge Base"
    fi
    
    # Initialize projects registry
    if [[ ! -f "$KB_PROJECTS_REGISTRY" ]]; then
        cat > "$KB_PROJECTS_REGISTRY" << 'EOF'
{
  "version": "1.0",
  "projects": []
}
EOF
        kb_log "✅ Initialized projects registry"
    fi
}

# Register project in central registry
register_project() {
    local project_path="$1"
    local project_name="$2"
    local project_id="$3"
    
    kb_init_central
    
    # Check if project already registered
    local existing=$(jq ".projects[] | select(.id == \"$project_id\")" "$KB_PROJECTS_REGISTRY")
    
    if [[ -z "$existing" ]]; then
        # Add project to registry
        local temp_file=$(mktemp)
        jq ".projects += [{
            \"id\": \"$project_id\",
            \"name\": \"$project_name\",
            \"path\": \"$project_path\",
            \"registered\": \"$(date -u +%Y-%m-%dT%H:%M:%SZ)\",
            \"last_accessed\": \"$(date -u +%Y-%m-%dT%H:%M:%SZ)\"
        }]" "$KB_PROJECTS_REGISTRY" > "$temp_file" && mv "$temp_file" "$KB_PROJECTS_REGISTRY"
        
        kb_log "📝 Registered project: $project_name"
    fi
}

# ============================================================================
# Enhanced KB Load Function
# ============================================================================

# Load project KB with new structure
kb_load_enhanced() {
    local project_root=$(find_project_root)
    local kb_file="$project_root/$KB_PROJECT_DIR/$KB_PROJECT_FILE"
    
    # Check for legacy KB file
    if [[ -f "$project_root/project-kb.json" ]] && [[ ! -f "$kb_file" ]]; then
        kb_log "🔄 Migrating legacy KB to new structure..."
        kb_migrate_legacy "$project_root"
    fi
    
    # Initialize if needed
    if [[ ! -f "$kb_file" ]]; then
        kb_init_project_enhanced "$project_root"
    fi
    
    echo "$kb_file"
}

# ============================================================================
# Legacy Migration
# ============================================================================

# Migrate legacy project-kb.json to new structure
kb_migrate_legacy() {
    local project_root="$1"
    local old_kb="$project_root/project-kb.json"
    local new_kb_dir="$project_root/$KB_PROJECT_DIR"
    local new_kb="$new_kb_dir/$KB_PROJECT_FILE"
    
    if [[ -f "$old_kb" ]]; then
        mkdir -p "$new_kb_dir"
        
        # Add project metadata to existing KB
        local project_name=$(get_project_name "$project_root")
        local project_id=$(generate_project_id "$project_root")
        local temp_file=$(mktemp)
        
        jq ". + {
            \"version\": \"2.0\",
            \"project_metadata\": {
                \"name\": \"$project_name\",
                \"id\": \"$project_id\",
                \"path\": \"$project_root\",
                \"created\": \"$(date -u +%Y-%m-%dT%H:%M:%SZ)\",
                \"last_accessed\": \"$(date -u +%Y-%m-%dT%H:%M:%SZ)\",
                \"migrated_from\": \"project-kb.json\"
            }
        }" "$old_kb" > "$temp_file" && mv "$temp_file" "$new_kb"
        
        # Keep old file as backup
        mv "$old_kb" "${old_kb}.migrated"
        
        kb_log "✅ Migrated KB to $KB_PROJECT_DIR/"
        kb_log "   Old KB backed up as project-kb.json.migrated"
        
        # Register migrated project
        register_project "$project_root" "$project_name" "$project_id"
    fi
}

# ============================================================================
# Project Management Functions
# ============================================================================

# Get current project info
kb_get_current_project() {
    local kb_file=$(kb_load_enhanced)
    
    if [[ -f "$kb_file" ]]; then
        jq -r '.project_metadata | "Project: \(.name)\nID: \(.id)\nPath: \(.path)"' "$kb_file"
    else
        echo "No project detected"
    fi
}

# List all registered projects
kb_list_projects() {
    kb_init_central
    
    if [[ -f "$KB_PROJECTS_REGISTRY" ]]; then
        echo "📋 Registered Projects:"
        echo
        jq -r '.projects[] | "  \(.name) [\(.id)]\n    Path: \(.path)\n    Last accessed: \(.last_accessed)\n"' "$KB_PROJECTS_REGISTRY"
    else
        echo "No projects registered yet"
    fi
}

# Switch to project (cd to project directory)
kb_switch_project() {
    local project_name="$1"
    kb_init_central
    
    local project_path=$(jq -r ".projects[] | select(.name == \"$project_name\") | .path" "$KB_PROJECTS_REGISTRY")
    
    if [[ -n "$project_path" ]] && [[ -d "$project_path" ]]; then
        cd "$project_path"
        kb_log "📍 Switched to project: $project_name"
        kb_get_current_project
    else
        kb_error "Project not found: $project_name"
        return 1
    fi
}

# ============================================================================
# KB Federation Functions
# ============================================================================

# Share pattern from project to central KB
kb_share_pattern() {
    local pattern_type="$1"  # architecture, implementation, testing, deployment
    local pattern_data="$2"
    local kb_file=$(kb_load_enhanced)
    
    kb_init_central
    
    # Get project metadata
    local project_name=$(jq -r '.project_metadata.name' "$kb_file")
    local project_id=$(jq -r '.project_metadata.id' "$kb_file")
    
    # Add pattern to central KB
    local temp_file=$(mktemp)
    local pattern=$(cat << EOF
{
    "source_project": "$project_name",
    "source_id": "$project_id",
    "timestamp": "$(date -u +%Y-%m-%dT%H:%M:%SZ)",
    "pattern": $pattern_data
}
EOF
)
    
    jq ".patterns.$pattern_type += [$pattern]" "$KB_CENTRAL_DIR/$KB_CENTRAL_FILE" > "$temp_file" && \
        mv "$temp_file" "$KB_CENTRAL_DIR/$KB_CENTRAL_FILE"
    
    kb_log "📤 Shared $pattern_type pattern to central KB"
}

# Search central KB for patterns
kb_search_patterns() {
    local search_term="$1"
    local pattern_type="${2:-all}"
    
    kb_init_central
    
    echo "🔍 Searching central KB for: $search_term"
    echo
    
    if [[ "$pattern_type" == "all" ]]; then
        jq -r ".patterns | to_entries[] | .value[] | select(.pattern | tostring | contains(\"$search_term\")) | 
            \"Type: \\(.key)\\nFrom: \\(.source_project)\\nPattern: \\(.pattern)\\n\"" \
            "$KB_CENTRAL_DIR/$KB_CENTRAL_FILE"
    else
        jq -r ".patterns.$pattern_type[] | select(.pattern | tostring | contains(\"$search_term\")) | 
            \"From: \\(.source_project)\\nPattern: \\(.pattern)\\n\"" \
            "$KB_CENTRAL_DIR/$KB_CENTRAL_FILE"
    fi
}

# ============================================================================
# Override Default Functions
# ============================================================================

# Override kb_load to use enhanced version
kb_load() {
    kb_load_enhanced
}

# Override kb_init_project to use enhanced version
kb_init_project() {
    kb_init_project_enhanced "$@"
}

# ============================================================================
# Export Functions
# ============================================================================
export -f find_project_root
export -f get_project_name
export -f generate_project_id
export -f kb_init_project_enhanced
export -f kb_init_central
export -f register_project
export -f kb_load_enhanced
export -f kb_migrate_legacy
export -f kb_get_current_project
export -f kb_list_projects
export -f kb_switch_project
export -f kb_share_pattern
export -f kb_search_patterns

kb_log "✅ Multi-project KB system loaded"