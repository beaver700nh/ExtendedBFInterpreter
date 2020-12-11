# Extended Brainf*ck Interpreter

## This is in progress!!!

This extension of Brainf*ck supports all the original features, plus more:
* the `!` character starts and ends a comment
* the `:` character jumps to the label identified by the next character, as in
```
! "a" is a label !
a
! code here !
:a
! ":a" jumps to label "a" !
```
* the `~` character reads a line and pushes it backwards by character onto the stack
* the `^` character pushes the current cell onto the stack
* the `v` character pops the top of the stack into the current cell

## Files

### main.cpp
The main file, starts off all C++ processing.

### .replit
Code for "Run" button for use on repl.it

### interpreter.cpp and interpreter.hpp
Core of interpreter

### main
Linux executable for running Brainf*ck programs

### main.sh
Tester and execution evironment for project devs

### README.md
This file (contains info)

### test.bf
A simple "Hello world" test

### testgoto.bf
A program to test `goto`s

### testio.bf
A program to test I/O
