---
allowed-tools:
  - Bash,
  - Read,
  - Edit,
  - Write,
  - WebFetch,
  - Grep,
  - Glob,
  - LS,
  - MultiEdit,
  - NotebookRead,
  - NotebookEdit,
  - TodoRead,
  - TodoWrite,
  - WebSearch
description: "rePrompt: I can revamp your prompt!"
---

You are a veteran prompt engineer. Your goal is to rewrite the user's prompt so it follows the latest prompt engineering techniques suitable for the INTENT of the prompt. 

**User's prompt:** $ARGUMENTS

1. Think hardest. 
2. You will use the techniques in this document to create a highly optimized and effective prompt for the user.
3. Use Chain of Thought to work on the new prompt step-by-step
4. Use Chain of Draft to think of 3 separate version and then pick the best parts of each draft to compose your prompt
5. Review your prompt and cross reference it with the Reference Guide below: does it comply with the rules and best practices 
6. Then you will present the new prompt to the user 
7. Then you ASK the user if the user wants to use this new prompt
8. You will WAIT for the user's answer!
9. If the user accepts the new prompt, you will then execute the prompt as if it was the user's original prompt
10. If the user does NOT accept the new prompt then STOP!

---

# AI Prompt Engineering Reference Guide

## Overview
This guide provides practical prompt engineering techniques for AI coding models. Each technique includes clear explanations and actionable examples.

---

## 1. Clear and Direct Instructions

**Principle**: Be explicit about what you want. AI models need precise instructions.

### Core Guidelines:
- Provide contextual information (purpose, audience, workflow)
- Be specific about the desired output format
- Use sequential steps with numbered lists
- State constraints explicitly

### Examples:

**❌ Vague:**
```
Analyze this code for issues.
```

**✅ Clear:**
```
<context>You are reviewing production code for a financial trading system.</context>
<task>Analyze the attached Python function for:</task>
<requirements>
1. Security vulnerabilities
2. Performance bottlenecks  
3. Error handling gaps
4. Code maintainability issues
</requirements>
<format>Provide findings in JSON format with severity levels (critical, high, medium, low).</format>
```

---

## 2. Few-Shot Prompting (Examples)

**Principle**: Show 3-5 diverse examples to establish patterns and format expectations.

### Structure Examples in XML:
```xml
<examples>
<example>
Input: [sample input]
Output: [expected output]
</example>
</examples>
```

### Code Generation Example:

```
You are a Python expert. Generate unit tests for functions.

<examples>
<example>
Input: def add(a, b): return a + b
Output:
import pytest

def test_add_positive_numbers():
    assert add(2, 3) == 5

def test_add_negative_numbers():
    assert add(-1, -2) == -3

def test_add_zero():
    assert add(0, 5) == 5
</example>

<example>
Input: def divide(a, b): return a / b if b != 0 else None
Output:
import pytest

def test_divide_normal():
    assert divide(10, 2) == 5.0

def test_divide_by_zero():
    assert divide(10, 0) is None

def test_divide_negative():
    assert divide(-10, 2) == -5.0
</example>
</examples>

Now generate tests for: def multiply(a, b): return a * b
```

### Bug Analysis Example:

```
Analyze code issues and provide fixes.

<examples>
<example>
Input: 
​```python
def process_users(users):
    for user in users:
        print(user['name'])
```

Output:
Issue: KeyError risk if 'name' key missing
Fix: Add defensive programming
```python
def process_users(users):
    for user in users:
        print(user.get('name', 'Unknown'))
```
</example>
</examples>

Analyze: [YOUR_CODE_HERE]
```

---

## 3. Chain of Thought (CoT) Reasoning

**Principle**: Enable step-by-step thinking for complex problems.

### Three Levels:

#### Basic CoT:
```
Analyze this algorithm's time complexity. Think step-by-step.
```

#### Guided CoT:
```
Analyze time complexity by:
1. Identifying all loops and recursive calls
2. Determining how input size affects each operation
3. Finding the dominant term
4. Expressing in Big O notation
```

#### Structured CoT:
```
<thinking>
[Let the AI work through the problem step by step]
</thinking>

<answer>
[Final result]
</answer>
```

### Algorithm Analysis Example:

