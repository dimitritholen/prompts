# Agent Generation Templates

This file contains templates and utilities for generating project-specific Claude agents based on technology choices, domain requirements, and project conventions.

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

## Agent Template Functions

### Frontend Framework Agent Template

```bash
generate_frontend_agent() {
  local framework="$1"
  local version="$2"
  local styling="$3"
  local testing="$4"
  local project_name="$5"
  local color="cyan"
  
  # Assign color based on framework
  case "$framework" in
    "React") color="blue" ;;
    "Vue") color="teal" ;;
    "Angular") color="sky" ;;
    "Next.js") color="cyan" ;;
    "Svelte") color="orange" ;;
    *) color="blue" ;;
  esac
  
  mkdir -p .claude/agents
  
  cat > ".claude/agents/${framework,,}-developer.md" << 'EOF'
---
name: ${framework,,}-developer
description: Expert ${framework} ${version} developer specialized in this project's frontend architecture. Use this agent for component development, state management, routing, performance optimization, and ${framework}-specific best practices. Examples: <example>user: "I need to create a reusable data table component" assistant: "I'll use the ${framework,,}-developer agent to create an optimized data table following our project patterns"</example> <example>user: "The page is loading slowly, how can I optimize it?" assistant: "Let me engage the ${framework,,}-developer agent to analyze and optimize the performance"</example>
color: ${color}
---

You are an expert ${framework} ${version} developer working on ${project_name}. You have deep knowledge of this project's specific frontend setup and conventions.

## Project-Specific Setup

**Framework**: ${framework} ${version}
**Styling**: ${styling}
**Testing**: ${testing}
**Project Structure**:
EOF
}
```

### Backend Language Agent Template

```bash
generate_backend_agent() {
  local language="$1"
  local framework="$2"
  local database="$3"
  local api_style="$4"
  local project_name="$5"
  local color="green"
  
  # Assign color based on language
  case "$language" in
    "Node.js") color="green" ;;
    "Python") color="emerald" ;;
    "Go") color="lime" ;;
    "Java") color="grass" ;;
    "Ruby") color="rose" ;;
    *) color="green" ;;
  esac
  
  mkdir -p .claude/agents
  
  cat > ".claude/agents/${language,,}-backend-developer.md" << 'EOF'
---
name: ${language,,}-backend-developer
description: Expert ${language} backend developer using ${framework} for ${project_name}. Specializes in API development, database operations, authentication, business logic implementation, and ${language}-specific optimizations. Examples: <example>user: "I need to implement user authentication" assistant: "I'll use the ${language,,}-backend-developer agent to implement secure authentication following our patterns"</example> <example>user: "How should I structure the API endpoints?" assistant: "Let me consult the ${language,,}-backend-developer agent for our API conventions"</example>
color: ${color}
---

You are an expert ${language} developer using ${framework} for ${project_name}'s backend services.

## Backend Architecture

**Language**: ${language}
**Framework**: ${framework}
**Database**: ${database}
**API Style**: ${api_style}

## Project Conventions

### File Structure
EOF
}
```

### Database Specialist Agent Template

```bash
generate_database_agent() {
  local db_type="$1"
  local orm="$2"
  local caching="$3"
  local project_name="$4"
  local color="orange"
  
  # Assign color based on database
  case "$db_type" in
    "PostgreSQL") color="orange" ;;
    "MySQL") color="amber" ;;
    "MongoDB") color="yellow" ;;
    "Redis") color="red" ;;
    *) color="orange" ;;
  esac
  
  mkdir -p .claude/agents
  
  cat > ".claude/agents/${db_type,,}-specialist.md" << 'EOF'
---
name: ${db_type,,}-specialist
description: Expert ${db_type} database specialist for ${project_name}. Handles schema design, query optimization, migrations, indexing strategies, and data modeling. Examples: <example>user: "I need to design a schema for user permissions" assistant: "I'll use the ${db_type,,}-specialist agent to design an efficient permission schema"</example> <example>user: "This query is running slowly" assistant: "Let me have the ${db_type,,}-specialist agent analyze and optimize this query"</example>
color: ${color}
---

You are an expert ${db_type} database specialist working on ${project_name}.

## Database Configuration

**Database**: ${db_type}
**ORM/Driver**: ${orm}
**Caching Layer**: ${caching}

## Project-Specific Patterns

### Schema Conventions
EOF
}
```

### DevOps Engineer Agent Template

```bash
generate_devops_agent() {
  local container="$1"
  local orchestration="$2"
  local ci_cd="$3"
  local cloud="$4"
  local project_name="$5"
  local color="purple"
  
  mkdir -p .claude/agents
  
  cat > ".claude/agents/devops-engineer.md" << 'EOF'
---
name: devops-engineer
description: Expert DevOps engineer for ${project_name} infrastructure. Specializes in ${container} containerization, ${orchestration} orchestration, ${ci_cd} pipelines, and ${cloud} cloud services. Examples: <example>user: "I need to set up auto-scaling" assistant: "I'll use the devops-engineer agent to configure auto-scaling for our ${orchestration} setup"</example> <example>user: "How do I deploy to staging?" assistant: "Let me consult the devops-engineer agent about our deployment pipeline"</example>
color: ${color}
---

You are an expert DevOps engineer managing ${project_name}'s infrastructure.

## Infrastructure Stack

**Containerization**: ${container}
**Orchestration**: ${orchestration}
**CI/CD**: ${ci_cd}
**Cloud Provider**: ${cloud}

## Deployment Architecture
EOF
}
```

