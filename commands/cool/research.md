---
allowed-tools: [Task, WebSearch, WebFetch, Bash, Read, Write, Edit, Glob, Grep, LS, MultiEdit]
description: "Intelligent research command that analyzes questions in project context, launches parallel research agents, reviews quality, and offers documentation integration"
version: "1.0.0"
tags: ["research", "analysis", "documentation", "multi-agent"]
---

# Intelligent Project-Aware Research Command

## Context Collection
First, let me gather comprehensive context about your current project to ensure the research is highly relevant and actionable.

```bash
# Detect project type and structure
find . -maxdepth 3 -name "package.json" -o -name "requirements.txt" -o -name "Cargo.toml" -o -name "pom.xml" -o -name "go.mod" -o -name "composer.json" | head -10
```

```bash
# Find existing documentation
find . -maxdepth 3 -name "*.md" -o -name "*.rst" -o -name "*.txt" | grep -E "(README|DOCS?|GUIDE)" | head -10
```

```bash
# Understand project scope and technologies
ls -la | head -20
```

## Your Task

I'm going to conduct ultra-comprehensive research on your question while considering your specific project context. Here's my systematic approach:

**QUESTION**: {Insert your research question here}

## STEP 1: CONTEXTUAL ANALYSIS AND RESEARCH PLANNING

Let me think step-by-step about how to approach this research optimally:

### Project Context Assessment
- **Project Type**: [Analyzing detected project structure]
- **Current Tech Stack**: [Identifying technologies in use]
- **Existing Documentation**: [Cataloging current docs]
- **Question Relevance**: [How this question relates to your specific project]

### Research Strategy Design
Let me **think harder** about the most effective research approach:

1. **Information Architecture Analysis**
   - What are the core information domains needed?
   - Which sources will provide the most authoritative answers?
   - How does this relate to your specific project requirements?

2. **Research Vector Planning**
   - Primary research paths for comprehensive coverage
   - Secondary validation sources for accuracy
   - Project-specific implementation considerations

3. **Quality Assurance Framework**
   - How to validate information accuracy
   - Cross-referencing strategy for reliability
   - Relevance filtering for your specific context

## STEP 2: PARALLEL RESEARCH AGENT DEPLOYMENT

I'm deploying multiple specialized research agents to gather comprehensive information from different perspectives:

### Agent 1: Domain Expert Research
*Focuses on deep technical knowledge and current best practices*

### Agent 2: Implementation-Focused Research  
*Searches for practical examples and real-world applications relevant to your project*

### Agent 3: Latest Developments Research
*Finds cutting-edge information and recent updates in the field*

### Agent 4: Problem-Solution Research
*Identifies common challenges and proven solutions in your specific context*

## STEP 3: RESEARCH EXECUTION AND SYNTHESIS

**CHECKPOINT**: Validating research quality and relevance
- [ ] Information accuracy verified across multiple sources
- [ ] Relevance to project context confirmed
- [ ] Implementation feasibility assessed
- [ ] Potential risks and limitations identified

### Research Quality Review Process

Let me **ultrathink** about the research findings to ensure maximum value:

1. **Information Validation**
   - Cross-referencing multiple authoritative sources
   - Verifying currency and accuracy of information
   - Identifying any conflicting or outdated information

2. **Project Relevance Analysis**  
   - How directly applicable is this to your project?
   - What adaptations are needed for your specific context?
   - Are there project-specific considerations or constraints?

3. **Implementation Readiness Assessment**
   - What prerequisites exist for implementation?
   - What resources or tools are required?
   - Are there any compatibility issues with your current setup?

## STEP 4: RESEARCH FINDINGS AND RECOMMENDATIONS

### Comprehensive Research Summary

[This section will be populated with synthesized findings from all research agents]

**Key Findings:**
- [Primary insights relevant to your question]
- [Implementation considerations for your project]
- [Best practices and recommendations]
- [Potential challenges and solutions]

**Project-Specific Applications:**
- [How this applies to your current codebase/project]
- [Specific implementation steps for your context]
- [Integration considerations with existing systems]

**Additional Resources:**
- [Links to authoritative documentation]
- [Related tools and libraries]
- [Community resources and examples]

### Quality Assurance Validation

**COMPLETION CRITERIA (ALL must be ✅):**
- [ ] Question thoroughly researched from multiple angles
- [ ] Information accuracy verified across sources
- [ ] Project-specific relevance confirmed
- [ ] Implementation guidance provided
- [ ] Potential challenges and solutions identified
- [ ] Resources and next steps clearly outlined

## STEP 5: DOCUMENTATION INTEGRATION OPTION

Based on the research findings, would you like me to:

1. **📖 Augment Existing Documentation**
   - Add research findings to relevant existing docs
   - Create cross-references and links
   - Maintain consistency with existing style

2. **📝 Create New Documentation**
   - Generate dedicated documentation for this topic
   - Structure as implementation guide or reference
   - Include examples specific to your project

3. **🔗 Create Knowledge Links**
   - Add references to existing code comments
   - Create internal documentation links
   - Build searchable knowledge base entries

4. **📋 Generate Action Items**
   - Create task list for implementation
   - Identify dependencies and prerequisites
   - Suggest timeline and priorities

**Documentation Integration Approach:**
- Maintain consistency with existing documentation style
- Follow project naming and organizational conventions
- Include relevant code examples using your project patterns
- Add appropriate cross-references and navigation

### Error Handling and Recovery

**IF research quality is insufficient:**
- Deploy additional specialized research agents
- Expand search terms and information domains
- Consult additional authoritative sources
- Request user clarification on specific aspects

**IF project context is unclear:**
- Gather additional project information
- Ask targeted questions about specific requirements
- Analyze existing codebase patterns more deeply

**IF documentation integration conflicts arise:**
- Preserve existing documentation structure
- Suggest alternative integration approaches
- Provide options for different documentation strategies

---

## Usage Instructions

To use this command, simply provide your research question as a parameter. The command will:

1. **Analyze** your current project context automatically
2. **Research** your question using multiple parallel agents
3. **Synthesize** findings with project-specific relevance
4. **Quality-check** all information for accuracy and applicability  
5. **Offer** to integrate findings into your documentation

**Example Usage:**
- "How should I implement authentication in my React app?"
- "What's the best way to handle async operations in this Python project?"
- "How can I optimize database queries for this specific use case?"

The research will be tailored to your exact project context and provide actionable, implementation-ready insights.