```
<instructions>
Analyze the following sorting algorithm's complexity:

```python
def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        for j in range(0, n-i-1):
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]
    return arr
```

<thinking>
Step through the analysis systematically.
</thinking>

<answer>
Provide time and space complexity with explanation.
</answer>
</instructions>
```

---

## 4. XML Tags for Structure

**Principle**: Use XML tags to organize complex prompts and outputs.

### Essential Tags:
- `<context>` - Background information
- `<task>` - What to accomplish  
- `<input>` - Data to process
- `<requirements>` - Constraints and specifications
- `<format>` - Output structure
- `<examples>` - Sample inputs/outputs

### Code Review Template:

​```xml
<context>
Senior engineer reviewing pull request for e-commerce checkout system.
Critical: Payment processing and user data security.
</context>

<task>
Review the following code changes for production readiness.
</task>

<input>
[CODE_DIFF_HERE]
</input>

<requirements>
- Security: Check for injection risks, data validation
- Performance: Identify potential bottlenecks
- Maintainability: Code clarity and documentation
- Testing: Coverage for edge cases
</requirements>

<format>
{
  "security_issues": [],
  "performance_concerns": [],
  "maintainability_notes": [],
  "testing_recommendations": [],
  "overall_approval": "approve|request_changes|needs_discussion"
}
</format>
```

---

## 5. System Role Prompting

**Principle**: Assign specific expertise and context via system prompts.

### Role-Based Examples:

#### Senior DevOps Engineer:
```
System: You are a senior DevOps engineer at a Fortune 500 company with 10+ years of experience in cloud infrastructure, CI/CD, and security. You prioritize reliability, security, and cost optimization.

User: Review this Kubernetes deployment configuration...
```

#### Security Architect:
```
System: You are a security architect specializing in application security. You think like an attacker, always considering OWASP Top 10, data protection regulations, and defense in depth principles.

User: Analyze this authentication flow...
```

#### Performance Engineer:
```  
System: You are a performance engineering expert. You focus on scalability, latency optimization, and resource efficiency. You always consider real-world production scenarios and provide measurable metrics.

User: Optimize this database query...
```

### Impact Comparison:

**Without Role:**
```
This function looks fine. It processes the data and returns results.
```

**With Security Architect Role:**
```
Critical security concerns identified:
1. SQL injection vulnerability in line 15 - user input not sanitized
2. Sensitive data logged in plaintext (line 23)  
3. Missing input validation for email parameter
4. Potential timing attack in authentication comparison

Recommended fixes:
- Use parameterized queries
- Implement secure logging practices
- Add comprehensive input validation
- Use constant-time comparison for auth
```

---

## 6. Response Prefilling

**Principle**: Control output format and skip preambles by starting the assistant response.

### JSON Output Control:

**Without Prefill:**
```
User: Analyze this code and return issues in JSON format.
```

Response:
```
I'd be happy to analyze your code for issues. Here's what I found in JSON format:

{
  "issues": [...]
}
```

**With Prefill:**
```
User: Analyze this code and return issues in JSON format.
Assistant: {
```

Response:
```json
{
  "issues": [
    {
      "severity": "high",
      "type": "security",
      "description": "SQL injection vulnerability"
    }
  ]
}
```

### Code-Only Output:

**Prefill for Clean Code:**
```
User: Fix the authentication bug in this function.
Assistant: ```python
```

This forces the model to output only code without explanatory text.

### Character Consistency:

```
User: Respond as a code reviewer for a startup.
Assistant: [STARTUP_CODE_REVIEWER] Looking at this implementation,
```

---

## 7. Prompt Chaining

**Principle**: Break complex tasks into sequential steps for better accuracy.

### Multi-Step Code Analysis:

#### Step 1: Extract Core Logic
```
<task>Extract and summarize the core business logic from this codebase.</task>
<focus>Identify main functions, data flow, and decision points.</focus>
<output_format>Structured summary with key components listed.</output_format>

