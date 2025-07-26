#!/bin/bash
# Knowledge Base (KB) Helper Functions
# High-level functions to simplify KB operations and reduce output noise

# Source the multi-project KB module (which sources kb-init.inc)
source "$(dirname "${BASH_SOURCE[0]}")/kb-multi-project.inc" 2>/dev/null || source modules/kb-multi-project.inc

# Override the confirmation message from kb-init.inc
kb_log() {
    [[ "$KB_QUIET_MODE" != "true" ]] && [[ "$1" != "✅ KB initialization module loaded" ]] && echo "$@"
}

# Fixed kb_save function with proper jq syntax
kb_save() {
    local kb_file="$1"
    local path="$2"
    local data="$3"
    
    if command -v jq &> /dev/null; then
        # Create a temporary file for the update
        local temp_file=$(mktemp)
        
        # Remove quotes from path and split by dots
        path=$(echo "$path" | sed 's/^\.*//')
        
        # Use proper jq syntax to set the value at the path
        if [[ "$data" =~ ^\{.*\}$ ]] || [[ "$data" =~ ^\[.*\]$ ]]; then
            # Data is already JSON
            jq ".$path = $data" "$kb_file" > "$temp_file" && mv "$temp_file" "$kb_file"
        else
            # Data needs to be treated as a string/value
            jq ".$path = $data" "$kb_file" > "$temp_file" && mv "$temp_file" "$kb_file"
        fi
    else
        # Fallback: append to a change log
        echo "[$(date -u +%Y-%m-%dT%H:%M:%SZ)] $path: $data" >> "${kb_file}.log"
        kb_error "jq not available, changes logged to ${kb_file}.log"
    fi
}

# ============================================================================
# Pipeline-Specific Helper Functions
# ============================================================================

# Get current pipeline stage (clean output)
kb_get_current_stage() {
    local kb_file="${1:-$(kb_load)}"
    local stage=$(kb_query "$kb_file" '.pipeline_status.current_stage' | tr -d '"')
    
    if [ "$stage" != "null" ] && [ -n "$stage" ]; then
        echo "$stage"
    else
        echo "none"
    fi
}

# Update pipeline stage with clean output
kb_pipeline_update_stage() {
    local kb_file="${1:-$(kb_load)}"
    local new_stage="$2"
    local from_stage="${3:-$(kb_get_current_stage "$kb_file")}"
    local timestamp=$(date -u +%Y-%m-%dT%H:%M:%SZ)
    
    # Update stage status
    kb_save "$kb_file" ".pipeline_status.stages.$from_stage.status" '"completed"' >/dev/null 2>&1
    kb_save "$kb_file" ".pipeline_status.stages.$from_stage.completed_at" "\"$timestamp\"" >/dev/null 2>&1
    kb_save "$kb_file" ".pipeline_status.stages.$new_stage.status" '"in_progress"' >/dev/null 2>&1
    kb_save "$kb_file" ".pipeline_status.current_stage" "\"$new_stage\"" >/dev/null 2>&1
    kb_save "$kb_file" ".pipeline_status.last_updated" "\"$timestamp\"" >/dev/null 2>&1
    
    kb_log "✅ Stage updated: $from_stage → $new_stage"
}

# Create pipeline handoff with minimal output
kb_pipeline_handoff() {
    local kb_file="${1:-$(kb_load)}"
    local from_stage="$2"
    local to_stage="$3"
    local handoff_data="$4"
    
    local timestamp=$(date -u +%Y-%m-%dT%H:%M:%SZ)
    local handoff=$(cat << EOF
{
    "timestamp": "$timestamp",
    "from": "$from_stage",
    "to": "$to_stage",
    "data": $handoff_data
}
EOF
)
    
    kb_save "$kb_file" ".handoffs.$from_stage.$to_stage" "$handoff" >/dev/null 2>&1
    kb_log "📦 Handoff created: $from_stage → $to_stage"
}

