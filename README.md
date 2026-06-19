# Circuit Analyzer

CSE231s – Computer Programming

---

## Project Description

Circuit Analyzer is a C++ program that calculates the equivalent resistance of electrical circuits containing series and parallel resistor connections.

The circuit is provided as a single string description using:

* `S` or `s` for Series connections
* `P` or `p` for Parallel connections
* `e` to mark the end of a connection

The program validates the input, evaluates nested connections from the innermost level outward, and outputs the total equivalent resistance.

---

## Features

* Supports Series and Parallel resistor networks
* Supports nested circuit descriptions
* Accepts integer and decimal resistor values
* Detects invalid circuit descriptions
* Calculates equivalent resistance automatically
* Handles up to 20 connections and up to 20 resistors per connection

---

## Error Handling

The program validates the circuit description before performing any calculations.

It checks for:

* Invalid starting characters (the description must begin with `S`, `s`, `P`, or `p`)
* Invalid characters in the input
* Missing or extra `e` terminators
* More than 20 connections in a circuit
* Invalid resistor values containing multiple decimal points
* Series connections containing fewer than 1 resistor
* Parallel connections containing fewer than 2 resistors
* More than 20 resistors within a single connection

If an invalid description is detected, the program terminates and displays an appropriate error message.

---

## Circuit Description Format

### Series Connection

Input:

S 10 20 30 e

Calculation:

10 + 20 + 30 = 60 Ω

---

### Parallel Connection

Input:

P 10 20 e

Calculation:

1 / (1/10 + 1/20) = 6.67 Ω

---

### Nested Connection

Input:

S 10 P 20 30 e 40 e

Calculation:

10 + (20 || 30) + 40

Equivalent Resistance = 62 Ω

---

## Example

Input:

S 10 P 20 30 e 40 e

Output:

The total resistance = 62 ohm

---

## How to Compile

Using g++:

```bash
g++ main.cpp -o CircuitAnalyzer
```

---

## How to Run

```bash
./CircuitAnalyzer
```

Example:

```text
Enter the circuit description: S 10 P 20 30 e 40 e
The total resistance = 62 ohm
```

---

## Author

Abdelrahman Khaled Aboellel
