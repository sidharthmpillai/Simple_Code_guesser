# Mastermind – Code Guessing Game

A simple code-guessing game developed using C.

## How to Play
- The computer generates a secret 4-digit code.
- Each digit is unique.
- You have 8 attempts to guess the code.
- **Exact match:** Correct digit in the correct position.
- **Wrong-position match:** Correct digit in the wrong position.
- Enter `H` to get one hint per game.
- You can choose to play again after each game.

## Features
- Random secret code generation
- Input validation
- Exact and wrong-position match checking
- Hint option
- Replay option

## Project Structure
```text
Mastermind/
├── main.c
├── game.c
├── game.h
└── README.md
```

## How to Run

Compile:
```bash
gcc main.c game.c -o mastermind
```

Run:
```bash
./mastermind
```

## Concepts Used
- C functions
- Arrays and strings
- Pointers
- Loops and conditional statements
- Random number generation