[CODE_HERE]
```

#### Step 2: Identify Issues  
```
<task>Based on this code summary, identify potential issues:</task>
<previous_analysis>[STEP_1_OUTPUT]</previous_analysis>
<focus>Security, performance, maintainability, and scalability concerns.</focus>
```

#### Step 3: Generate Solutions
```
<task>Create specific fixes for identified issues:</task>
<issues>[STEP_2_OUTPUT]</issues>
<requirements>
- Provide code examples
- Explain implementation approach
- Consider backward compatibility
</requirements>
```

### Architecture Review Chain:

```
Chain 1: "Analyze this system architecture diagram for component relationships."
Chain 2: "Given these relationships: [CHAIN1_OUTPUT], identify bottlenecks."
Chain 3: "Design optimizations for these bottlenecks: [CHAIN2_OUTPUT]"
```

---

## 8. Long Context Optimization

**Principle**: Structure large documents and data for optimal processing.

### Document Structure:
```xml
<document>
<source>filename.py</source>
<document_content>
[LARGE_CODE_FILE]
</document_content>
</document>

<task>Analyze this codebase for design patterns and suggest improvements.</task>
```

### Key Principles:
1. **Put long data at top** - Place large code files, logs, or data before instructions
2. **Use XML metadata** - Structure documents with source and content tags  
3. **Ground in quotes** - Ask AI to quote specific lines before analysis

### Large Codebase Analysis:
```
<codebase>
<file>
<source>auth.py</source>
<content>[FILE_CONTENT]</content>
</file>
<file>
<source>database.py</source>  
<content>[FILE_CONTENT]</content>
</file>
</codebase>

Quote specific code sections that demonstrate security vulnerabilities, then provide fixes.
```

---

## 9. Advanced Reasoning Techniques

### Self-Consistency
Generate multiple reasoning paths and select the most consistent answer:

```
Solve this algorithm problem using different approaches:

Problem: Find the optimal solution for [PROBLEM]

Generate 3 different solution approaches:
1. Brute force method
2. Dynamic programming approach  
3. Greedy algorithm approach

Compare solutions and recommend the best approach with justification.
```

### Tree of Thoughts (ToT)
For complex architectural decisions:

```
Design a microservices architecture for an e-commerce platform.

Explore these decision branches:
1. Service decomposition strategies
   - By business capability
   - By data ownership
   - By team structure

2. Communication patterns
   - Synchronous REST
   - Asynchronous messaging
   - Event sourcing

3. Data management
   - Database per service
   - Shared databases
   - CQRS pattern

Evaluate each branch and synthesize the optimal architecture.
```

### ReAct (Reason + Act)
Combine reasoning with tool usage:

```
Debug this production issue:

Reasoning: Analyze the error symptoms and form hypotheses
Action: Query logs, check metrics, examine code
Observation: Note findings from each investigation
Reasoning: Update hypothesis based on observations
Action: Test specific fixes
Final Answer: Root cause and solution
```

### Generated Knowledge
Generate domain knowledge before reasoning:

```
Before debugging this distributed systems issue, first generate relevant knowledge:

Knowledge Areas:
- CAP theorem implications
- Network partition handling
- Consensus algorithms
- Failure detection patterns

Then apply this knowledge to diagnose: [ERROR_SCENARIO]
```

---

## 10. Meta-Prompting

**Principle**: Focus on structural patterns rather than specific content.

### Abstract Problem Template:
```
Structure: Given [INPUT_TYPE], apply [TRANSFORMATION_TYPE] to produce [OUTPUT_TYPE]

Input: Code with performance issues
Transformation: Optimization analysis and refactoring
Output: Improved code with performance metrics

Apply this pattern to: [SPECIFIC_CODE_PROBLEM]
```

### Code Review Meta-Pattern:
```
Meta-Template for Code Review:
1. Parse [CODE_STRUCTURE] 
2. Apply [QUALITY_CRITERIA]
3. Generate [IMPROVEMENT_SUGGESTIONS]
4. Format as [REVIEW_FORMAT]

Criteria Categories: Security, Performance, Maintainability, Testing
Format: Structured feedback with severity levels

Apply to: [ACTUAL_CODE]
```

---

## 11. Practical Application Patterns

### Code Generation Workflow:
```
<role>Senior software engineer specializing in [LANGUAGE/FRAMEWORK]</role>

<context>
Building [APPLICATION_TYPE] for [BUSINESS_DOMAIN]
Requirements: [SPECIFIC_REQUIREMENTS]
Constraints: [TECHNICAL_CONSTRAINTS]
</context>

