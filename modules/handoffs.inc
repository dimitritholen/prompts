# Handoffs Module - Stage Transitions

## Core Handoff Principles

1. **Clear Documentation**: Each handoff includes what was done and what's next
2. **Context Preservation**: Key decisions and rationale are passed forward
3. **Quality Gates**: Exit criteria must be met before proceeding
4. **Actionable Next Steps**: Clear instructions for the next mode

## Standard Handoff Template

```markdown
## Handoff: [Previous Mode] → [Next Mode]

### Completed Deliverables
- **[Deliverable 1]**: [Brief description]
- **[Deliverable 2]**: [Brief description]
- **[Generated Agents]**: [List if applicable]

### Key Decisions Made
- [Decision 1]: [Rationale]
- [Decision 2]: [Rationale]
- [Important constraints or limitations]

### Critical Information for Next Stage
- [Key insight 1]
- [Key insight 2]
- [Dependencies or requirements]

### Next Steps
1. [Specific action 1]
2. [Specific action 2]
3. [Expected outcome]

### Documentation
- [Mode] Output: `docs/#/[mode].md`
- Supporting Docs: [List any additional files]
- Agents Created: `.claude/agents/[agent-names]`

### ⚠️ Important Notes
[Any warnings, blockers, or special considerations]
```

## Mode-Specific Handoffs

### Brainstorm → PRD
```markdown
## Handoff: Brainstorm → PRD

### Validated Concept
- **Problem**: [Clearly defined problem]
- **Solution**: [Proposed approach]
- **Target Users**: [Identified audience]
- **Differentiation**: [Unique value]

### Research Insights
- **Market Analysis**: [Key findings]
- **Competitor Landscape**: [Main players]
- **Technical Feasibility**: [Validation]

### Key Decisions
- [Major pivots or changes made]
- [Assumptions validated]
- [Risks identified]

### Next Steps
- Formalize requirements in PRD
- Define success metrics
- Create detailed specifications
- Generate domain-specific agents
```

### PRD → Architect
```markdown
## Handoff: PRD → Architect

### Requirements Summary
- **Functional Requirements**: [Key features]
- **Non-Functional Requirements**: [Performance, security, etc.]
- **Constraints**: [Technical, business, time]
- **Success Metrics**: [Measurable goals]

### Domain Agents Generated
- `product-manager`: Product vision keeper
- `[domain]-expert`: Domain knowledge
- `ux-designer`: User experience

### Critical Decisions Needed
- Technology stack selection
- Architecture pattern choice
- Scalability approach
- Security architecture

### Documentation
- PRD: `docs/#/prd.md`
- Domain Agents: `.claude/agents/`
```

### Architect → Tasks
```markdown
## Handoff: Architect → Tasks

### Architecture Decisions
- **Pattern**: [Microservices/Monolith/etc.]
- **Stack**: [Technologies chosen]
- **Infrastructure**: [Cloud/deployment approach]
- **Key Components**: [Major system parts]

### Tech Stack Agents Generated
- Frontend: `[framework]-developer`
- Backend: `[language]-backend-developer`
- Database: `[database]-specialist`
- DevOps: `devops-engineer`

### Implementation Considerations
- [Technical challenges identified]
- [Integration points defined]
- [Performance requirements]

### Documentation
- Architecture: `docs/#/architect.md`
- Tech Agents: `.claude/agents/`
```

### Tasks → Plan
```markdown
## Handoff: Tasks → Plan

### Task Summary
- **Total Tasks**: [Number]
- **Critical Path**: [Key dependencies]
- **Estimated Timeline**: [Duration]
- **Resource Needs**: [Team/tools required]

### Quality Agents Generated
- `code-reviewer`: Standards enforcement
- `test-engineer`: Quality assurance
- `security-engineer`: Security auditing

### Priority Order
1. [Foundation tasks]
2. [Core features]
3. [Enhancement tasks]

### Documentation
- Task Breakdown: `docs/#/tasks.md`
- Quality Agents: `.claude/agents/`
```

### Plan → Code
```markdown
## Handoff: Plan → Code

### Implementation Ready
- **Approach**: [Detailed strategy]
- **First Sprint**: [Initial tasks]
- **Test Strategy**: [Testing approach]
- **Success Criteria**: [Definition of done]

### All Agents Active
- Domain: [Count] agents
- Tech Stack: [Count] agents
- Quality: [Count] agents

### Key Risks
- [Risk 1]: [Mitigation]
- [Risk 2]: [Mitigation]

### Begin Coding
- Start with: [First task reference]
- Testing approach: [TDD/other]
- Use relevant agents for expertise
```

### Code/Test → Deploy
```markdown
## Handoff: Code/Test → Deploy

### Development Complete
- **Features Implemented**: [List]
- **Test Coverage**: [Percentage]
- **Performance Metrics**: [Results]
- **Known Issues**: [If any]

### Deployment Readiness
- [ ] All tests passing
- [ ] Documentation complete
- [ ] Security scan clean
- [ ] Performance acceptable

### Deployment Requirements
- Infrastructure needs
- Environment configurations
- Monitoring setup
- Rollback plan

### Next: Production Deployment
```

## Quality Gate Checklist

Use before each handoff:

```markdown
## Quality Gate: [Mode Name]

### Documentation
- [ ] Mode output saved to `docs/#/[mode].md`
- [ ] All decisions documented with rationale
- [ ] Key findings summarized

### Deliverables
- [ ] Primary deliverable complete
- [ ] Meets quality standards
- [ ] Reviewed for completeness

### Readiness
- [ ] Exit criteria met
- [ ] No blocking issues
- [ ] Next mode prerequisites available

### Handoff
- [ ] Handoff document prepared
- [ ] Context preserved
- [ ] Next steps clear

**Gate Status**: [PASS/FAIL]
```

## Pipeline Status Update

After each handoff, update pipeline status:

```bash
# Update stage status
update_stage_status() {
    local stage="$1"
    local status="$2"
    local timestamp=$(date +"%Y-%m-%d %H:%M:%S")
    
    # Update pipeline.md with new status
    # Mark previous stage complete
    # Mark next stage as current
    # Add handoff notes
}
```

## Emergency Handoffs

For interrupted or problematic transitions:

```markdown
## Emergency Handoff: [Mode]

### Interruption Point
- **Stage**: [Where stopped]
- **Reason**: [Why interrupted]
- **Progress**: [What was completed]

### Preserved Work
- [List of saved items]
- [Partial deliverables]

### Recovery Steps
1. [How to resume]
2. [What to verify]
3. [How to proceed]

### Critical Context
[Essential information to not lose]
```