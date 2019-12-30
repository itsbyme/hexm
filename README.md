# HEXM
## Introduction

`hexm` is an esoteric programming inspired by `machine code` and `brainfuck`.

The `hexm` interpreter has only 5 instruction: 
	* allocating space for a new 2-byte number
	* changing the index of current use number
	* addition
	* input
	* output
but the last 2 are not completed yet.

code on `hexm` language should not contain empty lines.

## Building 

`hexm` requires only make utility and GNU C Compiler to build the interpreter. So you only need to pass next command to your terminal

	make

It will automatically compile object files, build `hexm` interpreter and clean
object files.

## Examples

The `example/` directory contain some `hexm` programs.
