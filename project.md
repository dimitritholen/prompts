# Project Management Mode

Manage multiple projects with isolated knowledge bases and centralized learning repository.

## Commands

### Show Current Project
```bash
/#:project
```
Shows information about the current project based on your working directory.

### List All Projects
```bash
/#:project list
```
Lists all registered projects with their paths and last access times.

### Switch to Project
```bash
/#:project switch [project-name]
```
Changes to the project directory and shows project status.

### Search Central Knowledge
```bash
/#:project search [term] [type]
```
Searches the central KB for patterns and solutions. Type can be:
- `architecture` - Architecture patterns
- `implementation` - Implementation patterns
- `testing` - Testing strategies
- `deployment` - Deployment configurations
- `all` - Search everything (default)

### Share Pattern
```bash
/#:project share [type] [pattern-description]
```
Shares a successful pattern from current project to central KB.

### Migrate Legacy KB
```bash
/#:project migrate
```
Migrates old `project-kb.json` files to the new `.hash/` structure.

## Implementation

```bash
# Load multi-project KB system
source modules/kb-multi-project.inc
source modules/output-format.inc

# Parse command
COMMAND="${1:-status}"
shift

case "$COMMAND" in
    "status"|"")
        output_header "Current Project" "$ICON_FOLDER"
        kb_get_current_project
        ;;
        
    "list")
        output_header "Registered Projects" "$ICON_FOLDER"
        kb_list_projects
        ;;
        
    "switch")
        PROJECT_NAME="$1"
        if [[ -z "$PROJECT_NAME" ]]; then
            output_error "Please specify a project name"
            output_info "Usage: /#:project switch [project-name]"
            exit 1
        fi
        kb_switch_project "$PROJECT_NAME"
        ;;
        
    "search")
        SEARCH_TERM="$1"
        PATTERN_TYPE="${2:-all}"
        if [[ -z "$SEARCH_TERM" ]]; then
            output_error "Please specify a search term"
            output_info "Usage: /#:project search [term] [type]"
            exit 1
        fi
        output_header "Central KB Search Results" "$ICON_SEARCH"
        kb_search_patterns "$SEARCH_TERM" "$PATTERN_TYPE"
        ;;
        
    "share")
        PATTERN_TYPE="$1"
        PATTERN_DESC="$2"
        if [[ -z "$PATTERN_TYPE" ]] || [[ -z "$PATTERN_DESC" ]]; then
            output_error "Please specify pattern type and description"
            output_info "Usage: /#:project share [type] [description]"
            output_info "Types: architecture, implementation, testing, deployment"
            exit 1
        fi
        kb_share_pattern "$PATTERN_TYPE" "$(echo "$PATTERN_DESC" | jq -Rs .)"
        ;;
        
    "migrate")
        output_header "Migrating Legacy KB Files" "$ICON_PROGRESS"
        # Find all project-kb.json files
        find . -name "project-kb.json" -type f | while read -r kb_file; do
            project_dir=$(dirname "$kb_file")
            output_info "Found legacy KB in: $project_dir"
            (cd "$project_dir" && kb_migrate_legacy ".")
        done
        output_success "Migration complete!"
        ;;
        
    *)
        output_error "Unknown command: $COMMAND"
        output_info "Available commands: status, list, switch, search, share, migrate"
        exit 1
        ;;
esac
```

## Features

### Project Isolation
- Each project has its own `.hash/project.kb.json` file
- Project KBs are automatically created when you run any hash-prompts command
- KBs are gitignored by default to keep them local

### Central Knowledge Repository
- Located at `~/.claude/commands/#/kb/central.kb.json`
- Stores patterns and solutions that can be reused across projects
- Searchable database of successful implementations

### Automatic Project Detection
- Finds project root by looking for `.hash` or `.git` directories
- Automatically loads the correct KB based on your current directory
- No manual switching needed for most workflows

### Legacy Support
- Automatically migrates old `project-kb.json` files to new structure
- Preserves all existing data
- Creates backup of original file

## Example Workflow

```bash
# Start project X
cd /some/folder/projectx
/#:pipeline start
# Creates ./.hash/project.kb.json for project X

# Work on project Y
cd /some/folder/projecty  
/#:pipeline start
# Creates separate ./.hash/project.kb.json for project Y

# See all projects
/#:project list

# Search for patterns
/#:project search "authentication" architecture

# Share successful pattern
/#:project share implementation "Used dependency injection for better testability"

# Switch back to project X
/#:project switch projectx
```