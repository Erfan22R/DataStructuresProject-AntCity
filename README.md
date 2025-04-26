# DataStructuresProject-AntCity

This project implements an **encoding** and **decoding** system for managing the birth process of ants in a fictional city of ants.  
It was developed as a **full project for the Data Structures course**, not just a simple exercise.

## Problem Description

In the city of ants, each ant's body structure is represented by a string of English letters (similar to DNA in humans). There are two types of ants:
- **Queens** (mothers)
- **Workers** (fathers)

During the reproduction period:
- If a **substring** of a worker matches a **prefix** of a queen, a new baby ant is born with that substring as its body string.
- Newborn ants, along with some **foreign ants** (intruders that do not match any parent), form a queue to enter the city.

The **city gatekeeper** has two tasks:
1. Identify and remove foreign ants from the queue.
2. Save the order of the newborn ants efficiently in a file.

The main challenge is not just to correctly filter the ants, but also to **minimize the size** of the saved file (`order`).

## Project Components

- `encoder.cpp`:
  - Reads the list of queens and workers from the file `parents.txt`.
  - Reads the input queue of ants from the standard input.
  - Filters out the foreign ants.
  - Saves the sequence of newborn ants efficiently into the file `order`.

- `decoder.cpp`:
  - Reads `parents.txt` and `order`.
  - Reconstructs and outputs the exact sequence of the newborn ants to the standard output.

## Input and Output Details

- **`parents.txt`**:
  - First line: number of queens and workers.
  - Following lines: first the list of queens, then the list of workers (each on a separate line).

- **Encoder Standard Input**:
  - First line: the length of the input queue.
  - Next lines: the body string of each ant.

- **`order` File**:
  - Can have any format.
  - The content of this file is not evaluated directly; only the correctness and size minimization are important.

- **Decoder Standard Output**:
  - Prints the newborn ants in the exact original order, each on a separate line.

## Requirements

- C++11 or later
- A standard C++ compiler (e.g., `g++`, `clang++`)

## Notes

- This project was completed as a main project for the Data Structures course.
- The goal is to ensure **algorithmic correctness** while also **optimizing storage size** for the output file.
