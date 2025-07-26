#!/usr/bin/env node

const fs = require('fs').promises;
const path = require('path');

/**
 * Hash Prompts Knowledge Base Generator
 * 
 * This script parses all markdown command files and generates/updates the hash-prompts-kb.json
 * Ensures the KB stays in sync with markdown documentation
 */

class KBGenerator {
  constructor() {
    this.commandsPath = path.join(__dirname, '..');
    this.kbPath = path.join(__dirname, 'hash-prompts-kb.json');
    this.commands = {};
    this.rules = {
      global: {},
      quality_gates: {}
    };
  }

  async generate() {
    console.log('🚀 Starting Hash Prompts KB Generation...\n');
    
    try {
      // Load existing KB for comparison
      const existingKB = await this.loadExistingKB();
      
      // Parse all command markdown files
      await this.parseCommands();
      
      // Extract global rules
      this.extractGlobalRules();
      
      // Build the complete KB structure
      const kb = this.buildKBStructure();
      
      // Validate against schema
      await this.validateKB(kb);
      
      // Save the KB
      await this.saveKB(kb);
      
      // Report changes
      this.reportChanges(existingKB, kb);
      
      console.log('\n✅ KB Generation Complete!');
    } catch (error) {
      console.error('❌ Error generating KB:', error.message);
      process.exit(1);
    }
  }

  async loadExistingKB() {
    try {
      const data = await fs.readFile(this.kbPath, 'utf8');
      return JSON.parse(data);
    } catch (error) {
      console.log('📝 No existing KB found, creating new one...');
      return null;
    }
  }

  async parseCommands() {
    const files = await fs.readdir(this.commandsPath);
    const mdFiles = files.filter(f => f.endsWith('.md') && !f.startsWith('README'));
    
    console.log(`📄 Found ${mdFiles.length} command files to parse\n`);
    
    for (const file of mdFiles) {
      const commandName = file.replace('.md', '');
      console.log(`  Parsing ${commandName}...`);
      
      const content = await fs.readFile(path.join(this.commandsPath, file), 'utf8');
      this.commands[commandName] = this.parseCommandContent(commandName, content);
    }
  }

  parseCommandContent(name, content) {
    const command = {
      name,
      description: this.extractDescription(content),
      category: this.determineCategory(name, content),
      type: this.determineType(name, content),
      phases: this.extractPhases(content),
      workflow: this.extractWorkflow(name, content),
      time_estimates: this.extractTimeEstimates(content)
    };

    // Check for agent generation
    const agentMatches = content.match(/generate.*agent|create.*persona|technology.*expert/gi);
    if (agentMatches) {
      command.agents_generated = this.extractAgents(content);
    }

    return command;
  }

