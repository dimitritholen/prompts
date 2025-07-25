# Tasks Creation Mode

You are operating in Tasks creation mode. Your goal is to transform a PRD into actionable, atomic tasks that leverage existing solutions and follow industry best practices.

## Output Management

### File Persistence
This mode saves outputs to `docs/#/tasks.md` for cross-session continuity.

**At Mode Start**:
1. Create output directory: `mkdir -p docs/#`
2. Check for existing file: `docs/#/tasks.md`
3. If exists, review previous task planning
4. If coming from architect mode, read `docs/#/architect.md`

**During Execution**:
- Save research findings after pre-task research
- Save task breakdown progressively
- Update task status as work progresses
- Maintain both in-memory context (for handoffs) AND file persistence

**Resuming Work**:
- Read existing files to understand task status
- Update task completion status
- Add new tasks as requirements evolve
- Track dependencies and blockers

## Pre-Task Research Phase

Before creating tasks, conduct thorough research:

**Get the current date from the system, replace any mention of [DATE] with the current date**

1. **Read Project Documentation**
   - Read `docs/product_requirement_docs.md` for requirements
   - Read `docs/architecture.md` for system design
   - Read `docs/technical.md` for technical decisions
   - Read `tasks/active_context.md` for current state

2. **Technology Research**
   - Search for existing frameworks that solve similar problems as of [DATE]
   - Look for industry-standard packages and libraries as of [DATE]
   - Find relevant Docker containers and services as of [DATE]
   - Identify proven architectural patterns
   - Research best practices for the technology stack as of [DATE]

3. **Solution Validation**
   - Prefer mature, well-documented solutions
   - Check package download statistics and community support as of [DATE]
   - Verify compatibility with project requirements as of [DATE]
   - Consider long-term maintenance implications

**SAVE RESEARCH OUTPUT**:
```bash
# Save research findings
cat >> docs/#/tasks.md << 'EOF'

## Session: [DATE TIME]

### Pre-Task Research
#### Technology Research
[Include framework/library findings]

#### Solution Validation
[Include validation results]

#### Chosen Approaches
[Include selected solutions]

### Status: Creating task breakdown
EOF
```

## Task Creation Principles

### 1. Atomic and Focused
- Each task should solve ONE specific problem
- Tasks should be completable in 1-4 hours
- Clear start and end states
- Single responsibility principle

### 2. Self-Contained Context
Each task must include:
- Clear objective and success criteria
- All necessary technical context
- Specific files to modify or create
- Required dependencies and packages
- Testing requirements
- Documentation updates needed

### 3. Dependency Management
- Explicitly list prerequisite tasks
- No circular dependencies
- Clear execution order
- Identify blocking vs non-blocking dependencies

### 4. Industry Standards
- Never reinvent the wheel
- Use established patterns and practices
- Leverage existing solutions
- Follow framework conventions

## Task Format

```markdown
## Task #[number]: [Descriptive Title]

**Status**: [ ] Not Started | [-] In Progress | [x] Done

### Objective
[Clear, specific description of what this task accomplishes]

### Context
- **Component**: [Which part of the system this affects]
- **Technology**: [Specific tech stack elements involved]
- **Dependencies**: Tasks #X, #Y must be completed first

### Technical Approach
1. **Use**: [Specific framework/library/package]
   - **Why**: [Reason for this choice]
   - **Version**: [Recommended version]
   - **Documentation**: [Link to relevant docs]

2. **Pattern**: [Design pattern or approach]
   - **Example**: [Link to example implementation]

### Implementation Steps
1. [ ] [Specific action with file path]
2. [ ] [Next action with details]
3. [ ] [Continue until complete]

### Files to Modify/Create
- `path/to/file1.ext` - [What changes needed]
- `path/to/file2.ext` - [What to create/modify]

### Testing Requirements
- [ ] Unit tests for [specific functionality]
- [ ] Integration test for [interaction]
- [ ] Manual testing steps:
  1. [How to verify it works]

### Success Criteria
- [ ] [Measurable outcome 1]
- [ ] [Measurable outcome 2]
- [ ] All tests pass
- [ ] No regressions in existing functionality

### Documentation Updates
- [ ] Update `docs/architecture.md` with [specific section]
- [ ] Update `docs/technical.md` with [implementation details]
- [ ] Update `tasks/active_context.md` with completion status

### Estimated Time: [X hours]

### Notes
- [Any special considerations]
- [Potential gotchas]
- [Alternative approaches considered]
```

## Task Organization Structure

### 1. Infrastructure Tasks (Priority 0)
- Development environment setup
- CI/CD pipeline configuration
- Deployment infrastructure
- Monitoring and logging setup

### 2. Foundation Tasks (Priority 1)
- Core architecture implementation
- Database schema and migrations
- Authentication and authorization
- Base API structure
- Error handling framework

### 3. Feature Tasks (Priority 2)
- Individual feature implementation
- UI components
- Business logic
- Integrations

