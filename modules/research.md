# Research Module - Parallel Search Patterns

## Core Research Principles

**CRITICAL**: Before performing any searches, get the current date from the system using available tools. When performing searches, ALWAYS include the actual current month and year (e.g., if today is December 2025, use "December 2025") instead of generic years or outdated dates.

## Parallel Research Execution

### Implementation Pattern
```
EXECUTE ALL SEARCHES IN PARALLEL using Task agents:

"I need to research [X] different aspects. I'll spawn [X] parallel 
search agents to gather this information simultaneously, reducing 
research time from ~[Y] seconds to ~5-8 seconds."

Then create [X] Task tool invocations in a single response, each with:
- description: Brief search topic
- prompt: Detailed search instruction with specific query
- subagent_type: general-purpose
```

### Time Savings
- Sequential: N searches × 5 seconds = N×5 seconds
- Parallel: N searches in ~5-8 seconds total = 80%+ reduction

## Research Categories

### Market Research Queries
```
- "[domain] existing solutions [current month year]"
- "[domain] competitor analysis [current month year]"
- "[domain] market trends [current month year]"
- "[domain] user behavior patterns [current month year]"
- "[domain] industry standards [current month year]"
```

### Technical Research Queries
```
- "[technology] best practices [current month year]"
- "[technology] vs alternatives comparison [current month year]"
- "[technology] implementation patterns [current month year]"
- "[technology] common pitfalls avoid [current month year]"
- "[technology] performance optimization [current month year]"
```

### Architecture Research Queries
```
- "[domain] architecture patterns [current month year]"
- "microservices vs monolith [domain] [current month year]"
- "[technology] scaling strategies [user count] [current month year]"
- "[technology] security best practices [current month year]"
- "[technology] deployment strategies CI/CD [current month year]"
```

### Implementation Research Queries
```
- "existing frameworks [problem domain] [current month year]"
- "industry standard packages [technology] [current month year]"
- "Docker containers services [technology] [current month year]"
- "proven patterns [specific task] [current month year]"
```

## Cache Integration

### Check Cache First
```bash
# Before executing searches:
if [ -f ".claude/shared_research.md" ]; then
    echo "✓ Checking shared research document..."
fi

# Check research cache
check_cache() {
    local query="$1"
    local cache_key=$(echo -n "$query" | sha256sum | cut -c1-16)
    local cache_file=".claude/research_cache/${cache_key}.md"
    
    if [ -f "$cache_file" ]; then
        local age=$(($(date +%s) - $(stat -c %Y "$cache_file" 2>/dev/null)))
        if [ $age -lt 86400 ]; then  # 24 hour cache
            echo "✓ Found cached research for: $query"
            return 0
        fi
    fi
    return 1
}
```

### Update Shared Research
After completing searches, update the shared research document:
```bash
cat >> .claude/shared_research.md << 'EOF'
### [Research Category]: [Topic]
**Researched**: [Date]
**Key Findings**:
- [Finding 1]
- [Finding 2]
- [Finding 3]
EOF
```

## Research Quality Guidelines

### For Each Finding
1. **Surface Fact** → State the finding clearly
2. **Dig Deeper** → Understand the reasoning/context
3. **Extract Principle** → What can we learn?
4. **Apply to Context** → How does this affect our project?

### Validation Questions
- Is this from a credible source?
- Is this information current (check date)?
- Does this apply to our specific context?
- Are there contradicting viewpoints?

## Common Research Patterns by Mode

### Brainstorm Mode (8 parallel searches)
- Existing solutions
- Competitor analysis
- Market trends
- User problems
- Best practices
- Technology recommendations
- Regulatory requirements
- Failed attempts lessons

### PRD Mode (6 parallel searches)
- Similar solutions
- Market gaps
- Success patterns
- Technical frameworks
- Industry standards
- Compliance requirements

### Architect Mode (15-20 parallel searches)
- Architecture patterns (4 searches)
- Technology comparisons (5 per tech)
- Integration patterns
- Scalability strategies
- Security considerations

### Tasks Mode (6 parallel searches)
- Implementation frameworks
- Standard packages
- Docker services
- Architecture patterns
- Best practices
- Common pitfalls

### Plan Mode (6 parallel searches)
- Implementation patterns
- Similar solutions
- Optimization techniques
- Security practices
- Performance patterns
- Maintenance insights