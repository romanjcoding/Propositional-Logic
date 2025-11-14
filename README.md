# Propositional-Logic
## Background
A connective is functionally complete if it can be composed to express all possible 2D truth tables. The prototypical examples of 2-ary (two paramater) connectives which are functionally complete are NAND and NOR. In the N-ary case, necessary and sufficient conditions for functional completeness are given by Post's theorem, outlined below.

Let $`B = \{0,1\}`$, and $f: B^n \to B$. Then, $f$ is functionally complete if none of the following conditions hold:

1. $f(1, 1, ..., 1) = 1$
2. $f(0, 0, ..., 0) = 0$
3. $f(x_1, x_2, ... x_n) = \neg f(\neg x_1, \neg x_2, ... \neg x_n)$
4. $f$ is monotonic with respect to the partial order ⪯, where $(x_1, x_2, ... x_n) ⪯ (y_1, y_2, ... y_n)$ iff $x_i <= y_i$.
5. $f$ is affine, i.e., can be expressed as $f(x_1, x_2, ... x_n) = a_0 + a_1x_1 + ... + a_nx_n$, $a_i \in B$

The first four conditions are relatively quick to preform. Thus, the bulk of our focus is on determining whether or not $f$ is affine. This is done by efficiently generating the Algebraic Normal Form through a divide-and-conquer butterfly algorithm of $f$ as outlined in [this paper](https://www.sciencedirect.com/science/article/pii/S0304397519307674), and checking that degree of $f$ is equal to 1.

## Build