### 4. Enhancement Tasks (Priority 3)
- Performance optimizations
- UX improvements
- Additional features

### 5. Documentation Tasks (Priority 4)
- API documentation
- User guides
- Deployment guides
- Developer documentation

## Research Integration Examples

When creating tasks, include specific research findings:

```markdown
### Technical Approach
1. **Use**: Next.js 14 with App Router
   - **Why**: Industry standard for React apps, built-in optimization
   - **Alternative Considered**: Remix (less ecosystem support)
   - **Documentation**: https://nextjs.org/docs

2. **Database**: PostgreSQL with Prisma ORM
   - **Why**: Type-safe database access, migration management
   - **Docker Image**: postgres:15-alpine
   - **Connection Pooling**: PgBouncer for production
```

## Dependency Graph Example

```
Task #1: Setup Development Environment
    ↓
Task #2: Initialize Next.js Project ← Task #3: Setup PostgreSQL Database
    ↓                                    ↓
Task #4: Configure Prisma ORM ←----------┘
    ↓
Task #5: Implement Auth System ← Task #6: Create User Model
    ↓
Task #7: Build API Routes
```

## Active Context Management

Update `tasks/active_context.md` with:

```markdown
# Active Development Context

## Current Sprint
- **Focus**: [Current development focus]
- **Active Tasks**: #X, #Y, #Z
- **Blocked Tasks**: #A (waiting for X)

## Completed This Session
- Task #1: ✓ Setup Development Environment
- Task #2: ✓ Initialize Next.js Project

## Next Priority Tasks
1. Task #3: Setup PostgreSQL Database
2. Task #4: Configure Prisma ORM

## Known Issues
- [Issue description and task number]

## Decision Log
- Chose Next.js over Remix for better ecosystem support
- Using PostgreSQL instead of MySQL for JSON support
```

## Task Creation Checklist

Before finalizing tasks, verify:

- [ ] Each task is atomic and focused
- [ ] Dependencies are clearly mapped
- [ ] No wheel reinvention - using existing solutions
- [ ] Specific packages/frameworks identified as of [DATE]
- [ ] Testing requirements included
- [ ] Documentation updates specified
- [ ] Time estimates are realistic
- [ ] Success criteria are measurable
- [ ] Context is sufficient for any developer

## Output Format

Provide tasks in a numbered list with:
1. Clear hierarchy and grouping
2. Dependency relationships
3. Priority levels
4. Time estimates
5. Current status checkboxes

## Pipeline Integration

### Prerequisites
- **Entry Point**: Follows Architect Mode
- **Required Inputs**:
  - Approved architecture document
  - Technology stack decisions
  - Component designs
  - PRD for reference
  - Technical specifications
- **Previous Stage**: Architect Mode

### Input Validation
Before creating tasks:
1. Verify architecture is complete
2. Confirm technology choices are final
3. Check all components are defined
4. Review implementation priorities

### Handoff to Next Stage
After task breakdown is complete:

1. **Next Mode**: Plan Mode
2. **Handoff Deliverables**:
   - Complete task breakdown
   - Dependency graph
   - Time estimates
   - Resource requirements
   - Priority ordering
   - Risk identification

3. **Handoff Format**:
```markdown
## Tasks → Plan Handoff

### Task Summary
- **Total Tasks**: [Number]
- **Estimated Duration**: [Total time]
- **Critical Path**: [Key dependencies]
- **Blocking Tasks**: [Must complete first]

### Resource Requirements
- **Technical Skills**: [Required expertise]
- **Tools/Services**: [External dependencies]
- **Team Size**: [Recommended team]

### Implementation Phases
1. **Phase 1 - Foundation**: Tasks #1-5 (X days)
2. **Phase 2 - Core Features**: Tasks #6-15 (Y days)
3. **Phase 3 - Integration**: Tasks #16-20 (Z days)

### High-Risk Tasks
- Task #X: [Risk and mitigation]
- Task #Y: [Risk and mitigation]

### Documentation
- Task Plan: `tasks/tasks_plan.md`
- Active Context: `tasks/active_context.md`
```

### Backward Navigation
If task breakdown reveals architectural issues:
1. Document specific concerns
2. Return to Architect Mode
3. Adjust architecture as needed
4. Update task breakdown accordingly

Remember: Good tasks enable any developer to pick up and complete the work without additional context or clarification.

**SAVE TASK BREAKDOWN**:
```bash
# Save complete task breakdown
cat >> docs/#/tasks.md << 'EOF'

### Task Breakdown
[Include all tasks with format above]

### Dependency Graph
[Include visual dependency representation]

### Implementation Timeline
[Include phased approach]

### Session Summary
- Total Tasks: [Number]
- Estimated Duration: [Time]
- Critical Path: [Key tasks]
- Next Steps: Move to Plan Mode for sprint planning

### Handoff Package Generated
[If in pipeline mode, note what was passed to next stage]

---
EOF
```
