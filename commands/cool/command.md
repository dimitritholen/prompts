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
description: "Expert prompt engineering system that creates optimized Claude commands"
---

# Claude Command Generator

## Your Task

Transform the user's requirements in $ARGUMENTS into a production-ready Claude command using advanced prompt engineering techniques and chain-of-thought analysis.

🚨 **CRITICAL CONSTRAINT: ZERO-CODE POLICY** 🚨
Generated commands MUST be 100% prompt-driven with NO embedded code snippets, bash commands, or hardcoded scripts. All functionality must be achieved through intelligent AI prompting, tool orchestration, and reasoning patterns.

**STEP 1: REQUIREMENTS ANALYSIS**

Parse and analyze the user's input to identify:
- Primary objective and use case
- Technical domain (coding, analysis, automation, etc.)
- Required tools and capabilities
- Context dependencies
- Output format expectations
- Success criteria

**STEP 2: CHAIN OF THOUGHT COMMAND DESIGN**

Think step-by-step about the optimal command structure:

1. **Context Gathering Strategy**
   - What contextual information is needed?
   - Which Claude Code tools (Read, Glob, Grep, Task agents) will intelligently gather project state?
   - How to use AI-driven pattern recognition to detect project conventions?

2. **Workflow Architecture**
   - Should this be a linear process or multi-step workflow?
   - Are parallel sub-agents beneficial for complex tasks?
   - What checkpoints and validation steps are needed?

3. **Tool Selection and Integration**
   - Which Claude Code tools are most appropriate?
   - How to handle different project types and environments?
   - What fallback strategies are needed?

4. **Error Handling and Resilience**
   - How to gracefully handle missing dependencies?
   - What validation steps prevent common failures?
   - How to provide clear error messages and recovery suggestions?

5. **Output and Success Criteria**
   - What constitutes successful completion?
   - How to structure the output for maximum usability?
   - What follow-up actions or suggestions should be provided?

**STEP 3: ADVANCED PROMPT ENGINEERING INTEGRATION**

Apply these proven techniques:

**Chain of Thought Reasoning:**
- Use "Let me think step-by-step" patterns
- Include intermediate reasoning steps
- Make decision trees explicit

**Extended Thinking Integration:**
- Identify complex sections requiring "think harder" or "ultrathink"
- Apply extended reasoning to architectural decisions
- Use deep analysis for optimization opportunities

**Sub-Agent Orchestration:**
- Design parallel processing for independent tasks
- Create specialized agents for domain expertise
- Implement coordination and synthesis patterns

**Context Priming and Role Definition:**
- Establish clear persona and expertise domain
- Load relevant project context dynamically
- Maintain consistent voice and approach

**Structured Output Formatting:**
- Use clear section headers and organization
- Implement progress tracking and status updates
- Provide actionable recommendations

**Error Prevention and Validation:**
- Include comprehensive error checking
- Validate assumptions and prerequisites
- Provide clear failure modes and recovery

**STEP 4: COMMAND METADATA DESIGN**

Create appropriate YAML frontmatter:
- Select optimal tool permissions
- Write clear description and tags
- Set version and maintenance info

**STEP 5: INTELLIGENT CONTEXT DISCOVERY STRATEGY**

Design AI-driven analysis patterns that:
- Use Task agents to intelligently detect project type and structure
- Deploy specialized agents to gather relevant configuration through file analysis
- Apply pattern recognition to identify existing conventions and practices
- Use intelligent tool orchestration to assess project capabilities

**STEP 6: WORKFLOW IMPLEMENTATION**

Structure the command with:
- Clear step progression with validation
- Intermediate checkpoints and status
- Error handling and graceful degradation
- Success criteria and completion validation

**STEP 7: OUTPUT OPTIMIZATION**

Ensure the generated command:
- Follows established patterns from example commands
- Uses appropriate markdown formatting
- Includes comprehensive error handling
- Provides actionable feedback and next steps
- Maintains consistency with Claude Code conventions

## Advanced Prompt Engineering Patterns

### Chain of Thought Integration
**Pattern:** Embed step-by-step reasoning prompts throughout the command
- Use "Let me think step-by-step about..." triggers
- Include "First, I need to understand..." analysis phases
- Apply "Based on this analysis, the optimal approach is..." decision points

### Extended Thinking Triggers
**Pattern:** Deploy advanced reasoning for complex scenarios
- Use "Sequential Thinking" tool for multi-step analysis
- Apply "think harder about the tradeoffs" for architectural decisions
- Trigger "extended analysis of security implications" for sensitive operations

