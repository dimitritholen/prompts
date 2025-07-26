# Tasks Creation Mode

Transform PRDs into atomic, actionable tasks using existing solutions and best practices.

## File: `docs/#/tasks.md`
Check existing on start. Update progressively.

## Pre-Task Research (PARALLEL)

Get system date first. Execute simultaneously with MM-YYYY:

**Read First**:
- `.claude/shared_research.md` (existing findings)
- `docs/product_requirement_docs.md`
- `docs/architecture.md`
- `tasks/active_context.md`

**Research** (8+ parallel searches):
- "frameworks [domain] [MONTH YEAR]"
- "packages [technology] standard [MONTH YEAR]"
- "Docker services [technology] [MONTH YEAR]"
- "patterns [domain] implementation [MONTH YEAR]"
- "best practices [stack] [MONTH YEAR]"
- "pitfalls [technology] avoid [MONTH YEAR]"

**Validate**: Mature solutions → Package stats → Compatibility → Maintenance

## Task Principles

**Atomic**: ONE problem, 1-4 hours, clear start/end
**Self-contained**: Objective, context, files, dependencies, tests
**Solution-aware**: Use existing tools, avoid reinventing
**Dependency-mapped**: Clear order and prerequisites

## Task Format
```md
## Task: [Action + Target]
**ID**: PROJ-XXX
**Size**: XS/S/M/L (0.5/2/4/8 hours)
**Depends**: [Task IDs]

**Objective**: [One sentence outcome]

**Context**: 
- Problem: [Why needed]
- Solution: [Approach using researched tools]
- Integration: [How fits system]

**Implementation**:
1. [Step with specific action]
2. [Use package X for Y]
3. [Configure Z]

**Files**:
- Create: [New files]
- Modify: [Existing files]
- Config: [Settings files]

**Success**:
- [ ] [Measurable criterion]
- [ ] Tests pass
- [ ] No regression

**Resources**:
- Docs: [Official docs for chosen solution]
- Example: [Reference implementation]
```

## Research-Driven Breakdown

### 1. Categorize by Technical Domain
```md
## Frontend Tasks
[Tasks using React/Vue/etc patterns from research]

## Backend Tasks  
[Tasks using Express/FastAPI/etc patterns]

## Database Tasks
[Tasks using Postgres/Mongo/etc patterns]

## DevOps Tasks
[Tasks using Docker/K8s/etc patterns]
```

### 2. Identify Reusable Components
- Which tasks use same library?
- Which share configuration?
- Which can use same Docker service?

### 3. Create Dependency Graph
```
Setup Tasks → Core Features → Integration → Testing → Deployment
    ↓              ↓             ↓           ↓          ↓
Environment    Business      Connect      Verify    Release
```

## Task Estimation

**Complexity Factors**:
- New technology: +50%
- Integration points: +25% each
- External dependencies: +30%
- First of type: +100%

**Size Guide**:
- XS (0.5h): Config change, simple fix
- S (2h): Single component, clear pattern
- M (4h): Multiple files, some integration
- L (8h): Complex feature, significant testing

## Anti-patterns
❌ Vague objectives, "Research X", Combined responsibilities, Missing context
✅ Clear outcomes, Specific solutions, Atomic scope, Complete context

## Output Structure
```md
# Task Breakdown - [Project]

## Research Findings
[Chosen solutions with rationale]

## Task Categories
### Setup & Configuration
[Environment tasks]

### Core Implementation  
[Feature tasks by priority]

### Testing & Quality
[Test tasks]

### Deployment
[Release tasks]

## Task Details
[Full task specifications]

## Dependencies
[Visual representation of task order]

## Sprint Suggestions
Sprint 1: [Task IDs] - Foundation
Sprint 2: [Task IDs] - Core features
...
```

## Handoff
Next: Plan Mode
Deliverables: Atomic tasks, dependencies, estimates, technical context