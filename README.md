# 🧮 Arbitrary Precision Calculator (APC) in C

## 📌 Overview

This project implements an **Arbitrary Precision Calculator (APC)** using the C programming language.

Unlike standard arithmetic operations that are limited by built-in data types such as `int`, `long`, or `long long`, this calculator can perform arithmetic on numbers of virtually any size.

The project uses **Linked Lists** to store and manipulate large numbers digit by digit, allowing operations on numbers containing hundreds or thousands of digits.

---

## 🚀 Features

- Addition of large numbers
- Subtraction of large numbers
- Multiplication of large numbers
- Division of large numbers
- Modulo operation
- Supports numbers beyond standard datatype limits
- Command-line arithmetic operations

---

## 🛠️ Technologies Used

- C Programming
- Linked Lists
- Dynamic Memory Management
- Mathematical Algorithms
- Modular Programming

---

## ⚙️ How to Run

### Compile

```bash
gcc *.c -o apc
```

### Run

Execute the program by passing two numbers and an arithmetic operator as command-line arguments.

```bash
./apc 123 + 123
```

**Example commands:**

```bash
./apc 123456789123456789 + 987654321987654321
./apc 500 - 250
./apc 12345 x 6789
./apc 1000 / 25
./apc 100 % 7
```

> **Note:** Quote `*` as `'*'` to prevent the shell from interpreting it as a wildcard. If your executable is named `a.out`, use `./a.out` instead of `./apc`.

---

## 🎯 Concepts Practiced

- Linked Lists
- Dynamic Memory Allocation
- Big Integer Arithmetic
- Data Structure Design
- Algorithm Development
- Memory Management
- Command-Line Argument Handling (`argc` and `argv`)

---

## 👨‍💻 Author

Aditya Gupta
