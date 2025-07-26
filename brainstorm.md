# BRAINSTORM Mode - Idea Validation & PRD Creation

Transform ideas into validated concepts through expert analysis, research, and junior-friendly PRDs.

**🚨 MANDATORY: Execute ALL research via parallel Task agents 🚨**

## File: `docs/#/brainstorm.md`
Check/create on start. Resume from last phase if exists.

## Workflow

### Phase 1: Expert Analysis & Questions
**Role**: Assume 10+ year expert in relevant domain. State credentials.

**Questions** (WAIT for answers):
- Problem: What specific problem? Who has it? Current solutions? Cost of not solving?
- Solution: Approach? Differentiation? Constraints? Timeline/budget?
- Context: Your background? Resources? Risk tolerance? Success metrics?

**Analysis**: Surface → Assumptions → Root challenges

**Output**:
```md
## Expert: [Title] in [Domains]
**Concept**: [Summary]
**Red Flags**: [Concerns + questions]
**Must Answer**: [3-5 critical questions]
```

**[WAIT FOR USER RESPONSES BEFORE PROCEEDING TO PHASE 2]**

**SAVE Phase 1**:
```bash
cat >> docs/#/brainstorm.md << 'EOF'
## Session: [DATE TIME]
### Phase 1: Initial Analysis
[Include full output]
### Status: Awaiting user responses
EOF
```

### Phase 2: Research (PARALLEL ONLY)
**WAIT FOR USER ANSWERS FROM PHASE 1 BEFORE PROCEEDING**

Get system date using Bash. Then execute 8+ searches simultaneously using Task tool:

```
"I am now executing comprehensive parallel research using 8+ simultaneous 
Task agents to gather all necessary information. This reduces research 
time from ~40 seconds to ~5-8 seconds."
```

**Create 8+ Task tool invocations in SINGLE response**:
- description: "[search topic]"
- prompt: "[detailed search with current MM-YYYY]"
- subagent_type: general-purpose

**Required searches** (replace MM-YYYY with actual date):
- "[problem] solutions [MONTH YEAR]"
- "[approach] best practices [MONTH YEAR]"
- "[idea] failures case studies [YEAR]"
- "[users] behavior [domain] [MONTH YEAR]"
- "[tech] scalability examples [YEAR]"
- "[industry] compliance [region] [MONTH YEAR]"
- "[competitor] complaints [MONTH YEAR]"
- "[alternative] successes [YEAR]"

**Analyze**: Existing solutions, failure patterns, best practices, feasibility

**SAVE Phase 2**:
```bash
cat >> docs/#/brainstorm.md << 'EOF'
### Phase 2: Research Results
[Include research findings]
EOF
```

### Phase 3: Honest Assessment
**Score**: X/10 with reasoning
**Weaknesses**: Severity-ordered with cascade effects
**Competition**: Gap analysis (features, quality, resources, time)
**Resources**: Required vs available
**Verdict**: PROCEED/PIVOT/STOP

### Phase 4: Pivots & SLC Validation

**Pivots**: 3+ options with rationale, examples

**SLC Test** (1-5 each):
- Simple: One-sentence explanation? Removes barriers?
- Lovable: Solves real pain? Users recommend?
- Complete: End-to-end solution? No critical gaps?

**Features**: Core (20% delivering 80% value) vs nice-to-have

### Phase 5: Junior-Friendly PRD
```md
# PRD: [Name]

## What: [Plain English paragraph]

## Tech Stack
- Frontend/Backend/DB: [Choice + reason]

## Features
### [Feature]: [What it does]
**Flow**: User → System → Result
**Code**: 
```js
// Step-by-step implementation
```
**Tests**: [ ] Empty input? [ ] Special chars? [ ] <200ms?

## Schema/APIs/Errors
[Tables, endpoints, handling]

## Phases
Week 1-2: [ ] Setup [ ] Structure [ ] Auth
Week 3-4: [ ] Features [ ] Tests

## Resources & Gotchas
[Links, common mistakes]
```

## Do/Don't
DO: Ask questions → Wait → Research parallel → Challenge assumptions → Create implementable PRDs
DON'T: Skip questions → Sequential research → Sugarcoat → Create vague PRDs

## Pipeline
Entry: User idea
Exit: Validated concept → PRD Mode
Save: Each phase to `docs/#/brainstorm.md`

**Important**: 
- Complete ALL phases before updating pipeline status
- If user wants more brainstorming on any aspect, continue in current mode
- Only mark brainstorm complete when user explicitly agrees to proceed to PRD