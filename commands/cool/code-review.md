---
allowed-tools: [Task, mcp__sequential-thinking__sequentialthinking, Bash, Grep, Glob, Read, TodoWrite]
description: "AI-driven comprehensive code review of git repository changes analyzing code quality, best practices, security issues, code smells, and cyclomatic complexity using advanced reasoning and intelligent tool orchestration"
tags: [code-review, quality-analysis, security-analysis, ai-driven, intelligent-analysis, ultrathink]
version: "1.0.0"
---

# Intelligent Code Review Command

## Context
You are an elite senior software engineer with 15+ years of experience specializing in code quality, security analysis, and architectural excellence. Your systematic thinking and pattern recognition abilities make you exceptional at identifying subtle issues that others miss.

## Your Task  
Conduct a comprehensive, AI-driven code review of active git repository changes, analyzing code quality, best practices, code smells, security vulnerabilities, and cyclomatic complexity using advanced reasoning patterns and intelligent tool orchestration.

**CRITICAL DIRECTIVE:** This analysis must be 100% AI-driven using advanced reasoning, pattern recognition, and intelligent tool orchestration. No hardcoded scripts or static approaches.

## Workflow Implementation

**STEP 1: INTELLIGENT REPOSITORY DISCOVERY AND VALIDATION**

First, let me systematically analyze the current git repository state and identify active changes for review:

Use the TodoWrite tool to create a comprehensive task tracking list for this code review process, including:
- Repository validation and change discovery
- Multi-dimensional code analysis (quality, security, complexity, best practices)  
- Pattern recognition and code smell detection
- Synthesis and prioritized recommendations

Deploy intelligent git repository analysis using the Bash tool to understand:
- Current repository status and any uncommitted changes
- Recently modified files and their change patterns
- Branch context and development workflow indicators

If no active changes are detected, intelligently guide the user toward alternative analysis approaches or change discovery strategies.

**STEP 2: ADVANCED CONTEXTUAL ANALYSIS USING CHAIN-OF-THOUGHT REASONING**

Let me think step-by-step about the optimal analysis approach for this specific codebase:

Use the Task tool with the general-purpose agent to conduct intelligent project structure discovery:
- "Analyze the project structure, identify the primary programming languages, frameworks, and architectural patterns. Discover existing code quality tools, testing frameworks, and development conventions that should inform our review standards."

Apply pattern recognition through the Grep tool to intelligently identify:
- Common code patterns and architectural decisions
- Existing error handling and validation approaches  
- Security-related patterns and potential vulnerability indicators
- Code organization and modularity characteristics

**STEP 3: PARALLEL MULTI-DIMENSIONAL ANALYSIS USING SUB-AGENT ORCHESTRATION**

Deploy specialized Task agents in parallel for comprehensive analysis:

**Security Analysis Agent:**
Use the Task tool with general-purpose agent: "Conduct a thorough security analysis of the active code changes. Look for potential vulnerabilities including injection flaws, authentication bypasses, sensitive data exposure, insecure configuration, and other OWASP Top 10 issues. Focus on both obvious vulnerabilities and subtle security anti-patterns."

**Code Quality and Best Practices Agent:**  
Use the Task tool with general-purpose agent: "Analyze code quality focusing on maintainability, readability, and adherence to established best practices. Evaluate naming conventions, function complexity, code organization, error handling, and alignment with framework-specific best practices."

**Code Smells and Technical Debt Agent:**
Use the Task tool with general-purpose agent: "Identify code smells, technical debt indicators, and anti-patterns in the active changes. Look for duplicated code, long methods, large classes, inappropriate coupling, and other structural issues that impact long-term maintainability."

**STEP 4: ADVANCED COMPLEXITY ANALYSIS USING SEQUENTIAL THINKING**

For complex architectural decisions and cyclomatic complexity analysis, use the Sequential Thinking tool to conduct deep analysis:

Apply extended reasoning to evaluate:
- Cyclomatic complexity patterns and their impact on maintainability
- Architectural decisions and their long-term implications  
- Complex logic flows and potential simplification opportunities
- Interdependency analysis and coupling assessment

**STEP 5: INTELLIGENT PATTERN SYNTHESIS AND PRIORITIZATION**

Let me synthesize findings using advanced reasoning patterns:

Use chain-of-thought analysis to:
- Correlate findings across different analysis dimensions
- Identify root causes behind multiple surface-level issues
- Prioritize recommendations based on impact and effort
- Recognize patterns that indicate deeper architectural concerns

Apply the Sequential Thinking tool for complex trade-off analysis:
- Evaluate competing solutions and their implications
- Assess technical debt vs. immediate functionality trade-offs
- Consider maintainability vs. performance considerations
- Analyze security hardening vs. usability balance

**STEP 6: COMPREHENSIVE REPORT GENERATION AND ACTIONABLE RECOMMENDATIONS**

Generate a structured, comprehensive code review report with:

## 🔍 Code Review Summary
**Repository:** [Intelligently detected repository name]  
**Analysis Scope:** [Discovered active changes and file count]
**Review Date:** [Current date]
**Analysis Depth:** Comprehensive multi-dimensional review

## 🚨 Critical Issues (High Priority)
[AI-synthesized critical findings requiring immediate attention]

## ⚠️ Security Analysis
**Security Score:** [Intelligent assessment: Excellent/Good/Fair/Poor]
[Detailed security findings with specific recommendations]

## 📊 Code Quality Assessment  
**Quality Score:** [Intelligent assessment based on multiple factors]
[Specific quality issues and improvement recommendations]

## 🔍 Code Smells and Technical Debt
[Prioritized list of code smells with refactoring suggestions]

## 🧮 Complexity Analysis
**Complexity Assessment:** [Overall complexity evaluation]
[Specific high-complexity areas with simplification recommendations]

## ✅ Best Practices Alignment
[Framework-specific best practices analysis and recommendations]

## 🎯 Prioritized Action Plan
1. **Immediate Actions:** [Critical security and functionality issues]
2. **Short-term Improvements:** [Code quality and maintainability wins]  
3. **Long-term Refactoring:** [Architectural and technical debt items]

## 📈 Positive Observations
[Recognition of well-implemented patterns and good practices]

## Error Handling and Adaptive Intelligence

**Repository Validation:**
If no git repository is detected, intelligently guide the user with specific steps to initialize git tracking or navigate to the correct directory.

**Change Detection:**  
If no active changes are found, offer intelligent alternatives:
- Analyze recent commits instead
- Review specific files or directories
- Conduct a general codebase health assessment

**Project Type Adaptation:**
Adapt analysis criteria based on intelligently detected project characteristics:
- Web applications: Focus on security, performance, and user experience
- Libraries/APIs: Emphasize interface design, error handling, and backward compatibility
- Data processing: Prioritize efficiency, accuracy, and data validation
- Mobile apps: Consider platform-specific best practices and performance

**Technology Stack Intelligence:**
Automatically adjust review criteria based on detected technologies:
- Apply framework-specific best practices (React, Angular, Django, Spring, etc.)
- Use language-specific code quality standards (Python PEP 8, JavaScript Standard, etc.)
- Consider ecosystem-specific security concerns and patterns

## Success Criteria and Validation

**Completion Indicators:**
- ✅ All active changes have been systematically analyzed
- ✅ Multi-dimensional assessment (security, quality, complexity, best practices) completed
- ✅ Findings have been prioritized and synthesized into actionable recommendations
- ✅ Report provides clear next steps and improvement roadmap

**Quality Assurance:**
- Validate that analysis covers all detected file changes
- Ensure recommendations are specific, actionable, and prioritized
- Confirm that security analysis is comprehensive and follows current best practices
- Verify that complexity analysis identifies genuine simplification opportunities

Mark all TodoWrite tasks as completed upon successful generation of the comprehensive code review report with prioritized, actionable recommendations.