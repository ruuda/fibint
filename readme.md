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

I will publish a blog post with a thorough explanation shortly.
