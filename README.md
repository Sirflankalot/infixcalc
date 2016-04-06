# infixcalc
A basic double-based infix calculator that takes commands by argument.

## Backend
Internally, it uses a [Shunting Yard Parser](https://en.wikipedia.org/wiki/Shunting-yard_algorithm) to generate an [Abstract Syntax Tree](https://en.wikipedia.org/wiki/Abstract_syntax_tree), and the head of the tree is called which recurively solves for the answer.

It's numeric representation is a double (64 bit floating point).
