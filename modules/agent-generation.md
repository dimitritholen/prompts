# Agent Generation Module

## Color Palette

### Tech Stack Colors
- **Frontend Frameworks**: blue, cyan, teal, sky
- **Backend Languages**: green, emerald, lime, grass  
- **Databases**: orange, amber, yellow, gold
- **DevOps/Infrastructure**: purple, violet, indigo, plum
- **Testing/QA**: red, rose, pink, crimson
- **Domain/Business**: slate, stone, gray, zinc
- **Security/Compliance**: scarlet, ruby, maroon
- **Performance**: turquoise, aqua, mint

## Core Functions

### Generate Color Function
```bash
# Function to generate consistent color from technology name
generate_color() {
    local tech_name="$1"
    local colors=("blue" "teal" "sky" "cyan" "orange" "indigo" "lime" "emerald" "purple" "pink" "rose" "amber" "yellow" "green" "red")
    local hash=$(echo -n "$tech_name" | cksum | cut -d' ' -f1)
    local color_index=$((hash % ${#colors[@]}))
    echo "${colors[$color_index]}"
}
```

### Generate Dynamic Agent Function
```bash
# Function to generate agent from research data
generate_dynamic_agent() {
    local category="$1"
    local tech_name="$2"
    local version="$3"
    local expert_areas="$4"
    local common_tasks="$5"
    local best_practices="$6"
    local trigger_scenarios="$7"
    
    # Generate agent name (lowercase, replace spaces with hyphens)
    local agent_name=$(echo "$tech_name-$category" | tr '[:upper:]' '[:lower:]' | tr ' ' '-' | tr '/' '-')
    
    # Generate color
    local color=$(generate_color "$tech_name")
    
    # Check if agent already exists
    if [ -f ".claude/agents/${agent_name}.md" ]; then
        echo "  ⚠️  Agent ${agent_name} already exists, updating..."
    fi
    
    # Generate agent description from research
    local description="Use this agent when you need expert assistance with ${tech_name}${version:+ ${version}} for ${PROJECT_NAME}"
    
    # Add expert areas if provided
    if [ -n "$expert_areas" ] && [ "$expert_areas" != "[From Phase 1 research]" ]; then
        description="${description}, including ${expert_areas}"
    fi
    
    # Add trigger scenarios as examples
    local examples=""
    if [ -n "$trigger_scenarios" ] && [ "$trigger_scenarios" != "[From Phase 1 research]" ]; then
        examples=" Examples: <example>Context: ${trigger_scenarios} user: \"[user question]\" assistant: \"I'll use the ${agent_name} agent to help with this ${tech_name} task\" <commentary>This requires ${tech_name}-specific expertise for ${PROJECT_NAME}.</commentary></example>"
    else
        # Generate generic examples based on category
        case "$category" in
            "frontend")
                examples=" Examples: <example>Context: User needs help with UI components. user: \"I need to create a responsive navigation menu\" assistant: \"I'll use the ${agent_name} agent to create an optimized navigation component\" <commentary>This requires ${tech_name}-specific UI development expertise.</commentary></example>"
                ;;
            "backend")
                examples=" Examples: <example>Context: User needs API development help. user: \"I need to implement user authentication\" assistant: \"I'll use the ${agent_name} agent to implement secure authentication\" <commentary>This requires ${tech_name}-specific backend expertise.</commentary></example>"
                ;;
            "database")
                examples=" Examples: <example>Context: User needs database optimization. user: \"This query is running slowly\" assistant: \"I'll use the ${agent_name} agent to optimize the query performance\" <commentary>This requires ${tech_name}-specific database expertise.</commentary></example>"
                ;;
            *)
                examples=" Examples: <example>Context: User needs ${category} assistance. user: \"I need help with ${category} configuration\" assistant: \"I'll use the ${agent_name} agent for expert ${tech_name} guidance\" <commentary>This requires specialized ${tech_name} knowledge.</commentary></example>"
                ;;
        esac
    fi
    
    # Create agent file
    cat > ".claude/agents/${agent_name}.md" << AGENT_EOF
---
name: ${agent_name}
description: ${description}.${examples}
color: ${color}
---

You are an expert ${tech_name}${version:+ ${version}} specialist working on ${PROJECT_NAME}.

## Technology Expertise

**Technology**: ${tech_name}${version:+ ${version}}
**Category**: ${category}
**Project**: ${PROJECT_NAME}

## Core Competencies

${expert_areas:+### Expert Areas
${expert_areas}

}${common_tasks:+### Common Tasks
${common_tasks}

}${best_practices:+### Best Practices
${best_practices}

}## Project Integration

You understand how ${tech_name} integrates with the other technologies in this project's stack and follow the architectural decisions made for ${PROJECT_NAME}.

## Development Principles

- Apply project-specific patterns and conventions
- Optimize for the project's performance requirements
- Ensure compatibility with the overall architecture
- Follow security best practices for ${tech_name}
- Maintain code quality and documentation standards

[Additional project-specific guidelines will be populated from architecture decisions]
AGENT_EOF
    
    echo "✓ Created ${agent_name} agent (${color})"
}
```

## Usage Examples

### Generate Frontend Agent
```bash
generate_dynamic_agent "frontend" "React" "18.2" \
    "Component development, State management, Performance optimization" \
    "Creating reusable components, Managing application state, Implementing routing" \
    "Use functional components, Implement proper memoization, Follow accessibility guidelines" \
    "Building interactive UIs, Optimizing render performance"
```

### Generate Backend Agent
```bash
generate_dynamic_agent "backend" "Node.js" "20.x" \
    "API development, Database operations, Authentication, Microservices" \
    "Building REST APIs, Implementing middleware, Database queries" \
    "Use async/await, Implement proper error handling, Follow security best practices" \
    "Creating scalable backend services"
```

### Generate Database Agent
```bash
generate_dynamic_agent "database" "PostgreSQL" "15" \
    "Schema design, Query optimization, Indexing strategies" \
    "Designing schemas, Writing complex queries, Performance tuning" \
    "Normalize appropriately, Use proper indexing, Implement data validation" \
    "Optimizing database performance"
```

## Standard Agent Types

### Domain Agents (PRD Mode)
- `product-manager`: Product strategy and requirements
- `ux-designer`: User experience and design
- `[domain]-expert`: Domain-specific knowledge
- `compliance-officer`: Regulatory requirements

### Tech Stack Agents (Architect Mode)
- `[framework]-developer`: Frontend frameworks
- `[language]-backend-developer`: Backend languages
- `[database]-specialist`: Database systems
- `devops-engineer`: Infrastructure and deployment

### Quality Agents (Tasks Mode)
- `code-reviewer`: Code quality and standards
- `test-engineer`: Testing strategies
- `security-engineer`: Security auditing
- `performance-optimizer`: Performance tuning
- `documentation-writer`: Technical documentation