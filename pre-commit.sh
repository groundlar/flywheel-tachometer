#!/bin/sh

# Called by "git commit" with no arguments.  The hook should
# exit with non-zero status after issuing an appropriate message if
# it wants to stop the commit.

set -euo pipefail

# If there are whitespace errors, print the offending file names and fail.
exec git diff-index --check --cached $against --

git commit --no-verify -m 'Save index'
old_stash=$(git rev-parse -q --verify refs/stash)
git stash push -m 'Unstaged changes'
new_stash=$(git rev-parse -q --verify refs/stash)
git reset --soft HEAD^

# format staged changes
for file in `git diff --cached --name-only --diff-filter=ACMR`; do
  clang-format -i "${file}"
done

git add -u
if [ "$old_stash" != "$new_stash" ]; then # if unstaged changes were stashed reapply to working tree
    git stash pop
fi
exit 0

