#!/bin/sh

# Called by "git commit" with no arguments.  The hook should
# exit with non-zero status after issuing an appropriate message if
# it wants to stop the commit.

set -uo pipefail

git commit --no-verify -m 'Save index'
old_stash=$(git rev-parse -q --verify refs/stash)
git stash push -m 'Unstaged changes'
new_stash=$(git rev-parse -q --verify refs/stash)
git reset --soft HEAD^

# Format all files. No mercy.
clang-format -i $(find . -type f -name "*.cc" -o -name "*.h")

git add -u
if [ "$old_stash" != "$new_stash" ]; then # if unstaged changes were stashed reapply to working tree
    git stash pop
fi
exit 0

# If there are whitespace errors, print the offending file names and fail.
if git rev-parse --verify HEAD >/dev/null 2>&1
then
	against=HEAD
else
	# Initial commit: diff against an empty tree object
	against=$(git hash-object -t tree /dev/null)
fi
exec git diff-index --check --cached $against --
