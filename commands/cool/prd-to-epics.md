Turn requirements into actionable sprints with features using a prompt template. Each feature is a single and complete prompt that will develop this feature systematically.

---
$ARGUMENTS
---

## Expected AI Output Format

Create multiple SPRINT documents in ./tasks/SPRINT[NNN]_[SPRINT_SLUG].md

- Analyze step by step the content of the documentation. Think hardest.
- IF the PRD or documentation lacks details on the optimal tech stack then:
  - Use Tree of Thought and Chain of Thought to think of 3 separate versions of tech stacks, pick the best 
  - Use tech stack that fits a solo developer with a $100 budget
  - Review your choice of tech stack using Chain of Thought. Think ultrahard. 
  - Add the tech stack installation to SPRINT000_INFRA.md
- Sprints need to be in the correct order of development


- **Sprint [NNN]**  
  - Feature [FEATURE_NAME] (this list contains between 3 and 5 features, based on sprint complexity)
  - ...

### Feature: [Feature Name]  
**Summary:** [1–2 sentence summary of the feature]  
**Dependencies:** [List dependencies or “None”]  
**Progress:** TODO|DOING|DONE

**Development Cycle Prompt:**  

<prompt>
You are a senior [LANGUAGE] software engineer. Your task is to implement a complex software feature in a systematic, bug-free, and well-tested way. 
Follow this process strictly, step by step, without skipping or merging phases. Always explain your reasoning before producing code.  

Feature: "[Feature Name]"

## Workflow

### Step 1: Requirements Analysis
- Summarize the feature in your own words.  
- Use Chain of Thought to think about the solution.
- Think hardest. List functional and non-functional requirements.  
- Ask clarifying questions if anything is unclear.  
- Do not proceed until requirements are explicit and validated.  

### Step 2: Architecture & Design
- Think hardest. Break down the feature into logical modules/components.  
- Think hardest. Define clear interfaces, dependencies, and data flows.  
- Think hardest. Highlight design trade-offs (performance, maintainability, scalability).  
- Think hardest. Avoid unnecessary mocks — prefer real testable components (e.g. in-memory DBs).  

### Step 3: Test Planning
- Use Chain of Thought to think about the tests
- Think hardest. Write *acceptance tests* in Gherkin-style (Given/When/Then).  
- **CRITICAL** Think hardest. Design *property-based tests* for variable/random input.  
- **CRITICAL** Think hardest. Add *integration tests* (minimal mocking, realistic data).  
- **CRITICAL** Think hardest. Cover error handling and edge cases.  
- Think hardest. Show how test coverage will be measured.  

### Step 4: Iterative Implementation
- **ALWAYS CHECK FOR A SUITABLE SUB-AGENT TO USE FOR IMPLEMENTATION**
- Local agents (.claude/agents) have priority over GLOBAL agents (~/.claude/agents)
- Implement the feature module by module.  
- For each module:  
  1. Restate requirements for that module.  
  2. Write tests first.  
  3. Implement the code.  
  4. Run the tests and report results.  
- Ensure each iteration leaves the system in a working state.  

### Step 5: Self-Review & Quality Checks
- Perform a static analysis (linting, type safety, code smells).  
- Identify duplication, poor naming, or unclear logic.  
- Report any bugs or inconsistencies.  
- Improve code and tests until they reach senior-level quality.  

### Step 6: Final Validation
- Show that all tests pass successfully.  
- Report coverage metrics and demonstrate edge-case handling.  
- Confirm that the implementation fully satisfies all requirements.  

## Rules **IMPORTANT**
- Do NOT jump directly to final implementation.  
- Think hardest. Step by step. Think aloud about design decisions before coding.  
- **CRITICAL** Tests must be meaningful — no trivial asserts, no fully hardcoded tests.  
- Deliver iteratively and transparently.  
- If requirements change during clarification, update all downstream steps accordingly.  

Begin now with **Step 1: Requirements Analysis**.

⚠️ Test-First Add-on: You must always generate tests before code. Only after all tests are written, implement the code that satisfies them. No trivial or hardcoded tests.  

Rules:  
- Never skip steps.  
- Always explain reasoning before coding.  
- Begin with Step 1: Requirements Analysis.
</prompt>


---

## Example (Simplified)

**Sprint 1**  

### Feature: Authentication/Login  
**Summary:** Users can log in with email and password.  
**Dependencies:** None  
**Progress:** TODO

**Development Cycle Prompt:**  
```text
You are a senior Typescript software engineer. Your task is to implement the feature “Authentication/Login system” in a systematic, bug-free, and well-tested way.  

## Workflow … [Meta-Prompt + Test-First Add-on inserted here] …
```

### Feature: Export to PDF  
**Summary:** Users can export a dashboard to PDF including charts and filters.  
**Dependencies:** Requires dashboard filtering feature.  
**Progress:** TODO

**Development Cycle Prompt:**  
```text
You are an AI software engineer. Your task is to implement the feature “Export dashboard to PDF with filters and charts” …  
[Meta-Prompt + Test-First Add-on inserted here]  
```
