# Pascal-like Language Parsers

Parsers for a simplified Pascal-like language, developed as part of a Programming Languages course.

The same general grammar was explored using C, Common Lisp, Prolog, and Java. Each version demonstrates how a parser can be expressed using the programming model and language features of its implementation language.

## C

### What's implemented

* Lexical analysis that converts the source input into tokens
* A recursive descent parser for:

  * Program headers
  * Variable declarations
  * Statement blocks
  * Assignment statements
  * Arithmetic expressions
  * Program termination
* Separate parsing functions corresponding to grammar productions
* Lookahead-token handling
* A symbol table for declared identifiers
* Detection of duplicate declarations
* Detection of undeclared identifiers
* Syntax- and semantic-error reporting

### What I learned

* How to manually implement a lexer and recursive descent parser in C
* How grammar productions translate into parsing functions
* How a parser consumes tokens using lookahead
* How structures can represent tokens, symbols, and parser state
* How symbol tables support semantic analysis
* The difference between lexical, syntax, and semantic analysis
* How the lexer, parser, and symbol table form a compiler front-end

## Common Lisp

This implementation was completed from supplied skeleton code. The starter code already provided much of the reader and lexer framework, parser-state representation, token advancement, error functions, and file-parsing infrastructure.

### Provided starter code

* Helper functions for reading and constructing lexemes
* Character-based input processing
* Recognition of names, numbers, symbols, and whitespace
* Support for reading single-character symbols and the `:=` operator
* The parser-state structure
* Parser-state initialization
* Token advancement through `get-token`
* The general token-matching function
* Syntax- and semantic-error reporting functions
* The top-level parsing and result-reporting framework
* Grammar descriptions and placeholders for the missing parser functions

### What I completed

* Mapping lexemes to their corresponding token types
* Recognition and validation of identifiers
* Recognition and validation of integer literals
* Accessor functions for the current token and lexeme
* Symbol-table insertion and lookup
* Recursive descent functions for:

  * Program headers
  * Variable declarations
  * Identifier lists
  * Type declarations
  * Statement blocks
  * Statement lists
  * Assignments
  * Expressions
  * Terms
  * Factors
  * Operands
* Operator precedence through separate expression, term, and factor functions
* Detection of duplicate declarations
* Detection of undeclared identifiers
* Checking for unexpected input after the end of a program
* Automatic execution of the parser against all Pascal test files in a directory

### What I learned

* How an existing parser framework can be completed from grammar specifications
* How grammar productions translate into recursive Lisp functions
* How recursion can replace conventional loops
* How Lisp lists can represent tokens and symbol tables
* How `defstruct` can represent shared parser state
* How `setf` is used to update parser state
* How a lexer maps raw lexemes into symbolic token types
* How syntax checking and semantic checking can be added to a parser
* How a recursive descent parser maintains operator precedence

## Prolog

This implementation was also based on supplied starter code. The starter grammar already contained the program rule, a program-header rule, a small example identifier rule, placeholders for the remaining grammar, and examples for testing grammar productions.

The completed parser also uses an adapted file-reading implementation based on code from *Programming in Prolog* by Clocksin and Mellish. **The reader is NOT an original implementation.**

### Provided starter code

* The top-level `program` DCG rule
* A basic program-header grammar
* An example identifier rule
* Placeholders for variable declarations and statement parsing
* Bottom-up examples for testing individual grammar rules
* Example tests for the program header and complete program grammar

### What I completed

* Integration of the file reader, lexer, and parser stages
* Token-code mappings for:

  * Keywords
  * Identifiers
  * Integer literals
  * Operators
  * Delimiters
  * The `:=` assignment operator
* Definite Clause Grammar rules for:

  * Variable declarations
  * Lists of variable declarations
  * Identifier lists
  * Integer, real, and Boolean types
  * Statement blocks
  * Statement lists
  * Assignment statements
  * Arithmetic expressions
  * Terms
  * Factors
  * Parenthesized expressions
* Operator precedence through expression, term, and factor rules
* Parse-success and parse-failure reporting
* Processing multiple Pascal test files
* Writing the test results to an output file

### What I learned

* How Definite Clause Grammars represent grammar productions
* How Prolog lists can represent lexeme and token streams
* How unification matches tokens against grammar rules
* How recursion is used to process repeated grammar structures
* How backtracking allows Prolog to test alternative productions
* How a declarative parser differs from an imperative recursive descent parser
* How reader, lexer, and parser stages can be connected
* How grammar rules can be tested individually before testing complete programs

## Java

The Java version is a separate implementation of the Pascal-like language using object-oriented design.

### What's implemented

* Reading source code from standard input using Java readers

* Support for input redirection:

  ```bash
  java ParserMain < testok1.pas
  ```

* A lexer that recognizes:

  * Identifiers
  * Integer literals
  * Keywords
  * Operators
  * Delimiters

* Immutable tokens represented with a Java record

* Token categories, data types, and symbol roles represented with enums

* A lookup table for single-character symbols

* A recursive descent parser with separate methods for grammar productions

* Lookahead-token handling

* Parsing of:

  * Program headers
  * Variable declarations
  * Statement blocks
  * Assignments
  * Arithmetic expressions
  * Parenthesized expressions

* Operator precedence through expression, term, and factor methods

* A symbol table implemented using `LinkedHashMap`

* Preservation of symbol declaration order

* Detection of duplicate declarations

* Detection of undeclared identifiers

* Tracking of each symbol's:

  * Name
  * Role
  * Type
  * Storage size
  * Address

* Assignment of types to groups of declared variables

* Calculation of required static storage

* An operator table for determining expression result types

* Type compatibility checking for integer and real operands

* Formatted symbol-table output

### What I learned

* How to build a lexer and recursive descent parser using Java classes
* How to read redirected standard input using `System.in`
* How Java records reduce boilerplate for immutable data
* How enums represent fixed language concepts
* How static initializer blocks construct shared lookup tables
* How to use `HashMap` and `LinkedHashMap`
* How to use `HashMaps` for token and symbol lookup
* How to separate lexer, parser, symbol-table, and type-checking responsibilities
* How to perform semantic type checking using an operator table
  
## Concepts demonstrated

Across the implementations, the project demonstrates:

* Lexical analysis
* Token generation
* Recursive descent parsing
* Definite Clause Grammar parsing
* Lookahead-token handling
* Grammar production implementation
* Operator precedence
* Symbol-table management
* Syntax checking
* Semantic checking
* Type compatibility
* Static storage calculation
* Automated parser testing using bash

## Tech stack

* C
* Common Lisp
* Prolog
* Java

