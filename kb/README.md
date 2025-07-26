# Hash Prompts Knowledge Base

## Overview

The Hash Prompts Knowledge Base (KB) is a structured, queryable system that stores all command information, research results, and rules in JSON format. This eliminates the need to constantly parse markdown files and enables intelligent, context-aware command execution.

## Architecture

```
kb/
├── hash-prompts-kb.json      # Core KB with all commands, rules, workflows
├── project-kb-template.json  # Template for project-specific data
├── kb-generator.js          # Script to sync KB with markdown files
├── schemas/                 # JSON schemas for validation
│   ├── command-schema.json
│   ├── rules-schema.json
│   └── project-schema.json
└── README.md               # This file
```

## Core Components

### 1. Hash Prompts KB (`hash-prompts-kb.json`)

The main knowledge base containing:

- **Commands**: All 14 commands with phases, workflows, and time estimates
- **Rules**: Global rules including mandatory parallel research
- **Relationships**: Command flow and agent generation triggers
- **Execution Patterns**: Optimized patterns like parallel research
- **Modules**: Reusable functionality across commands

### 2. Project KB Template (`project-kb-template.json`)

Template for storing project-specific data:

- **Project Data**: Command-specific data (PRDs, architecture decisions, etc.)
- **Research Cache**: Cached research results with TTL
- **Decision Log**: Audit trail of all decisions made
- **Metrics**: Performance and usage statistics
- **Session History**: Cross-session continuity

### 3. KB Generator (`kb-generator.js`)

Automated script that:
- Parses all markdown command files
- Extracts command structure, phases, and rules
- Identifies parallel research requirements
- Generates updated `hash-prompts-kb.json`
- Reports changes and validates structure

## Usage

### Generating/Updating the KB

```bash
# From the kb directory
node kb-generator.js

# Or from project root
node kb/kb-generator.js
```

This will:
1. Parse all `.md` files in the parent directory
2. Extract command information and rules
3. Generate/update `hash-prompts-kb.json`
4. Validate the structure
5. Report any changes

### Creating a Project KB

When starting a new project:

1. Copy `project-kb-template.json` to your project directory
2. Rename it (e.g., `myproject-kb.json`)
3. Update metadata:
   ```json
   {
     "metadata": {
       "project_id": "unique-id",
       "project_name": "My Project",
       "description": "Project description",
       "created": "2024-01-15T10:00:00Z",
       "last_updated": "2024-01-15T10:00:00Z"
     }
   }
   ```

### Querying the KB

Example queries:

```javascript
// Get all commands that require parallel research
const researchCommands = Object.entries(kb.commands)
  .filter(([name, cmd]) => 
    cmd.phases.some(p => p.parallel_research?.required)
  )
  .map(([name]) => name);

// Get command workflow
const workflow = kb.commands.brainstorm.workflow.next_commands;

// Check global rules
const parallelRule = kb.rules.global.parallel_research;
console.log(`Min agents: ${parallelRule.parameters.min_parallel_agents}`);

// Get time savings
const savings = parallelRule.time_savings.reduction; // "75-85%"
```

## Key Features

### 1. Mandatory Parallel Research

The KB enforces parallel research execution:

```json
{
  "parallel_research": {
    "id": "RULE_001",
    "type": "mandatory",
    "enforcement": "CRITICAL_ERROR",
    "parameters": {
      "min_parallel_agents": 6,
      "max_parallel_agents": 10
    },
    "time_savings": {
      "sequential": "30-60 seconds",
      "parallel": "5-8 seconds",
      "reduction": "75-85%"
    }
  }
}
```

### 2. Research Caching

Project KB stores research with TTL:

```json
{
  "research_cache": {
    "tech_stack_analysis_2024": {
      "id": "unique_key",
      "query": "best practices React 2024",
      "timestamp": "2024-01-15T10:00:00Z",
      "ttl_days": 30,
      "data": {
        // Research results
      }
    }
  }
}
```

### 3. Decision Tracking

All decisions are logged:

```json
{
  "decision_log": [{
    "id": "dec_001",
    "timestamp": "2024-01-15T10:00:00Z",
    "command": "architect",
    "decision": "Use microservices architecture",
    "rationale": "Need independent scaling",
    "reversible": true
  }]
}
```

### 4. Cross-Session Continuity

Session data persists across conversations:

```json
{
  "session_history": [{
    "session_id": "session_123",
    "started": "2024-01-15T09:00:00Z",
    "commands_used": ["brainstorm", "prd"],
    "outputs_generated": ["docs/#/prd-v1.md"]
  }]
}
```

## Schema Validation

All KB data is validated against JSON schemas:

- **command-schema.json**: Validates command structure
- **rules-schema.json**: Validates rule definitions  
- **project-schema.json**: Validates project-specific data

## Best Practices

1. **Keep KB in Sync**: Run `kb-generator.js` after modifying markdown files
2. **Version Control**: Commit both markdown and KB changes together
3. **Cache Wisely**: Set appropriate TTL for research (default: 30 days)
4. **Track Decisions**: Log all architectural and technical decisions
5. **Monitor Metrics**: Use metrics to optimize command performance

## Integration

### With Commands

Commands can query the KB for:
- Previous research results
- Project context and decisions
- Workflow relationships
- Rule enforcement

### With Agents

Agents access KB for:
- Technology-specific knowledge
- Best practices and patterns
- Historical decisions
- Performance metrics

## Future Enhancements

1. **GraphQL Interface**: Query KB with GraphQL
2. **Real-time Sync**: Auto-update KB on markdown changes
3. **Visualization**: D3.js workflow and relationship graphs
4. **AI Learning**: ML-based pattern recognition
5. **Distributed KB**: Multi-project knowledge sharing