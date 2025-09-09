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
description: "Think hardest plan mode"
---
Git commit in logically grouped atomic commits. 

**DO NOT COMMIT CLAUDE.md**

Use the industry standard format:

<format>[type] [optional scope]: [description]

[optional body]

[optional footer(s)]
</format>

<example>feat(parser): add ability to parse arrays

Allows users to provide array input in config files.
Handles edge cases with empty arrays.

BREAKING CHANGE: config files with single values must be wrapped in arrays.
</example>