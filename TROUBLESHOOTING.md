# Hash Prompts Troubleshooting Guide

## Common Issues and Solutions

### 1. Commands Not Recognized

**Problem**: When typing `/#:pipeline start`, Claude tries to execute bash commands instead of recognizing it as a command.

**Symptoms**:
```
● Bash(source modules/kb-helpers.inc && kb_init_project . && echo "KB initialized")
  ⎿  Error: (eval):source:1: no such file or directory: modules/kb-helpers.inc
```

**Solutions**:

1. **Verify you're using Claude Code** (not regular Claude):
   - Claude Code is required for custom commands to work
   - Visit https://claude.ai/code to access Claude Code

2. **Check installation**:
   ```bash
   ./verify-installation.sh
   ```

3. **Fix installation if needed**:
   ```bash
   ./fix-installation.sh
   ```

4. **Try in a new conversation**:
   - Sometimes Claude needs a fresh context to recognize newly installed commands
   - Start a new conversation and try the command again

### 2. Installation Issues

**Problem**: Commands aren't installing properly

**Solutions**:

1. **Run the installer with explicit location**:
   ```bash
   # For global installation (recommended)
   curl -sSL https://raw.githubusercontent.com/dimitritholen/hash-prompts/feature/kb/scripts/install.sh | bash -s -- --global
   
   # For local installation
   curl -sSL https://raw.githubusercontent.com/dimitritholen/hash-prompts/feature/kb/scripts/install.sh | bash -s -- --local
   ```

2. **Check Claude CLI is installed**:
   ```bash
   claude --version
   ```
   If not installed, visit: https://claude.ai/code

3. **Verify installation directories**:
   - Global: `~/.claude/commands/#/`
   - Local: `./.claude/commands/#/`

### 3. Module Not Found Errors

**Problem**: Getting errors like "modules/kb-helpers.inc not found"

**Cause**: The implementation code is trying to run in your project directory instead of the Claude commands directory.

**Solutions**:

1. **Ensure proper command format** - Commands should have this header:
   ```markdown
   # /#:commandname Command
   
   This command activates the commandname mode for your AI assistant.
   
   Usage: /#:commandname $ARGUMENTS
   
   ---
   ```

2. **Fix command files**:
   ```bash
   ./fix-installation.sh
   ```

### 4. KB System Issues

**Problem**: Knowledge Base not initializing properly

**Solutions**:

1. **Check KB file permissions**:
   ```bash
   ls -la .hash/
   ```

2. **Initialize KB manually**:
   ```bash
   mkdir -p .hash
   touch .hash/project.kb.json
   ```

3. **Check for jq installation** (required for KB operations):
   ```bash
   which jq || echo "jq not installed"
   ```

### 5. Commands Work But No Output

**Problem**: Commands seem to run but produce no visible output

**Solutions**:

1. **Check quiet mode isn't enabled**:
   - Don't use `--quiet` or `-q` flags unless you want minimal output

2. **Try verbose mode**:
   ```
   /#:pipeline start --verbose
   ```

## How Claude Commands Work

Understanding how Claude commands work can help with troubleshooting:

1. **Command Recognition**: When you type `/#:commandname`, Claude looks for a file at:
   - `~/.claude/commands/#/commandname.md` (global)
   - `./.claude/commands/#/commandname.md` (local)

2. **Command Execution**: Claude reads the markdown file and follows the instructions within it.

3. **Module Loading**: Commands can reference modules using paths relative to the command directory:
   ```bash
   source modules/kb-helpers.inc  # Looks in ~/.claude/commands/#/modules/
   ```

## Manual Installation

If automated installation fails, you can install manually:

1. **Create directories**:
   ```bash
   mkdir -p ~/.claude/commands/#/modules
   mkdir -p ~/.claude/commands/#/kb/schemas
   ```

2. **Download commands** (example for pipeline.md):
   ```bash
   curl -sSL https://raw.githubusercontent.com/dimitritholen/hash-prompts/feature/kb/pipeline.md \
     -o ~/.claude/commands/#/pipeline.md
   ```

3. **Add command header** to each .md file:
   ```bash
   # /#:pipeline Command
   
   This command activates the pipeline mode for your AI assistant.
   
   Usage: /#:pipeline $ARGUMENTS
   
   ---
   
   [Original content here]
   ```

## Testing Commands

Test if commands are working:

1. **Simple test**:
   ```
   /#:help
   ```

2. **Pipeline test**:
   ```
   /#:pipeline help
   ```

3. **Project test**:
   ```
   /#:project
   ```

## Getting Help

If issues persist:

1. **Check GitHub Issues**: https://github.com/dimitritholen/hash-prompts/issues
2. **Report new issues** with:
   - Your OS and shell
   - Output of `./verify-installation.sh`
   - The exact error message
   - What command you're trying to run

## Debug Mode

For detailed debugging:

```bash
DEBUG=1 ./verify-installation.sh
```

This will show additional information about paths and configurations.