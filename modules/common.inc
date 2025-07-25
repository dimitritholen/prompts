# Common Module - Shared Patterns

## Output Management Pattern

### File Persistence
This pattern is used by all modes to save outputs for cross-session continuity.

**At Mode Start**:
1. Create output directory: `mkdir -p docs/#`
2. Check for existing file: `docs/#/[mode-name].md`
3. If exists, briefly summarize previous sessions
4. Resume from last incomplete phase if applicable

**During Execution**:
- Save each phase output immediately after completion
- Maintain both in-memory context (for handoffs) AND file persistence
- Each save includes timestamp for tracking progress

**Resuming Work**:
- Read existing `docs/#/[mode-name].md` to understand context
- Identify last completed phase from status markers
- Continue from next phase or complete interrupted phase
- Maintain continuity with previous findings

### Save Phase Output Template

```bash
# Save [phase name] output
cat >> docs/#/[mode-name].md << 'EOF'

## Session: [DATE TIME]

### Phase [N]: [Phase Name]
#### [Section Name]
[Include findings/output]

#### [Section Name 2]
[Include findings/output]

### Status: [Next action or completion status]
EOF
```

### Standard Phase Structure

Each mode typically follows this phase structure:
1. **Research/Discovery Phase** - Gather information
2. **Analysis/Validation Phase** - Process and validate findings
3. **Solution/Design Phase** - Create the deliverable
4. **Documentation Phase** - Finalize and save outputs

### Progress Tracking

```markdown
### Phase Completion Status
- ✅ Phase 1: [Name] - Completed at [timestamp]
- 🔄 Phase 2: [Name] - In progress
- ⏳ Phase 3: [Name] - Not started
- ⏳ Phase 4: [Name] - Not started
```

### Session Management

When starting a new session:
```bash
TIMESTAMP=$(date +"%Y-%m-%d %H:%M:%S")
echo "## Session Started: $TIMESTAMP" >> docs/#/[mode-name].md
```

When resuming:
```bash
if [ -f "docs/#/[mode-name].md" ]; then
    echo "📋 Found existing work. Resuming from previous session..."
    # Parse last status
    LAST_PHASE=$(grep -E "^### Phase [0-9]+" docs/#/[mode-name].md | tail -1)
    echo "Last completed: $LAST_PHASE"
fi
```

### Error Recovery

If a phase fails or is interrupted:
```markdown
### Status: Phase [N] interrupted
- Issue: [What happened]
- Recovery: [How to continue]
- Data saved: [What was preserved]
```

## Best Practices

1. **Always save after each phase** - Don't wait until the end
2. **Include timestamps** - Helps track progress over time
3. **Use clear status markers** - Makes resuming easier
4. **Preserve context** - Include enough detail to resume later
5. **Validate saves** - Ensure file was written successfully