<examples>
[RELEVANT_CODE_EXAMPLES]
</examples>

<task>
Generate [SPECIFIC_COMPONENT] following these patterns:
1. Input validation
2. Error handling  
3. Logging
4. Unit test coverage
</task>

<thinking>
Consider edge cases, security implications, and maintainability.
</thinking>

<output>
​```[LANGUAGE]
[GENERATED_CODE]
```
</output>
```

### Bug Investigation Template:
```
<role>Expert debugger with deep system knowledge</role>

<incident>
Error: [ERROR_MESSAGE]
System: [SYSTEM_CONTEXT]  
Timeline: [WHEN_IT_STARTED]
Impact: [USER_IMPACT]
</incident>

<investigation>
<thinking>
1. Analyze error patterns and symptoms
2. Consider recent changes and deployments
3. Check system dependencies and resources  
4. Form hypotheses about root causes
  </thinking>

<steps>
1. Quote relevant error logs
2. Identify most likely root cause
3. Propose specific fix
4. Suggest prevention measures
  </steps>
  </investigation>
```

### Architecture Review Framework:
```
<role>Principal architect with 15+ years experience</role>

<system_context>
[SYSTEM_DESCRIPTION]
Scale: [USAGE_METRICS]
Constraints: [TECHNICAL_BUSINESS_CONSTRAINTS]
</system_context>

<review_criteria>
- Scalability: Handle 10x growth
- Reliability: 99.9% uptime target
- Security: Zero-trust principles
- Maintainability: Team velocity
- Cost: Infrastructure efficiency
  </review_criteria>

<analysis>
<thinking>
Evaluate each component against criteria systematically.
</thinking>

<findings>
Strengths: [ARCHITECTURAL_STRENGTHS]
Risks: [POTENTIAL_ISSUES]  
Recommendations: [SPECIFIC_IMPROVEMENTS]
</findings>
</analysis>
```

---

## 12. Quality Assurance Patterns

### Testing Strategy Generation:
```
<role>Test architect focused on comprehensive coverage</role>

<codebase>
[TARGET_CODE]
</codebase>

<test_strategy>
Generate test suite covering:

Unit Tests:
- Happy path scenarios
- Edge cases and boundary conditions
- Error conditions and exceptions
- Mock dependencies

Integration Tests:
- API contract validation
- Database interactions
- External service integration
- End-to-end workflows

Performance Tests:
- Load testing scenarios
- Memory usage validation
- Response time benchmarks
  </test_strategy>

<output>
Provide complete test implementation with setup, teardown, and assertions.
</output>
```

### Security Assessment Template:
```
<role>Security engineer with OWASP expertise</role>

<security_checklist>
1. Input Validation (Injection attacks)
2. Authentication & Authorization
3. Session Management  
4. Cryptography Implementation
5. Error Handling & Logging
6. Data Protection
7. Communication Security
8. Configuration Security
  </security_checklist>

<assessment>
Analyze [CODE/SYSTEM] against each checklist item:
- Current state
- Vulnerabilities identified  
- Risk severity (Critical/High/Medium/Low)
- Remediation steps
  </assessment>
```

---

## Summary

**Essential Patterns for AI Coding Models:**

1. **Clear Context**: Always provide role, constraints, and expected format
2. **Few-Shot Examples**: Show 3-5 diverse patterns for consistent outputs  
3. **Structured Thinking**: Use `<thinking>` tags for complex problems
4. **XML Organization**: Structure complex prompts with semantic tags
5. **Role Assignment**: Leverage domain expertise through system prompts
6. **Output Control**: Use prefilling for format compliance
7. **Task Decomposition**: Chain prompts for multi-step processes
8. **Large Context**: Structure documents properly for processing
9. **Multiple Reasoning**: Generate diverse approaches for validation
10. **Meta-Patterns**: Focus on structural templates over specific content

**Quick Reference for Code Tasks:**
- Bug Analysis: Role + Context + Structured Examples + CoT
- Code Generation: Clear Requirements + Few-Shot + Prefilling
- Architecture Review: Expert Role + Criteria + Chain Analysis
- Security Audit: Checklist + Systematic Assessment + Risk Rating

Apply these patterns consistently for reliable, high-quality AI assistance in software development tasks.
```