# Show clean pipeline status
kb_pipeline_status() {
    local kb_file="${1:-$(kb_load)}"
    local status=$(kb_query "$kb_file" '.pipeline_status')
    
    if [ "$status" = "null" ]; then
        echo "❌ No pipeline in progress"
        return 1
    fi
    
    local project_name=$(kb_query "$kb_file" '.pipeline_status.project_name' | tr -d '"')
    local project_id=$(kb_query "$kb_file" '.pipeline_status.project_id' | tr -d '"')
    local current_stage=$(kb_query "$kb_file" '.pipeline_status.current_stage' | tr -d '"')
    local started=$(kb_query "$kb_file" '.pipeline_status.started' | tr -d '"')
    
    echo "📊 Pipeline Status"
    echo "  Project: $project_name"
    echo "  ID: $project_id"
    echo "  Started: $(kb_format_timestamp "$started")"
    echo "  Current: $current_stage"
    echo ""
    echo "  Progress:"
    
    # Show stage progress
    local stages=("brainstorm" "prd" "architect" "tasks" "plan" "code" "test" "deploy")
    for stage in "${stages[@]}"; do
        local stage_status=$(kb_query "$kb_file" ".pipeline_status.stages.$stage.status" | tr -d '"')
        kb_format_stage_status "$stage" "$stage_status"
    done
}

# Get list of completed stages
kb_get_completed_stages() {
    local kb_file="${1:-$(kb_load)}"
    local stages=("brainstorm" "prd" "architect" "tasks" "plan" "code" "test" "deploy")
    local completed=()
    
    for stage in "${stages[@]}"; do
        local status=$(kb_query "$kb_file" ".pipeline_status.stages.$stage.status" | tr -d '"')
        if [ "$status" = "completed" ]; then
            completed+=("$stage")
        fi
    done
    
    printf '%s\n' "${completed[@]}"
}

# ============================================================================
# Data Query Helper Functions
# ============================================================================

# Get project name only
kb_get_project_name() {
    local kb_file="${1:-$(kb_load)}"
    local name=$(kb_query "$kb_file" '.pipeline_status.project_name' | tr -d '"')
    
    if [ "$name" != "null" ] && [ -n "$name" ]; then
        echo "$name"
    else
        echo "Unnamed Project"
    fi
}

# Get project ID only
kb_get_project_id() {
    local kb_file="${1:-$(kb_load)}"
    local id=$(kb_query "$kb_file" '.pipeline_status.project_id' | tr -d '"')
    
    if [ "$id" != "null" ] && [ -n "$id" ]; then
        echo "$id"
    else
        echo "no-id"
    fi
}

# Count sessions for a given mode
kb_count_sessions() {
    local kb_file="${1:-$(kb_load)}"
    local mode="$2"
    
    local count=$(kb_query "$kb_file" ".project_data.$mode.sessions | length")
    if [ "$count" = "null" ]; then
        echo "0"
    else
        echo "$count"
    fi
}

# Check if a path has data
kb_has_data() {
    local kb_file="${1:-$(kb_load)}"
    local path="$2"
    
    local data=$(kb_query "$kb_file" "$path")
    if [ "$data" != "null" ] && [ "$data" != "[]" ] && [ "$data" != "{}" ]; then
        return 0
    else
        return 1
    fi
}

# Save session data with clean output
kb_save_session_data() {
    local kb_file="${1:-$(kb_load)}"
    local mode="$2"
    local phase="$3"
    local content="$4"
    local metadata="${5:-{}}"
    
    local timestamp=$(date -u +%Y-%m-%dT%H:%M:%SZ)
    local session_data=$(cat << EOF
{
    "timestamp": "$timestamp",
    "phase": "$phase",
    "content": $content,
    "metadata": $metadata
}
EOF
)
    
    kb_append "$kb_file" ".project_data.$mode.sessions" "$session_data" >/dev/null 2>&1
    kb_log "💾 Saved: $mode/$phase session data"
}

# ============================================================================
# Output Formatting Helper Functions
# ============================================================================

# Format stage status with icons
kb_format_stage_status() {
    local stage="$1"
    local status="$2"
    local stage_display=$(echo "$stage" | sed 's/^\(.\)/\u\1/')  # Capitalize first letter
    
    case "$status" in
        "completed")
            echo "  ✅ $stage_display"
            ;;
        "in_progress")
            echo "  🔄 $stage_display (in progress)"
            ;;
        "pending"|"null"|"")
            echo "  ⏳ $stage_display"
            ;;
        *)
            echo "  ❓ $stage_display ($status)"
            ;;
    esac
}

