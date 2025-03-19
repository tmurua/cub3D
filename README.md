# cub3D

## Git Collaboration & Workflow

**Commit Prefixes:**
- `feat:` for new features and major functionalities.
- `fix:` for bug fixes or corrections.
- `docs:` for documentation updates.
- `style:` for code style improvements and refactoring.

### Git Workflow

1. **Create a New Branch:**
    ```bash
    git checkout -b branch-name
    ```

2. **Push New Branch to GitHub:**
    ```bash
    git push -u origin branch-name
    ```

3. **Stay Updated with Main Branch:**
    ```bash
    git checkout main
    git pull
    git checkout branch-name
    git merge main
    ```

4. **Merge Branch into Main:**
    ```bash
    git checkout main
    git merge branch-name
    git push
    ```

5. **Delete a Branch:**
    ```bash
    git branch -d branch-name
    git push origin --delete branch-name
    ```

- **Resolve Conflicts:**
  In case of merge conflicts, resolve them manually by editing the affected files, then add and commit the changes.
