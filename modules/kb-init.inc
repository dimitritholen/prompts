# Knowledge Base (KB) Initialization Module
# This module provides functions for initializing and working with the JSON-based KB system

# Function to initialize project KB
kb_init_project() {
    local project_root="${1:-.}"
    local kb_file="${project_root}/project-kb.json"
    
    if [ ! -f "$kb_file" ]; then
        echo "🔧 Initializing project Knowledge Base..."
        
        # Find the template file
        local template_paths=(
            "$HOME/.claude/commands/#/kb/project-kb-template.json"
            "./.claude/commands/#/kb/project-kb-template.json"
            "$(dirname "$0")/../kb/project-kb-template.json"
        )
        
        local template_found=false
        for template in "${template_paths[@]}"; do
            if [ -f "$template" ]; then
                cp "$template" "$kb_file"
                template_found=true
                echo "✅ Created project-kb.json from template"
                break
            fi
        done
        
        if [ "$template_found" = false ]; then
            echo "⚠️  Could not find KB template, creating minimal KB"
            cat > "$kb_file" << 'EOF'
{
  "version": "1.0",
  "created": "$(date -u +%Y-%m-%dT%H:%M:%SZ)",
  "project_data": {
    "brainstorm": {
      "sessions": []
    },
    "prd": {
      "requirements": {},
      "features": [],
      "constraints": []
    },
    "architect": {
      "design": {},
      "decisions": []
    },
    "tasks": {
      "breakdown": []
    },
    "plan": {
      "schedule": {}
    }
  },
  "research_cache": {},
  "agents_generated": {},
  "decision_log": []
}
EOF
        fi
    else
        echo "✅ Using existing project-kb.json"
    fi
}

# Function to load KB data
kb_load() {
    local kb_file="${1:-./project-kb.json}"
    
    if [ ! -f "$kb_file" ]; then
        echo "⚠️  KB file not found: $kb_file"
        kb_init_project "$(dirname "$kb_file")"
    fi
    
    # Return the KB file path for use in commands
    echo "$kb_file"
}

# Function to save data to KB
kb_save() {
    local kb_file="$1"
    local path="$2"
    local data="$3"
    
    # Using jq to update the KB (if available), otherwise append to a log
    if command -v jq &> /dev/null; then
        # Create a temporary file for the update
        local temp_file=$(mktemp)
        jq --arg path "$path" --arg data "$data" \
           'setpath($path | split("."); $data)' \
           "$kb_file" > "$temp_file" && mv "$temp_file" "$kb_file"
    else
        # Fallback: append to a change log
        echo "[$(date -u +%Y-%m-%dT%H:%M:%SZ)] $path: $data" >> "${kb_file}.log"
        echo "⚠️  jq not available, changes logged to ${kb_file}.log"
    fi
}

# Function to query KB data
kb_query() {
    local kb_file="$1"
    local path="$2"
    
    if command -v jq &> /dev/null; then
        jq -r "$path" "$kb_file" 2>/dev/null || echo "null"
    else
        echo "⚠️  jq not available for KB queries"
        echo "null"
    fi
}

# Function to append to KB array
kb_append() {
    local kb_file="$1"
    local path="$2"
    local data="$3"
    
    if command -v jq &> /dev/null; then
        local temp_file=$(mktemp)
        jq --arg path "$path" --argjson data "$data" \
           'setpath($path | split("."); (getpath($path | split(".")) // []) + [$data])' \
           "$kb_file" > "$temp_file" && mv "$temp_file" "$kb_file"
    else
        # Fallback: append to change log
        echo "[$(date -u +%Y-%m-%dT%H:%M:%SZ)] APPEND $path: $data" >> "${kb_file}.log"
    fi
}

# Function to save command output to KB
kb_save_output() {
    local kb_file="$1"
    local command="$2"
    local output_file="$3"
    local metadata="${4:-{}}"
    
    local timestamp=$(date -u +%Y-%m-%dT%H:%M:%SZ)
    local content=$(cat "$output_file" | jq -Rs .)
    
    local entry=$(cat << EOF
{
  "timestamp": "$timestamp",
  "command": "$command",
  "content": $content,
  "metadata": $metadata
}
EOF
)
    
    kb_append "$kb_file" ".project_data.$command.sessions" "$entry"
}

# Export functions for use in commands
export -f kb_init_project
export -f kb_load
export -f kb_save
export -f kb_query
export -f kb_append
export -f kb_save_output

echo "✅ KB initialization module loaded"