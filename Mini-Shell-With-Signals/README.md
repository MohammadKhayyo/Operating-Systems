# Mini Shell With Signals

### Authored by: Mohammad Khayyo

---

## Background

The exercise revolves around the design and implementation of a simplified shell. This shell handles commands, piping, and signal-based interactions with a specific focus on the interactions driven by the `SIGTSTP` and `SIGCONT` signals. Typically, these signals correspond to pausing (`^Z`) and resuming (`fg`) processes in a terminal.

---

## Description

The mini shell receives and processes user commands. Its features include:

- Command parsing and execution.
- Support for piping between processes.
- Handling of signals:
  - Pausing a process with `SIGTSTP` (`^Z`).
  - Resuming a paused process with `SIGCONT` (`fg`).

---

## Usage

To utilize the mini shell:

1. **Compilation**:
   ```bash
   gcc ex4.c -o ex4
   ```
2. **Execution**:
   ```bash
   ./ex4
   ```

### Example:

```bash
Input: cat (then press Enter and Ctrl-Z)
Input: fg

Output: running the last suspended process
```

---

## Program Files

- **ex4.c**: Contains the main function and all associated helper functions.
