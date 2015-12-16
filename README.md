# CCompiler
A simple compiler which can map a subset of c source code into mips assembly. 

## Description
* Lexical, syntax, and semantic error handling
* Declaration of constants, variables, arrays (3D and more!)
* Code for assignments
* If and while loops
* Array accesses and operations
* Functions and recursion (limited)
* Do-while loops
* Print syscalls

## Installation
* flex and bison to scan and parse a given source code
* Mars to execute a generated MIPS code
* Graphviz to build an AST image

## Usage
Compile:
```
> make
```
Run:
```
> ./compiler [flags] [source_filename]
```

Command line flags:
* -d[slp]         : follow d with s, l, and/or p to toggle Symbol Tabel, Lexical, and Parser debugging
* -c              : compile and assemble (not implemented yet)
* -a              : generate intermediate Abstract Symbol Tree code (AST)
* -q              : generate intermediate 3 Address Code (3AC)
* -S              : generate assembly (MIPS)

## Authors
* Yuta Miyake
* Niki Silveria
* David Vaughan
* Aaron Whitehead
