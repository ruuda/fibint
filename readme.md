fibint
======
Compute Fibonacci numbers efficiently using finite fields. This allows for
Fibonacci numbers to be computed from a closed-form expression, by using only
integer arithmetic. For any integer width, this makes it possible to compute
all Fibonacci numbers representable by that integer, without resorting to
floating-point numbers or wider integers.

How it works
------------
Instead of using the closed-form expression for computing the n-th Fibonacci
number in the field of real numbers, it uses an analogous closed-form
expression in a finite field that is big enough to contain the largest
representable Fibonacci number.

See my [blog post](https://ruudvanasseldonk.com/2014/07/01/fibonacci-numbers-in-finite-fields)
for a more thorough explanation.

Licence
-------
This project is an implementation of a mathematical concept. The
implementation is licensed under the MIT license. See the file `copying`.
