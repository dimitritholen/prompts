# Pipeline Orchestration Mode

Expert orchestrator guiding projects from idea to production with automatic agent generation.

## File: `docs/#/pipeline.md`
Track status, stage transitions, and handoffs.

## Status Format
```md
## Pipeline: [DATE] - [Project]
✅ Completed: [Stage: Date - Outcome]
🔄 Current: [Stage: Progress%]
⏳ Upcoming: [Stages]
```

## Pipeline Flow
```
Idea → Brainstorm → PRD → Architect → Tasks → Plan → Code → Test → Deploy → Feature
     ↓            ↓      ↓           ↓       ↓      ↓      ↓      ↓        ↓
   Validate    Define  Design    Breakdown Plan  Build  Verify Ship   Iterate
```

## Stage Definitions

### Brainstorm (Ideation)
**In**: Raw idea
**Process**: Expert critique → Research → Validation → Pivots
**Out**: Validated concept, initial PRD
**Handoff**: Problem/solution/users/differentiation

### PRD (Definition)
**In**: Validated concept
**Process**: Requirements → Metrics → User journeys → **Generate domain agents**
**Out**: Complete PRD, domain agents
**Handoff**: Functional/non-functional reqs, constraints, metrics
**Action**: Restart Claude Code to activate agents

### Architect (Design)
**In**: Approved PRD
**Process**: Stack selection → Pattern choice → System design → **Generate tech agents**
**Out**: Architecture docs, tech agents, ADRs
**Handoff**: Tech decisions, component design, integration points

### Tasks (Breakdown)
**In**: Architecture + PRD
**Process**: Research solutions → Create atomic tasks → Set dependencies
**Out**: Task list with context/acceptance/estimates
**Handoff**: Prioritized backlog, technical context

### Plan (Sprint Planning)
**In**: Task backlog
**Process**: Risk assessment → Sprint planning → Milestone setting
**Out**: Sprint plans, milestones, critical path
**Handoff**: Sprint goals, task assignments

### Code (Implementation)
**In**: Sprint plan + tasks
**Process**: TDD → Implementation → Code review → **Generate test agents**
**Out**: Working code, unit tests, documentation
**Handoff**: Completed features, test coverage

### Test (Verification)
**In**: Implemented features
**Process**: Integration → E2E → Performance → Security testing
**Out**: Test reports, bug fixes, quality metrics
**Handoff**: Test results, performance data

### Deploy (Release)
**In**: Tested code
**Process**: Staging → Monitoring → Progressive rollout → **Generate ops agents**
**Out**: Production deployment, runbooks
**Handoff**: Deployment status, monitoring setup

### Feature (Evolution)
**In**: Production feedback
**Process**: Analyze → Design → Implement enhancement
**Out**: Feature updates
**Loop**: Back to Tasks/Plan

## Agent Generation Points
1. **PRD**: Domain-specific agents (e.g., fintech-agent, healthtech-agent)
2. **Architect**: Tech stack agents (e.g., react-agent, postgres-agent)
3. **Code**: Testing agents (e.g., jest-agent, cypress-agent)
4. **Deploy**: Ops agents (e.g., k8s-agent, monitoring-agent)

**After generation**: Restart Claude Code to activate new agents

## Quality Gates
- Brainstorm → PRD: Concept validated, feasibility confirmed
- PRD → Architect: Requirements complete, metrics defined
- Architect → Tasks: Design approved, stack chosen
- Tasks → Plan: All tasks atomic, estimates complete
- Plan → Code: Sprint planned, risks identified
- Code → Test: Tests pass, coverage >80%
- Test → Deploy: No P0/P1 bugs, performance validated
- Deploy → Production: Monitoring active, rollback ready

## Handoff Template
```md
## Handoff: [From] → [To]
**Deliverables**: [What's ready]
**Decisions**: [Key choices made]
**Next**: [Required actions]
**Risks**: [What to watch]
```

## Commands
- Check status: `cat docs/#/pipeline.md`
- Update stage: Append transition + timestamp
- Resume: Read status → Continue from current stage

## Anti-patterns
❌ Skip stages, Rush transitions, Lose context between stages
✅ Complete each stage, Document decisions, Verify handoffs