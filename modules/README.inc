# Modules Directory

This directory contains reusable components shared across all pipeline modes.

## Available Modules

### common.md
- Output management patterns
- File persistence logic
- Save phase templates
- Session management
- Progress tracking

### research.md
- Parallel search execution patterns
- Research query templates
- Cache integration
- Time-saving strategies
- Mode-specific research patterns

### slc-validation.md
- SLC (Simple, Lovable, Complete) framework
- Scoring system (1-5 scale)
- Feature validation checklists
- Warning signs and violations
- Integration guidelines

### agent-generation.md
- Color palette for agent types
- `generate_color()` function
- `generate_dynamic_agent()` function
- Usage examples
- Standard agent types

### handoffs.md
- Stage transition templates
- Mode-specific handoff formats
- Quality gate checklists
- Pipeline status updates
- Emergency handoff procedures

## How to Use Modules in Mode Files

Modes should reference these modules instead of duplicating content:

```markdown
# MODE_NAME Mode

<!-- Output Management -->
See: modules/common.md#output-management-pattern

<!-- Research Patterns -->
See: modules/research.md#parallel-research-execution

<!-- SLC Validation -->
See: modules/slc-validation.md#feature-validation-checklist

<!-- Agent Generation -->
See: modules/agent-generation.md#generate-dynamic-agent-function

<!-- Handoffs -->
See: modules/handoffs.md#mode-specific-handoffs
```

## Benefits

1. **Single Source of Truth**: Update once, applies everywhere
2. **Smaller Files**: Mode files focus on unique content
3. **Consistency**: Same patterns used across all modes
4. **Maintainability**: Easier to update and improve
5. **Modularity**: Mix and match components as needed

## Module Conventions

- Each module is self-contained
- Modules provide templates and patterns
- Mode files implement module patterns with specific details
- Functions are defined once in modules
- Cross-references use section anchors

## Future Modules

Potential additions:
- `testing.md`: Test patterns and strategies
- `deployment.md`: Deployment configurations
- `monitoring.md`: Observability patterns
- `security.md`: Security checklists