### Sub-Agent Orchestration  
**Pattern:** Coordinate specialized AI agents for parallel processing
- **Task Agent - Domain Expert**: Deploy for deep technical analysis
- **Task Agent - Quality Assurance**: Deploy for validation and testing
- **Task Agent - Documentation**: Deploy for clear communication
- **Task Agent - Integration**: Deploy for tool and system compatibility

### Intelligent Validation Checkpoints
**Pattern:** Use AI-driven validation instead of hardcoded checks
- Apply "intelligent prerequisite assessment using available tools"
- Use "adaptive project structure analysis" to understand context
- Deploy "smart error detection and recovery suggestion" patterns

### Dynamic Success Criteria
**Pattern:** Create adaptive completion validation
- Use TodoWrite for tracking progress dynamically
- Apply "intelligent completion assessment" based on discovered requirements  
- Implement "adaptive success metrics" that respond to project characteristics

## Quality Assurance Framework

**Input Validation:**
- Check for required parameters
- Validate file paths and permissions
- Verify tool dependencies

**Process Monitoring:**
- Track progress through workflow steps
- Log intermediate results for debugging
- Validate each step before proceeding

**Output Verification:**
- Confirm completion criteria met
- Validate output format and content
- Check for any remaining errors or warnings

**Error Recovery:**
- Provide specific error messages
- Suggest corrective actions
- Offer fallback approaches when possible

## Command Generation Standards

**File Structure:**
- YAML frontmatter with complete metadata
- Context section with dynamic environment detection
- Clear step-by-step workflow with validation
- Error handling and recovery procedures
- Success criteria and completion validation

**Prompt Engineering Standards:**
- Use intelligent AI-driven environment discovery through Claude Code tools
- Implement adaptive error handling through smart prompting patterns
- Follow markdown formatting conventions with clear reasoning triggers
- Include comprehensive AI guidance patterns and intelligent examples

**Testing Integration:**
- Build in validation checkpoints
- Include self-testing capabilities where appropriate
- Provide clear success/failure indicators

## Generated Command Template

**PROMPT-DRIVEN STRUCTURE:**
---
allowed-tools: [intelligent tool selection based on requirements]
description: "[Clear purpose emphasizing AI-driven approach]"
tags: [relevant tags including "prompt-driven", "ai-analysis"]
---

## Context
[AI-driven context discovery using intelligent prompting and Claude Code tool orchestration]

## Your Task  
[Clear objective with detailed requirements emphasizing intelligent analysis]

**STEP 1**: [AI-guided initial analysis and intelligent setup]
**STEP 2**: [Prompt-driven core processing with reasoning chains]
**STEP 3**: [Intelligent validation using adaptive quality checks]
**STEP 4**: [AI-synthesized output generation and smart finalization]

[Comprehensive prompt-driven error handling, adaptive validation, and intelligent success criteria]

## 🚫 ZERO-CODE ENFORCEMENT GUIDELINES

**FORBIDDEN ELEMENTS (Never Include):**
- Bash command blocks or inline bash commands
- Code snippets of any programming language  
- Hardcoded scripts or command sequences
- Static file paths or directory structures
- Fixed command-line operations

**REQUIRED REPLACEMENTS (Always Use Instead):**
- **Tool Orchestration**: Use Task agents, Read, Glob, Grep, etc. through intelligent prompting
- **AI-Driven Analysis**: "Let me intelligently analyze..." instead of hardcoded commands
- **Reasoning Chains**: "Think step-by-step about optimal approach..." 
- **Adaptive Discovery**: "Use intelligent file pattern recognition..." instead of fixed paths
- **Smart Validation**: "Apply adaptive validation using available tools..." instead of static checks

**PROMPT-DRIVEN COMMAND PATTERNS:**
- "Deploy a specialized Task agent to intelligently..."
- "Use chain-of-thought reasoning to determine..."  
- "Apply extended thinking to analyze the tradeoffs..."
- "Orchestrate parallel agents for comprehensive..."
- "Synthesize findings using intelligent pattern recognition..."

## Execution

Generate a complete, production-ready Claude command that:
1. **ENFORCES ZERO-CODE POLICY**: Contains absolutely no embedded code snippets, bash commands, or hardcoded scripts
2. **Uses Pure AI Intelligence**: Relies entirely on intelligent prompting, reasoning chains, and tool orchestration  
3. **Incorporates Advanced Prompt Engineering**: Deploys chain-of-thought, extended thinking, and sub-agent patterns
4. **Follows Adaptive Best Practices**: Uses intelligent, context-aware approaches instead of static procedures
5. **Implements Smart Error Handling**: Uses AI-driven validation and adaptive recovery strategies
6. **Provides Dynamic Success Criteria**: Creates intelligent, responsive completion indicators

The generated command should be 100% prompt-driven, immediately usable, and represent the pinnacle of AI-powered command design using advanced reasoning and intelligent tool orchestration.