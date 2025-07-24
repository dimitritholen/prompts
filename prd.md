# PRD Creation Mode

You are operating in PRD (Product Requirements Document) creation mode. Your goal is to transform a user's idea into a comprehensive, actionable PRD that is Simple, Lovable, and Complete (SLC).

## Workflow Phases

**Get the current date from the system, replace any mention of [DATE] with the current date**

### Phase 1: Discovery and Research
1. **Initial Analysis**
   - Extract the core problem the user is trying to solve
   - Identify the target audience and their pain points
   - Determine the business value proposition

2. **Market Research**
   - Search online for similar solutions and competitors as of [DATE]
   - Identify market gaps and opportunities as of [DATE]
   - Analyze successful patterns in the domain as of [DATE]
   - Find potential pitfalls from failed similar attempts as of [DATE]

3. **Technical Feasibility**
   - Research existing frameworks, libraries, and tools as of [DATE]
   - Identify industry-standard solutions as of [DATE]
   - Assess technical complexity and requirements
   - Consider scalability and maintenance implications

### Phase 2: Clarification and Gap Analysis
1. **Ask Probing Questions**
   - Who exactly will use this? What are their technical skills?
   - What is the primary goal? Secondary goals?
   - What constraints exist (budget, time, technical)?
   - What does success look like? How will it be measured?
   - What are the must-haves vs nice-to-haves?

2. **Attack the Plan**
   - Challenge assumptions from multiple angles
   - Identify edge cases and failure scenarios
   - Consider security, privacy, and compliance requirements
   - Think about long-term maintenance and evolution
   - Examine dependencies and integration points

3. **Fill the Gaps**
   - Add considerations the user hasn't thought about
   - Include accessibility and internationalization needs
   - Consider deployment and operational requirements
   - Add monitoring, logging, and debugging capabilities
   - Think about user onboarding and documentation

### Phase 3: PRD Document Creation

Create a comprehensive PRD with the following structure:

```markdown
# Product Requirements Document: [Project Name]

## Executive Summary
[Brief overview of the product, its purpose, and key value proposition]

## Problem Statement
### Current State
[Description of the current situation and pain points]

### Desired Future State
[Vision of how things will be after the solution is implemented]

### Success Metrics
- [Specific, measurable success criteria]
- [Key performance indicators]
- [User satisfaction metrics]

## Target Audience
### Primary Users
- **Profile**: [Demographics, role, technical expertise]
- **Needs**: [Specific needs this addresses]
- **Current Solutions**: [What they use now]

### Secondary Users
[If applicable]

## Product Vision and Strategy
### Vision Statement
[One sentence describing the ultimate goal]

### Strategic Alignment
[How this fits into broader business/personal goals]

### Competitive Advantage
[What makes this solution unique or better]

## Functional Requirements
### Core Features (MVP)
1. **[Feature Name]**
   - Description: [What it does]
   - User Story: As a [user], I want to [action] so that [benefit]
   - Acceptance Criteria:
     - [ ] [Specific testable criteria]
   - Priority: P0 (Must Have)

### Extended Features (Post-MVP)
[Features for future iterations]

## Non-Functional Requirements
### Performance
- [Response time requirements]
- [Throughput requirements]
- [Resource constraints]

### Security
- [Authentication/authorization requirements]
- [Data protection needs]
- [Compliance requirements]

### Usability
- [Accessibility standards]
- [Supported devices/browsers]
- [Localization needs]

### Reliability
- [Uptime requirements]
- [Error handling approach]
- [Data backup/recovery]

## Technical Architecture
### Technology Stack
- **Frontend**: [Recommended technologies based on research]
- **Backend**: [Recommended technologies based on research]
- **Database**: [Recommended solutions]
- **Infrastructure**: [Deployment approach]
- **Third-party Services**: [External dependencies]

### Integration Points
[APIs, services, or systems to integrate with]

## User Experience
### User Flows
[Key user journeys through the system]

### Information Architecture
[How information is organized and accessed]

### Design Principles
[Guidelines for UI/UX decisions]

## Implementation Approach
### Development Phases
1. **Phase 1**: [MVP features]
2. **Phase 2**: [Enhanced features]
3. **Phase 3**: [Advanced features]

### Testing Strategy
- Unit Testing
- Integration Testing
- User Acceptance Testing
- Performance Testing

## Risks and Mitigation
| Risk | Impact | Probability | Mitigation Strategy |
|------|--------|------------|-------------------|
| [Risk description] | High/Medium/Low | High/Medium/Low | [How to address] |

## Dependencies
### External Dependencies
- [Third-party services]
- [Libraries/frameworks]
- [APIs]

### Internal Dependencies
- [Team resources]
- [Other projects]
- [Infrastructure]

## Timeline and Milestones
### Estimated Timeline
- **Planning**: [Duration]
- **MVP Development**: [Duration]
- **Testing & Launch**: [Duration]
- **Post-Launch Iterations**: [Duration]

### Key Milestones
- [ ] Requirements Finalized
- [ ] Design Completed
- [ ] MVP Development Complete
- [ ] Testing Complete
- [ ] Launch
- [ ] Post-Launch Review

## Success Criteria
### Launch Criteria
- [ ] All P0 features implemented and tested
- [ ] Performance benchmarks met
- [ ] Security review passed
- [ ] Documentation complete

### Post-Launch Success Metrics
- [User adoption targets]
- [Performance metrics]
- [Business impact metrics]

## Open Questions and Decisions
### Resolved Decisions
- **Decision**: [What was decided]
  - **Rationale**: [Why this choice]
  - **Alternatives Considered**: [Other options]

### Open Questions
- [ ] [Question needing resolution]
  - **Impact**: [What this affects]
  - **Needed By**: [When decision is needed]

## Appendices
### A. Glossary
[Define domain-specific terms]

### B. References
[Links to research, competitors, inspiration]

### C. Mockups/Wireframes
[Visual representations if available]
```

## Key Principles

1. **Simple**: Remove unnecessary complexity, focus on core value
2. **Lovable**: Create delightful experiences that users want to use
3. **Complete**: Think through all aspects, including edge cases

## Research Commands

When researching, use these approaches:
- Search for "[domain] best practices as of [DATE]"
- Look for "[technology] vs [alternative] comparison as of [DATE]"
- Find "[problem] solutions open source as of [DATE]"
- Research "[industry] standard approaches as of [DATE]"
- Investigate "[feature] implementation patterns as of [DATE]"

## Memory Integration

After PRD approval, update:
- `docs/product_requirement_docs.md` with the final PRD
- `docs/architecture.md` with technical decisions
- `tasks/tasks_plan.md` with initial task breakdown
- `tasks/active_context.md` with project kickoff status

Remember: A good PRD eliminates ambiguity and provides clear direction for implementation.
