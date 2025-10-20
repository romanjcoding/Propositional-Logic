# Propositional-Logic
A connective is functionally complete if it can be composed to express all possible 2D truth tables. The prototypical examples of 2-ary (two paramater) connectives which are functionally complete are NAND and NOR. In the N-ary case, necessary and sufficient conditions for functional completeness are given by Post's theorem, outlined below.

Let `B = {0,1}`, and `f: B^n → B`. Then, `f` is functionally complete if none of the following hold:

1. `f(1, 1, ..., 1) = 1`
2. `f(0, 0, ..., 0) = 0`
3. `f(x_1, x_2, ... x_n) = ¬f(¬x_1, ¬x_2, ... ¬x_n)`, where `¬x_i = 1 - x_i`
4. `f` is monotonic with respect to the partial order `⪯`, where `(x_1, x_2, ... x_n) ⪯ (y_1, y_2, ... y_n)` if `x_i <= y_i`.
5. `f` is linear, and can be expressed as `f(x_1, x_2, ... x_n) = a_0 + a_1x_1 + ... + a_nx_n; a_i ∈ {0,1}`