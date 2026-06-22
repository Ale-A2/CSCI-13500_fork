# Git Authentication & Credentials in WSL (Ubuntu)

Notes on setting up GitHub authentication for pushing from **Ubuntu on WSL**, and why the
earlier push attempts failed.

---

## The problems we hit

When pushing over HTTPS from WSL, two separate errors showed up:

```
remote: Permission to Ale-A2/CSCI-13500_fork.git denied to Ale-A2.
fatal: ... The requested URL returned error: 403
```
and on the next try:
```
remote: Invalid username or token. Password authentication is not supported for Git operations.
fatal: Authentication failed ...
```

**The repo URL was fine.** Both errors were about *authentication*, not the URL.

### Cause 1 — Password authentication is dead
GitHub disabled account-password authentication for git in **August 2021**. When git prompts:

```
Password for 'https://Ale-A2@github.com':
```

it is **not** asking for your GitHub login password. It wants a **Personal Access Token (PAT)**.
Typing the real password always fails with *"Password authentication is not supported."*

### Cause 2 — A stale stored credential (the 403)
WSL git was using the **`store`** credential helper, which keeps credentials in **plaintext** at
`~/.git-credentials`. That file held an **old/wrong token**, so git kept resending it and GitHub
returned **403** (authenticated, but not authorized to write to that repo).

---

## How `store` vs Git Credential Manager differ

| | `store` (old) | Git Credential Manager (new) |
|---|---|---|
| Where creds live | plaintext `~/.git-credentials` | encrypted Windows Credential Manager |
| How you authenticate | manually type username + PAT | browser sign-in (once) |
| When it prompts | every time the file lacks a match | only first time / when token expires |
| Bad token behavior | resends it → 403 forever | refreshes automatically |

---

## The fix we applied

We switched WSL to use the **Windows Git Credential Manager (GCM)**, which is already installed
with Git for Windows. It stores credentials securely and uses a one-time browser login.

```bash
# 1. Remove the stale plaintext credential file (this caused the 403)
rm -f ~/.git-credentials

# 2. Point WSL git at the Windows GCM executable
git config --global credential.helper "/mnt/c/Program\ Files/Git/mingw64/bin/git-credential-manager.exe"

# 3. Verify
git config --global credential.helper
# -> /mnt/c/Program\ Files/Git/mingw64/bin/git-credential-manager.exe
```

> Note: the path above is the default install location for Git for Windows. If Git is installed
> elsewhere, adjust the path accordingly.

---

## Using it

```bash
git push origin main
```

- The **first** push opens a **browser window** to sign in to GitHub and authorize.
  - Sign in as the account that **owns the fork** (`Ale-A2`). Signing in as a different account
    gives you the `403 denied` error again.
  - If no browser opens, GCM prints a URL/code in the terminal — follow it.
- Every push **after that is silent** — GCM reuses the saved token until it expires, then
  re-opens the browser automatically. You never type a username or PAT by hand.

---

## Alternative: PAT + `store` (simpler, less secure)

If you ever can't use GCM, you can stick with a manually created token:

1. Create a token at <https://github.com/settings/tokens> (classic), with the **`repo`** scope.
2. On the next push prompt, enter your username and paste the **token as the password**.
3. With `credential.helper store`, it's saved to `~/.git-credentials` (plaintext) so you aren't
   prompted again.

This works but keeps the token unencrypted on disk — GCM is preferred.

---

## Quick reference

```bash
# Which helper is WSL git using?
git config --global credential.helper

# Clear a stale plaintext credential
rm -f ~/.git-credentials

# Check remotes (URL sanity check)
git remote -v
```

Windows-side credentials can be viewed/removed in:
**Control Panel → Credential Manager → Windows Credentials** (look for `git:https://github.com`).
