# Resolving a Merge Conflict (Notes)

A quick reference for how I resolved the README.md conflict after merging
`upstream/main` into my fork, plus the alternative resolutions.

## Background

After fetching the original repo I merged its changes into my branch:

```bash
git fetch upstream
git merge upstream/main
```

Most files merged automatically, but `README.md` had a **content conflict**
(the same lines were edited on both sides), so Git paused and asked me to
resolve it manually.

## Steps I Took (accepted the incoming changes)

"Incoming changes" = the branch being merged in (`upstream/main`). In a
**merge**, that side is `--theirs`.

```bash
git checkout --theirs README.md   # take upstream's version of the file
git add README.md                 # mark the conflict as resolved
git commit                        # complete the merge (saves the merge commit)
```

Then I confirmed everything was clean:

```bash
git status                        # should show no more "unmerged paths"
```

## Hypothetical: Rejecting the incoming changes (keep my version)

"Reject incoming / keep mine" = my current branch (HEAD) = `--ours`.

```bash
git checkout --ours README.md     # keep my version of the file
git add README.md
git commit
```

## Cheat Sheet

| Goal                                   | Command                          |
| -------------------------------------- | -------------------------------- |
| Accept **incoming** (upstream's) file  | `git checkout --theirs <file>`   |
| Keep **my** (current branch) file      | `git checkout --ours <file>`     |
| Mark a file resolved                   | `git add <file>`                 |
| Finish the merge                       | `git commit`                     |
| Abort the whole merge (before commit)  | `git merge --abort`              |

## Things to Remember

- `--ours` / `--theirs` are **all-or-nothing per file** — they take the entire
  file from one side. To keep pieces of both, edit the file by hand and delete
  the `<<<<<<<`, `=======`, `>>>>>>>` conflict markers manually.
- The meaning of `--ours` / `--theirs` is **reversed during a `git rebase`**
  compared to a `git merge`. These notes are for a **merge**.
- `git merge --abort` only works before you commit the merge — it's the safe
  "undo, let me start over" button.
