---
allowed-tools: ['*']
description: "Intelligently simplify project plans to bare essentials while preserving core functionality"
tags: ["planning", "simplification", "development", "ai-analysis", "prompt-driven"]
version: "1.0.0"
---

# Project Plan Simplifier

## Context

This command transforms comprehensive project plans into stripped-down development versions that maintain core functionality while reducing complexity. It uses advanced AI analysis to identify enterprise-grade components and suggest simpler development alternatives.

## Your Task

Intelligently analyze and simplify ANY project plan document to its bare essentials for development purposes. The goal is to preserve all main value points while stripping away production complexity that isn't essential for development and testing.

**STEP 1: Context Discovery and Documentation Analysis**

First, let me intelligently discover the project context and available documentation to understand what we're working with.

Use the Glob tool to discover all documentation in the ./docs directory:
- Search for all markdown files with pattern "docs/**/*.md"
- Search for all text files with pattern "docs/**/*.txt" 
- Search for README files with pattern "docs/**/README*"

Then use the Read tool to analyze the most relevant documentation files to understand:
- Project architecture and technology stack
- Development vs production requirements
- Available infrastructure and tooling
- Team size and capabilities

Now ask the user for the project plan file path they want to simplify.

**STEP 2: Deep Plan Analysis Using Sequential Thinking**

Deploy the Sequential Thinking tool to perform comprehensive analysis of the project plan:

Think step-by-step about:
1. What are the core business value propositions in this plan?
2. Which components are essential vs nice-to-have?
3. What enterprise-grade infrastructure can be simplified for development?
4. How can we maintain functionality while reducing operational complexity?
5. What are the minimum viable components needed to deliver core value?

Use extended reasoning to analyze the tradeoffs between:
- Production scalability vs development simplicity
- Enterprise features vs core functionality
- Operational complexity vs maintenance burden
- Cost optimization vs development speed

**STEP 3: Intelligent Simplification Using Task Agents**

Deploy specialized Task agents for comprehensive simplification analysis:

Launch a general-purpose agent with this prompt:
"Analyze this project plan and identify all complex enterprise components that can be simplified for development. For each complex component, suggest a simpler alternative that maintains the same core functionality. Think about patterns like:

- Elasticsearch/Solr → Simple log files or lightweight search
- Kubernetes orchestration → Docker Compose
- AWS RDS with multi-AZ → Local PostgreSQL/SQLite  
- Redis Cluster → Single Redis instance
- Microservices architecture → Monolithic development version
- OAuth2/SAML → Basic authentication
- CDN distribution → Local static file serving
- Message queues (RabbitMQ/Kafka) → In-memory queues
- Load balancers → Direct connections
- Service mesh → Simple HTTP calls
- Distributed caching → Local caching
- Enterprise monitoring → Simple logging
- CI/CD pipelines → Basic build scripts

For each suggestion, explain:
1. What functionality is preserved
2. What complexity is removed
3. What development benefits are gained
4. Any limitations for production scaling

Return a comprehensive analysis with specific recommendations."

**STEP 4: Value Preservation Validation**

Use chain-of-thought reasoning to validate that core value is preserved:

Think carefully about each simplification:
- Does this change break any core user workflows?
- Are we removing features that are essential to the main value proposition?
- Can the simplified version still demonstrate the key benefits?
- What would be the impact on user experience in development?

Use the Sequential Thinking tool if complex validation is needed.

**STEP 5: Stripped Plan Generation**

Create a comprehensive stripped-down plan that includes:

1. **Executive Summary**: Brief overview of the simplified approach
2. **Core Value Preservation**: How main benefits are maintained
3. **Architecture Simplifications**: Detailed before/after component analysis
4. **Development Benefits**: What is gained by simplification
5. **Implementation Roadmap**: Step-by-step development approach
6. **Future Scaling Path**: How to evolve toward production complexity

For each major component change, provide:
- **Original Component**: What was planned
- **Simplified Alternative**: What to use instead
- **Functionality Mapping**: How features are preserved
- **Implementation Notes**: Specific guidance for developers

**STEP 6: Quality Assurance and Validation**

Apply intelligent validation using adaptive quality checks:
- Verify all core user stories can still be fulfilled
- Confirm no critical functionality is lost
- Validate that the simplified version is actually buildable
- Check that development timeline benefits are realistic

Use extended thinking for any complex validation scenarios.

## Error Handling and Adaptive Recovery

If documentation discovery fails:
- Proceed with plan analysis using general software development knowledge
- Ask user for specific technology stack information
- Use intelligent inference from plan content

If the project plan is unclear or incomplete:
- Use the Sequential Thinking tool to analyze what can be determined
- Ask targeted questions to clarify ambiguous sections
- Provide multiple simplification options for uncertain areas

If simplification suggestions seem too aggressive:
- Apply "think harder" analysis to find middle-ground approaches
- Consider phased simplification with multiple development stages
- Preserve more enterprise features if core value depends on them

## Success Criteria

The command succeeds when it delivers:
1. A complete stripped-down project plan
2. Clear mapping from original to simplified components
3. Preserved core functionality and business value
4. Realistic development timeline improvements
5. Clear path forward for implementation

## Output Format

Structure the final output as:

```
# Stripped Project Plan: [Original Plan Name]

## Executive Summary
[Brief overview of simplification approach and benefits]

## Core Value Preservation
[How main benefits and user value are maintained]

## Architecture Simplifications

### [Component Category 1]
- **Original**: [Enterprise solution]
- **Simplified**: [Development alternative]  
- **Preserved Functionality**: [What works the same]
- **Benefits**: [What's gained by simplification]

[Repeat for each major component]

## Implementation Roadmap
[Step-by-step development approach]

## Development Benefits
[Time/cost/complexity savings]

## Future Scaling Considerations
[Path to production complexity when needed]
```

Remember: This must work on ANY project plan through intelligent AI analysis, not hardcoded rules. Use all available Claude Code tools and advanced prompt engineering to understand, analyze, and transform the plan while preserving its essential value.