  extractDescription(content) {
    // Extract from title or first paragraph
    const titleMatch = content.match(/^#\s+(.+?)(?:\s*\{|$)/m);
    if (titleMatch) {
      return titleMatch[1].replace(/\s*\[.*?\]\s*/g, '').trim();
    }
    
    const firstParaMatch = content.match(/^(?!#)(.+?)$/m);
    return firstParaMatch ? firstParaMatch[1].trim() : '';
  }

  determineCategory(name, content) {
    const categoryMap = {
      'brainstorm': 'ideation',
      'prd': 'requirements',
      'architect': 'technical',
      'tasks': 'planning',
      'plan': 'planning',
      'code': 'implementation',
      'test': 'quality',
      'deploy': 'operations',
      'pipeline': 'orchestration',
      'feature': 'enhancement',
      'generate-agent': 'utility',
      'help': 'utility',
      'anti-overengineering': 'guidelines'
    };
    
    return categoryMap[name] || 'utility';
  }

  determineType(name, content) {
    if (name === 'pipeline') return 'meta_command';
    if (name === 'help') return 'documentation';
    if (name === 'anti-overengineering') return 'principles';
    return 'standard';
  }

  extractPhases(content) {
    const phases = [];
    const phaseRegex = /##\s*(?:Phase|Step)\s*(\d+[a-z]?):?\s*(.+?)(?=\n|$)/gi;
    let match;
    
    while ((match = phaseRegex.exec(content))) {
      const phaseId = `phase${match[1].toLowerCase()}`;
      const phaseName = match[2].trim();
      
      // Extract phase content
      const phaseStartIndex = match.index + match[0].length;
      const nextPhaseMatch = phaseRegex.exec(content);
      const phaseEndIndex = nextPhaseMatch ? nextPhaseMatch.index : content.length;
      phaseRegex.lastIndex = match.index + match[0].length; // Reset regex position
      
      const phaseContent = content.substring(phaseStartIndex, phaseEndIndex);
      
      const phase = {
        id: phaseId,
        name: phaseName,
        activities: this.extractActivities(phaseContent)
      };
      
      // Check for parallel research requirements
      if (phaseContent.match(/parallel.*(?:research|search|Task|agent)/i)) {
        phase.parallel_research = this.extractParallelResearch(phaseContent);
      }
      
      // Extract outputs if present
      const outputs = this.extractOutputs(phaseContent);
      if (outputs) {
        phase.outputs = outputs;
      }
      
      phases.push(phase);
    }
    
    return phases;
  }

  extractActivities(phaseContent) {
    const activities = [];
    const bulletRegex = /^[\s]*[-•*]\s+(.+?)$/gm;
    let match;
    
    while ((match = bulletRegex.exec(phaseContent))) {
      const activity = match[1].trim();
      // Filter out sub-bullets and examples
      if (!activity.startsWith('-') && !activity.startsWith('Example:')) {
        activities.push(activity);
      }
    }
    
    return activities;
  }

  extractParallelResearch(content) {
    const research = {
      required: true,
      min_searches: 6 // Default minimum
    };
    
    // Extract number of searches
    const numberMatch = content.match(/(\d+)\+?\s*(?:parallel|simultaneous|concurrent)/i);
    if (numberMatch) {
      research.min_searches = parseInt(numberMatch[1]);
    }
    
    // Extract search topics
    const topicsMatch = content.match(/(?:search|research|investigate|explore).*?:[\s\S]*?(?=\n\n|\n##|$)/i);
    if (topicsMatch) {
      research.search_topics = this.extractActivities(topicsMatch[0]);
    }
    
    // Time estimate
    const timeMatch = content.match(/(\d+(?:-\d+)?)\s*seconds/i);
    if (timeMatch) {
      research.time_estimate = `${timeMatch[1]} seconds`;
    }
    
    return research;
  }

  extractOutputs(content) {
    const outputsMatch = content.match(/(?:outputs?|delivers?|produces?|generates?):[\s\S]*?(?=\n\n|\n##|$)/i);
    if (!outputsMatch) return null;
    
    const outputs = {};
    const items = this.extractActivities(outputsMatch[0]);
    
    items.forEach(item => {
      const [key, value] = item.split(':').map(s => s.trim());
      if (value) {
        outputs[key.toLowerCase().replace(/\s+/g, '_')] = value;
      }
    });
    
    return Object.keys(outputs).length > 0 ? outputs : null;
  }

  extractWorkflow(name, content) {
    const workflow = {};
    
    // Extract next commands
    const nextMatch = content.match(/(?:next|hands?\s*off|continues?\s*to)[:\s]+([a-z-,\s]+)/i);
    if (nextMatch) {
      workflow.next_commands = nextMatch[1].split(/[,\s]+/).filter(cmd => cmd.length > 0);
    }
    
    // Extract prerequisites
    const prereqMatch = content.match(/(?:prerequisites?|requires?|needs?)[:\s]+([a-z-,\s]+)/i);
    if (prereqMatch) {
      workflow.prerequisites = prereqMatch[1].split(/[,\s]+/).filter(cmd => cmd.length > 0);
    }
    
    // Extract handoff deliverables
    const deliverables = this.extractHandoffDeliverables(content);
    if (deliverables.length > 0) {
      workflow.handoff_deliverables = deliverables;
    }
    
    return workflow;
  }

  extractHandoffDeliverables(content) {
    const deliverables = [];
    const handoffSection = content.match(/handoff.*?:[\s\S]*?(?=\n##|\n\n|$)/i);
    
    if (handoffSection) {
      const items = this.extractActivities(handoffSection[0]);
      items.forEach(item => {
        // Convert to snake_case identifier
        const deliverable = item.toLowerCase()
          .replace(/[^\w\s]/g, '')
          .replace(/\s+/g, '_')
          .substring(0, 50); // Limit length
        
        if (deliverable) {
          deliverables.push(deliverable);
        }
      });
    }
    
    return deliverables;
  }

  extractTimeEstimates(content) {
    const estimates = {};
    
    // Total time
    const totalMatch = content.match(/(?:total|overall|entire).*?(\d+(?:-\d+)?)\s*(hours?|minutes?|seconds?)/i);
    if (totalMatch) {
      estimates.total = `${totalMatch[1]} ${totalMatch[2]}`;
    }
    
    // Research time (specifically for parallel execution)
    const researchMatch = content.match(/(?:research|parallel).*?(\d+(?:-\d+)?)\s*seconds/i);
    if (researchMatch) {
      estimates.research = `${researchMatch[1]} seconds`;
    }
    
    return Object.keys(estimates).length > 0 ? estimates : undefined;
  }

  extractAgents(content) {
    const agents = [];
    const agentRegex = /(?:generate|create|spawn).*?([a-z-]+)(?:\s+agent|expert|persona)/gi;
    let match;
    
    while ((match = agentRegex.exec(content))) {
      const agentName = match[1].toLowerCase();
      if (!agents.includes(agentName) && agentName.length > 3) {
        agents.push(agentName);
      }
    }
    
    // Also check for specific agent mentions
    const specificAgents = content.match(/(?:domain-expert|product-manager|code-reviewer|test-engineer|security-engineer)/gi);
    if (specificAgents) {
      specificAgents.forEach(agent => {
        const normalized = agent.toLowerCase();
        if (!agents.includes(normalized)) {
          agents.push(normalized);
        }
      });
    }
    
    return agents.length > 0 ? agents : 'dynamic_based_on_stack';
  }

  extractGlobalRules() {
    // Core rules that apply across all commands
    this.rules.global = {
      parallel_research: {
        id: "RULE_001",
        type: "mandatory",
        description: "ALL research MUST use parallel Task agents",
        enforcement: "CRITICAL_ERROR",
        parameters: {
          min_parallel_agents: 6,
          max_parallel_agents: 10,
          timeout_per_agent: 5000,
          execution_mode: "simultaneous"
        },
        violation_message: "🚨 CRITICAL ERROR: Sequential research execution detected!",
        time_savings: {
          sequential: "30-60 seconds",
          parallel: "5-8 seconds",
          reduction: "75-85%"
        }
      },
      
      slc_validation: {
        id: "RULE_002",
        type: "mandatory",
        description: "All features must pass SLC (Simple, Lovable, Complete) validation",
        criteria: {
          simple: {
            min_score: 4,
            description: "Remove barriers, streamline user experience",
            validation_questions: [
              "Can this be explained in one sentence?",
              "Does this remove complexity rather than add it?",
              "Will new users understand the value within 5 minutes?"
            ]
          },
          lovable: {
            min_score: 4,
            description: "Build products that delight users",
            validation_questions: [
              "Will users genuinely love this?",
              "Does this solve a real pain point?",
              "Would users recommend this to others?"
            ]
          },
          complete: {
            min_score: 4,
            description: "Fully deliver on core promise",
            validation_questions: [
              "Does this fully solve the core problem?",
              "Can users accomplish their main goal end-to-end?",
              "Are there critical gaps in the core workflow?"
            ]
          }
        }
      },
      
      yagni_principle: {
        id: "RULE_003",
        type: "mandatory",
        description: "You Aren't Gonna Need It - No speculative features",
        validation: [
          "Build only what's needed now",
          "Require evidence for new features",
          "No hypothetical future requirements",
          "Incremental complexity only when proven necessary"
        ]
      },
      
      documentation_sync: {
        id: "RULE_004",
        type: "mandatory",
        description: "All outputs must be saved for cross-session continuity",
        requirements: [
          "Save to docs/#/ directory",
          "Update active context",
          "Maintain handoff packages"
        ]
      }
    };
    
    // Quality gates
    this.rules.quality_gates = {
      research: {
        entry: ["current_date_retrieved", "check_shared_research_first"],
        exit: ["min_parallel_agents_met", "results_stored", "time_under_10_seconds"]
      },
      handoff: {
        requirements: ["all_deliverables_present", "validation_passed", "documentation_updated"]
      }
    };
  }

  buildKBStructure() {
    // Build relationships
    const relationships = this.buildRelationships();
    
    // Build execution patterns
    const executionPatterns = {
      parallel_research: {
        protocol: "Create N Task tool invocations in SINGLE response",
        benefits: {
          time_reduction: "75-85%",
          coverage: "comprehensive",
          efficiency: "optimal"
        },
        example_code: "Create 8+ Task tool invocations in a SINGLE response"
      }
    };
    
    // Build modules
    const modules = this.buildModules();
    
    return {
      version: "1.0",
      metadata: {
        description: "Hash Prompts Knowledge Base - Complete command and rules reference",
        generated: new Date().toISOString().split('T')[0],
        total_commands: Object.keys(this.commands).length,
        rules_version: "2.0"
      },
      rules: this.rules,
      commands: this.commands,
      relationships,
      execution_patterns: executionPatterns,
      modules
    };
  }

  buildRelationships() {
    const commandFlow = [];
    const agentGeneration = [];
    
    // Define the standard workflow
    const workflow = [
      {from: "brainstorm", to: "prd"},
      {from: "prd", to: "architect"},
      {from: "architect", to: "tasks"},
      {from: "tasks", to: "plan"},
      {from: "plan", to: "code"},
      {from: "code", to: "test"},
      {from: "test", to: "deploy"},
      {from: "deploy", to: "feature"},
      {from: "feature", to: "plan"}
    ];
    
    workflow.forEach(({from, to}) => {
      commandFlow.push({
        from,
        to,
        type: to === "plan" && from === "feature" ? "handoff" : "handoff"
      });
    });
    
    // Agent generation triggers
    const agentTriggers = {
      prd: ["domain-expert", "product-manager"],
      architect: "dynamic_tech_stack_agents",
      tasks: ["code-reviewer", "test-engineer"]
    };
    
    Object.entries(agentTriggers).forEach(([trigger, generates]) => {
      agentGeneration.push({trigger, generates});
    });
    
    return {
      command_flow: commandFlow,
      agent_generation: agentGeneration
    };
  }

  buildModules() {
    return {
      common: {
        description: "Output management, file persistence, session handling",
        exports: ["save_output", "load_context", "manage_session"]
      },
      research: {
        description: "Parallel search patterns, query templates, caching",
        exports: ["execute_parallel_research", "cache_results"]
      },
      "slc-validation": {
        description: "Complete SLC framework and validation checklists",
        exports: ["validate_slc", "score_feature"]
      },
      "agent-generation": {
        description: "Agent creation functions and color palettes",
        exports: ["generate_agent", "assign_color"]
      },
      handoffs: {
        description: "Stage transitions, quality gates, handoff templates",
        exports: ["validate_handoff", "package_deliverables"]
      }
    };
  }

  async validateKB(kb) {
    console.log('\n🔍 Validating KB structure...');
    
    // Basic structure validation
    const requiredKeys = ['version', 'metadata', 'rules', 'commands'];
    for (const key of requiredKeys) {
      if (!kb[key]) {
        throw new Error(`Missing required key: ${key}`);
      }
    }
    
    // Validate commands
    Object.values(kb.commands).forEach(command => {
      if (!command.name || !command.description || !command.category) {
        throw new Error(`Invalid command structure for ${command.name || 'unknown'}`);
      }
    });
    
    console.log('  ✓ KB structure is valid');
  }

  async saveKB(kb) {
    const json = JSON.stringify(kb, null, 2);
    await fs.writeFile(this.kbPath, json, 'utf8');
    console.log(`\n💾 Saved KB to ${this.kbPath}`);
    console.log(`  Size: ${(json.length / 1024).toFixed(2)} KB`);
  }

  reportChanges(oldKB, newKB) {
    if (!oldKB) {
      console.log('\n📊 KB Statistics:');
      console.log(`  • Commands: ${Object.keys(newKB.commands).length}`);
      console.log(`  • Global Rules: ${Object.keys(newKB.rules.global).length}`);
      console.log(`  • Modules: ${Object.keys(newKB.modules).length}`);
      return;
    }
    
    console.log('\n📊 KB Changes:');
    
    // Compare command counts
    const oldCommands = Object.keys(oldKB.commands || {});
    const newCommands = Object.keys(newKB.commands);
    
    const added = newCommands.filter(cmd => !oldCommands.includes(cmd));
    const removed = oldCommands.filter(cmd => !newCommands.includes(cmd));
    
    if (added.length > 0) {
      console.log(`  • Added commands: ${added.join(', ')}`);
    }
    if (removed.length > 0) {
      console.log(`  • Removed commands: ${removed.join(', ')}`);
    }
    
    // Check for modified commands
    let modified = 0;
    newCommands.forEach(cmd => {
      if (oldCommands.includes(cmd)) {
        const oldCmd = JSON.stringify(oldKB.commands[cmd]);
        const newCmd = JSON.stringify(newKB.commands[cmd]);
        if (oldCmd !== newCmd) {
          modified++;
        }
      }
    });
    
    if (modified > 0) {
      console.log(`  • Modified commands: ${modified}`);
    }
    
    if (added.length === 0 && removed.length === 0 && modified === 0) {
      console.log('  • No changes detected');
    }
  }
}

// Run the generator
if (require.main === module) {
  const generator = new KBGenerator();
  generator.generate().catch(error => {
    console.error('Fatal error:', error);
    process.exit(1);
  });
}

module.exports = KBGenerator;