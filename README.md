# Custom Game of Life – C Implementation

Custom cellular automaton inspired by Conway’s Game of Life, implemented in C.

## Overview

This project implements a modified version of the Game of Life with different evolution rules:

- Dead cells remain dead (no spontaneous birth).
- Living cells update their life counter using the sum of their neighbors.
- A living cell dies if its updated life counter strictly exceeds a given threshold.
- Surviving cells can optionally increment or decrement their life counter.

The simulation runs on a square grid of variable size.


## Key Differences from Classic Conway's Game of Life

Unlike the classical version:

- There is no birth rule for dead cells.
- Each cell maintains a life counter.
- A threshold rule determines survival.
- Border and corner cells are handled explicitly.
- The simulation can stop due to:
  - Total extinction
  - Invariance (no state change)
  - Maximum iteration reached

---

## Technical Concepts Used

- Variable-length 2D arrays (VLA)
- Grid simulation
- Separation between current and next generation
- Boundary case handling (corners, edges, interior)
- Population extinction detection
- Invariance detection
- Structured modular functions
- Iterative evolution logic

---

## Program Flow

1. Read grid size, threshold and number of iterations.
2. Load initial grid from input.
3. Simulate evolution step by step.
4. Stop when:
   - Population extinction
   - Invariance detected
   - Maximum iterations reached

---

## Termination Conditions

The program stops when:

- All cells are dead.
- The grid becomes invariant (no change between two generations).
- The specified number of iterations is reached.

---

## Author

Ilyes Belgacem  
Bachelor Data Science & Network Security – ESIEE-IT
