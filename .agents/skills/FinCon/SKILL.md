```markdown
# FinCon Development Patterns

> Auto-generated skill from repository analysis

## Overview
This skill teaches the core development patterns and conventions used in the FinCon TypeScript codebase. You'll learn how to structure files, write code, commit changes, and write tests in a way that aligns with the project's standards. This guide is ideal for new contributors or anyone seeking to maintain consistency across the repository.

## Coding Conventions

### File Naming
- **Pattern:** PascalCase
- **Example:**  
  `UserProfile.ts`  
  `TransactionService.ts`

### Import Style
- **Pattern:** Relative imports
- **Example:**
  ```typescript
  import { TransactionService } from './TransactionService';
  ```

### Export Style
- **Pattern:** Named exports
- **Example:**
  ```typescript
  // In TransactionService.ts
  export function processTransaction() { ... }
  ```

### Commit Messages
- **Style:** Conventional commits
- **Allowed Prefixes:** `feat`
- **Average Length:** ~47 characters
- **Example:**
  ```
  feat: add user authentication to login flow
  ```

## Workflows

### Feature Development
**Trigger:** When adding a new feature  
**Command:** `/feature-development`

1. Create a new TypeScript file using PascalCase.
2. Implement the feature using named exports.
3. Use relative imports for dependencies.
4. Write or update corresponding test files (`*.test.ts`).
5. Commit changes using the conventional commit format with the `feat` prefix.

### Writing Tests
**Trigger:** When adding or updating tests  
**Command:** `/write-tests`

1. Create a test file with the `.test.` infix (e.g., `UserProfile.test.ts`).
2. Write test cases for your feature or module.
3. Use the project's preferred (unknown) testing framework.
4. Run tests to ensure correctness.

## Testing Patterns

- **Test File Naming:**  
  Use the `.test.` infix in filenames, e.g., `TransactionService.test.ts`.
- **Testing Framework:**  
  Not specified; check existing tests for framework usage.
- **Example Test File:**
  ```typescript
  // TransactionService.test.ts
  import { processTransaction } from './TransactionService';

  describe('processTransaction', () => {
    it('should process a valid transaction', () => {
      // test implementation
    });
  });
  ```

## Commands
| Command               | Purpose                                   |
|-----------------------|-------------------------------------------|
| /feature-development  | Guide for adding a new feature            |
| /write-tests          | Steps for writing and organizing tests    |
```
