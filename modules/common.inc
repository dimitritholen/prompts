# Common Module - Shared Patterns

## Output Management Pattern

### Knowledge Base Integration
This pattern is used by all modes to save outputs using the JSON-based Knowledge Base system.

**At Mode Start**:
1. Source KB module: `source modules/kb-init.inc`
2. Initialize project KB: `kb_init_project .`
3. Load KB: `KB_FILE=$(kb_load)`
4. Check for existing sessions in KB
5. Resume from last incomplete phase if applicable

**During Execution**:
- Save each phase output to KB immediately after completion
- Use structured JSON for all data storage
- Cache research results with TTL
- Log all decisions for audit trail

**Resuming Work**:
- Query KB for previous sessions: `kb_query "$KB_FILE" '.project_data.[mode].sessions'`
- Load last phase status from KB
- Continue from next phase or complete interrupted phase
- Leverage cached research to avoid duplication

### Save Phase Output Template

```bash
# Save phase output to KB
PHASE_DATA=$(cat << EOF
{
  "phase": "[Phase Name]",
  "timestamp": "$(date -u +%Y-%m-%dT%H:%M:%SZ)",
  "content": $(echo "[Phase content]" | jq -Rs .),
  "status": "[completed/in_progress]",
  "metadata": {
    "key": "value"
  }
}
EOF
)

kb_append "$KB_FILE" '.project_data.[mode].sessions' "$PHASE_DATA"
kb_save "$KB_FILE" '.pipeline_status.stages.[mode].last_phase' '"[Phase Name]"'
```

### Standard Phase Structure

Each mode typically follows this phase structure:
1. **Research/Discovery Phase** - Gather information (cache in KB)
2. **Analysis/Validation Phase** - Process findings (store in KB)
3. **Solution/Design Phase** - Create deliverable (save to KB)
4. **Documentation Phase** - Finalize outputs (mark complete in KB)

### Progress Tracking

```bash
# Update progress in KB
kb_save "$KB_FILE" '.pipeline_status.stages.[mode].phases' '{
  "phase_1": {"name": "Research", "status": "completed", "timestamp": "..."},
  "phase_2": {"name": "Analysis", "status": "in_progress", "timestamp": "..."},
  "phase_3": {"name": "Solution", "status": "pending"},
  "phase_4": {"name": "Documentation", "status": "pending"}
}'
```

### Session Management

When starting a new session:
```bash
SESSION_ID=$(date +%s | sha256sum | cut -c1-8)
SESSION_DATA=$(cat << EOF
{
  "id": "$SESSION_ID",
  "started": "$(date -u +%Y-%m-%dT%H:%M:%SZ)",
  "mode": "[mode-name]",
  "phase": "starting"
}
EOF
)
kb_append "$KB_FILE" '.sessions' "$SESSION_DATA"
```

When resuming:
```bash
# Check for existing sessions
EXISTING=$(kb_query "$KB_FILE" '.project_data.[mode].sessions')
if [ "$EXISTING" != "null" ] && [ "$EXISTING" != "[]" ]; then
    echo "📋 Found existing work. Resuming from previous session..."
    LAST_PHASE=$(kb_query "$KB_FILE" '.pipeline_status.stages.[mode].last_phase')
    echo "Last completed phase: $LAST_PHASE"
fi
```

### Error Recovery

If a phase fails or is interrupted:
```bash
ERROR_DATA=$(cat << EOF
{
  "phase": "[Phase Name]",
  "timestamp": "$(date -u +%Y-%m-%dT%H:%M:%SZ)",
  "error": "[What happened]",
  "recovery": "[How to continue]",
  "data_saved": true
}
EOF
)
kb_append "$KB_FILE" '.error_log' "$ERROR_DATA"
```

## KB Functions Reference

- `kb_init_project [path]` - Initialize KB for project
- `kb_load` - Get KB file path
- `kb_save [path] [data]` - Save data to specific path
- `kb_query [path]` - Query data from KB
- `kb_append [path] [data]` - Append to array in KB
- `kb_save_output [command] [file]` - Save command output

## Best Practices

1. **Always use KB for persistence** - No more markdown files
2. **Structure data properly** - Use JSON for all storage
3. **Cache research results** - Check KB before searching
4. **Track all decisions** - Maintain audit trail in KB
5. **Handle errors gracefully** - Log to KB for recovery