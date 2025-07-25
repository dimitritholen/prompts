# SLC Validation Module

## Core SLC Principles

### Simple
**Goal**: Remove barriers and eliminate unnecessary complexity

**Characteristics**:
- Streamlined user experience
- Intuitive interface requiring minimal learning
- Clear, focused functionality
- No redundant or confusing features
- Fast loading and responsive
- Minimal cognitive load on users

**Validation Questions**:
- Can a new user accomplish their main goal within 5 minutes?
- Can the core functionality be explained in one sentence?
- Are there any steps that could be eliminated?
- Would removing this feature make the product simpler without losing core value?
- Does every element serve a clear purpose?

### Lovable
**Goal**: Create genuine user delight and emotional connection

**Characteristics**:
- Solves a real pain point effectively
- Delights users beyond basic functionality
- Creates positive emotional response
- Users recommend it to others
- High retention and engagement
- Users feel the product "gets them"

**Validation Questions**:
- Do users actively choose this over alternatives?
- Would users be genuinely disappointed if this feature disappeared?
- Does this create a "wow" moment or solve a frustrating problem?
- Do users talk positively about this experience?
- Does this make users' lives meaningfully better?

### Complete
**Goal**: Fully deliver on the core promise without gaps

**Characteristics**:
- Accomplishes the intended job thoroughly
- No major functionality gaps in core workflow
- Users can complete their primary task end-to-end
- Reliable and consistent performance
- Meets or exceeds user expectations
- Feels finished, not beta-quality

**Validation Questions**:
- Can users complete their entire workflow without external tools?
- Are there any broken or incomplete user journeys?
- Does this fulfill the promise made in marketing/onboarding?
- Would users consider this a "real" product vs. a prototype?
- Are all critical edge cases handled?

## SLC Scoring Framework

Rate each aspect from 1-5:

### Simple Score (1-5)
- **5**: Incredibly intuitive, zero learning curve
- **4**: Very easy to use, minimal explanation needed
- **3**: Reasonably simple, some guidance helpful
- **2**: Somewhat complex, requires documentation
- **1**: Complex, confusing, high learning curve

### Lovable Score (1-5)
- **5**: Users are evangelists, love the experience
- **4**: Users are very satisfied, would recommend
- **3**: Users are satisfied, find it useful
- **2**: Users tolerate it, meets basic needs
- **1**: Users frustrated, only use because they have to

### Complete Score (1-5)
- **5**: Fully solves the problem, exceeds expectations
- **4**: Effectively solves the problem, meets expectations
- **3**: Solves the problem with minor gaps
- **2**: Partially solves the problem, notable gaps
- **1**: Major gaps, users need workarounds

**SLC Threshold**: All three scores must be 3+ for a feature to qualify

## Feature Validation Checklist

Before adding any feature, ensure it passes ALL checks:

### SLC Compatibility Check
- [ ] **Simple**: Does this maintain or improve simplicity?
- [ ] **Lovable**: Will users genuinely love this addition?
- [ ] **Complete**: Does this help complete the core promise?
- [ ] **No Contradictions**: Does this align with all three SLC principles?

### User Evidence Check
- [ ] **Real User Need**: Based on actual user research/feedback
- [ ] **Problem Validation**: Solves a documented user problem
- [ ] **Value Proposition**: Clear benefit users would pay/effort for
- [ ] **Usage Intent**: Will be used by >50% of target users

### Implementation Check
- [ ] **Core Workflow**: Essential for primary user journey
- [ ] **Cannot Wait**: Needed now, not "nice to have later"
- [ ] **No Alternatives**: Cannot be solved with existing features
- [ ] **Maintenance Worthy**: Worth ongoing support and iteration

## SLC Validation Output Template

```markdown
### SLC Validation Results

#### Feature: [Feature Name]

**Simple Score**: [1-5] - [Justification]
**Lovable Score**: [1-5] - [Justification]
**Complete Score**: [1-5] - [Justification]

**Overall**: [PASS/FAIL] - [All scores ≥3 = PASS]

#### Recommendations:
- [Specific improvements needed]
- [Elements to remove/simplify]
- [Gaps to fill]
```

## Warning Signs

### Simple Violations 🚨
- Users need training to use basic features
- Feature requires detailed documentation
- Multiple ways to accomplish the same task
- Interface feels cluttered or overwhelming
- New users take >30 minutes to see value

### Lovable Violations 🚨
- Low user engagement or retention
- Features go unused by majority of users
- Users complain about experience quality
- High churn during trial/onboarding
- Users stick with inferior alternatives

### Complete Violations 🚨
- Users need external tools for core workflow
- Frequent feature requests for "basic" functionality
- High support ticket volume for functionality gaps
- Users create workarounds for missing pieces
- Core use cases remain unsolved

## Integration with Modes

### During Brainstorm
- Validate initial idea against SLC
- Score concept viability
- Identify potential violations early

### During PRD
- Apply SLC to each feature
- Prioritize based on SLC scores
- Remove features that fail validation

### During Architect
- Choose technologies that support simplicity
- Design for completeness
- Optimize for user delight

### During Tasks
- Ensure each task contributes to SLC
- Flag tasks that might compromise principles
- Prioritize SLC-enhancing tasks