# Format timestamp to human-readable
kb_format_timestamp() {
    local timestamp="$1"
    
    if [ "$timestamp" = "null" ] || [ -z "$timestamp" ]; then
        echo "Unknown"
        return
    fi
    
    # Try to format with date command if available
    if command -v date >/dev/null 2>&1; then
        # Remove quotes if present
        timestamp=$(echo "$timestamp" | tr -d '"')
        
        # Try GNU date first (Linux)
        if date --version >/dev/null 2>&1; then
            date -d "$timestamp" "+%Y-%m-%d %H:%M" 2>/dev/null || echo "$timestamp"
        else
            # Try BSD date (macOS)
            date -j -f "%Y-%m-%dT%H:%M:%SZ" "$timestamp" "+%Y-%m-%d %H:%M" 2>/dev/null || echo "$timestamp"
        fi
    else
        echo "$timestamp"
    fi
}

# Show visual progress bar
kb_format_progress_bar() {
    local current="$1"
    local total="$2"
    local width="${3:-20}"
    
    if [ "$total" -eq 0 ]; then
        echo "[No stages]"
        return
    fi
    
    local percent=$((current * 100 / total))
    local filled=$((width * current / total))
    local empty=$((width - filled))
    
    printf "["
    printf "%${filled}s" | tr ' ' '█'
    printf "%${empty}s" | tr ' ' '░'
    printf "] %d%%" "$percent"
}

# ============================================================================
# Utility Functions
# ============================================================================

# Initialize pipeline with clean output
kb_init_pipeline() {
    local project_name="${1:-New Project}"
    local kb_file="$(kb_load)"
    
    local project_id=$(uuidgen 2>/dev/null || date +%s | sha256sum | cut -c1-8)
    local timestamp=$(date -u +%Y-%m-%dT%H:%M:%SZ)
    
    local pipeline_status=$(cat << EOF
{
    "project_name": "$project_name",
    "project_id": "$project_id",
    "started": "$timestamp",
    "current_stage": "brainstorm",
    "stages": {
        "brainstorm": {"status": "pending"},
        "prd": {"status": "pending"},
        "architect": {"status": "pending"},
        "tasks": {"status": "pending"},
        "plan": {"status": "pending"},
        "code": {"status": "pending"},
        "test": {"status": "pending"},
        "deploy": {"status": "pending"}
    }
}
EOF
)
    
    kb_save "$kb_file" '.pipeline_status' "$pipeline_status" >/dev/null 2>&1
    
    echo "🚀 Pipeline initialized"
    echo "  Project: $project_name"
    echo "  ID: $project_id"
    echo "  Next: /#:brainstorm [your idea]"
}

# Clean pipeline status display
kb_show_next_action() {
    local kb_file="${1:-$(kb_load)}"
    local current_stage=$(kb_get_current_stage "$kb_file")
    
    case "$current_stage" in
        "brainstorm")
            echo "📝 Next: Complete brainstorming with /#:brainstorm"
            ;;
        "prd")
            echo "📋 Next: Create PRD with /#:prd"
            ;;
        "architect")
            echo "🏗️ Next: Design architecture with /#:architect"
            ;;
        "tasks")
            echo "📋 Next: Break down tasks with /#:tasks"
            ;;
        "plan")
            echo "📅 Next: Create plan with /#:plan"
            ;;
        "code")
            echo "💻 Next: Start coding with /#:code"
            ;;
        "test")
            echo "🧪 Next: Run tests with /#:test"
            ;;
        "deploy")
            echo "🚀 Next: Deploy with /#:deploy"
            ;;
        *)
            echo "🚀 Next: Start pipeline with /#:pipeline start"
            ;;
    esac
}

# Export all helper functions
export -f kb_get_current_stage
export -f kb_pipeline_update_stage
export -f kb_pipeline_handoff
export -f kb_pipeline_status
export -f kb_get_completed_stages
export -f kb_get_project_name
export -f kb_get_project_id
export -f kb_count_sessions
export -f kb_has_data
export -f kb_save_session_data
export -f kb_format_stage_status
export -f kb_format_timestamp
export -f kb_format_progress_bar
export -f kb_init_pipeline
export -f kb_show_next_action

kb_log "✅ KB helper functions loaded"