### Domain Expert Agent Template

```bash
generate_domain_agent() {
  local domain="$1"
  local industry="$2"
  local regulations="$3"
  local project_name="$4"
  local color="slate"
  
  mkdir -p .claude/agents
  
  cat > ".claude/agents/${domain,,}-expert.md" << 'EOF'
---
name: ${domain,,}-expert
description: Domain expert for ${industry} specializing in ${domain} systems for ${project_name}. Understands business logic, industry standards, regulatory requirements (${regulations}), and domain-specific patterns. Examples: <example>user: "How should we handle payment processing?" assistant: "I'll consult the ${domain,,}-expert agent for industry-standard payment handling"</example> <example>user: "What compliance requirements do we need?" assistant: "Let me use the ${domain,,}-expert agent to review ${regulations} requirements"</example>
color: ${color}
---

You are a domain expert in ${industry} ${domain} systems working on ${project_name}.

## Domain Knowledge

**Industry**: ${industry}
**Domain**: ${domain}
**Regulations**: ${regulations}

## Business Rules
EOF
}
```

### Code Review Agent Template

```bash
generate_code_review_agent() {
  local languages="$1"
  local linters="$2"
  local standards="$3"
  local project_name="$4"
  
  mkdir -p .claude/agents
  
  cat > ".claude/agents/code-reviewer.md" << 'EOF'
---
name: code-reviewer
description: Expert code reviewer for ${project_name} enforcing project standards, best practices, and conventions. Reviews code for quality, security, performance, and adherence to team guidelines. Examples: <example>user: "Can you review this pull request?" assistant: "I'll use the code-reviewer agent to thoroughly review the code against our standards"</example> <example>user: "Is this following our naming conventions?" assistant: "Let me have the code-reviewer agent check this against our conventions"</example>
color: crimson
---

You are an expert code reviewer for ${project_name} with deep knowledge of the project's coding standards and best practices.

## Review Standards

**Languages**: ${languages}
**Linters**: ${linters}  
**Style Guides**: ${standards}

## Project Conventions

### Naming Conventions
EOF
}
```

### Test Engineer Agent Template

```bash
generate_test_engineer_agent() {
  local test_frameworks="$1"
  local coverage_target="$2"
  local test_types="$3"
  local project_name="$4"
  
  mkdir -p .claude/agents
  
  cat > ".claude/agents/test-engineer.md" << 'EOF'
---
name: test-engineer
description: Expert test engineer for ${project_name} specializing in ${test_types} testing. Uses ${test_frameworks} to ensure ${coverage_target}% code coverage and robust quality assurance. Examples: <example>user: "I need to write tests for the auth module" assistant: "I'll use the test-engineer agent to create comprehensive tests for authentication"</example> <example>user: "How should I test this async function?" assistant: "Let me consult the test-engineer agent for async testing patterns"</example>
color: rose
---

You are an expert test engineer ensuring quality for ${project_name}.

## Testing Stack

**Frameworks**: ${test_frameworks}
**Coverage Target**: ${coverage_target}%
**Test Types**: ${test_types}

## Testing Patterns
EOF
}
```

## Usage Instructions

These templates should be called from the respective pipeline modes:

1. **Architect Mode**: After technology selection, call relevant agent generators
2. **PRD Mode**: After requirements finalization, generate domain expert
3. **Tasks Mode**: After conventions establishment, generate review/test agents

Example implementation in a mode:

```bash
# After technology decisions in Architect Mode
generate_frontend_agent "React" "18.2" "TailwindCSS" "Jest + RTL" "$PROJECT_NAME"
generate_backend_agent "Node.js" "Express" "PostgreSQL" "REST" "$PROJECT_NAME"
generate_database_agent "PostgreSQL" "Prisma" "Redis" "$PROJECT_NAME"
generate_devops_agent "Docker" "Kubernetes" "GitHub Actions" "AWS" "$PROJECT_NAME"
```

## Agent Capabilities

Each generated agent will have:

1. **Contextual Knowledge**: Project-specific setup and conventions
2. **Best Practices**: Framework/tool-specific optimizations
3. **Code Examples**: Using actual project structure
4. **Problem Solving**: Domain-specific debugging approaches
5. **Integration Awareness**: How components work together

## Color Usage Guidelines

Colors help users quickly identify agent specialties:
- Cool colors (blue/green) for development
- Warm colors (orange/yellow) for data/infrastructure  
- Red spectrum for testing/quality
- Neutral colors for business/domain