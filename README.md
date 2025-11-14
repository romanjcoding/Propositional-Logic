# Propositional-Logic
## Background
A Boolean connective is *functionally complete* if compositions of itself can express all possible truth tables. The prototypical examples of *2-ary* (two parameter) connectives which are functionally complete are NAND and NOR. In the *N-ary* case, necessary and sufficient conditions for functional completeness are given by Post's theorem, outlined below.

Let $`B = \{0,1\}`$, and $f: B^n \to B$. Then, $f$ is functionally complete if none of the following conditions hold:

1. $f(1, 1, ..., 1) = 1$
2. $f(0, 0, ..., 0) = 0$
3. $f(x_1, x_2, ... x_n) = \neg f(\neg x_1, \neg x_2, ... \neg x_n)$
4. $f$ is monotonic with respect to the partial order ⪯, where $(x_1, x_2, ... x_n) ⪯ (y_1, y_2, ... y_n)$ iff $x_i <= y_i$.
5. $f$ is affine, i.e., can be expressed as $f(x_1, \dots, x_n) = a_0 \oplus a_1 x_1 \oplus \cdots \oplus a_n x_n,\quad a_i \in B$, where $\oplus$ denotes addition mod 2.

The first four conditions are relatively quick to preform. Thus, the bulk of the work is determining whether or not $f$ is affine. This is done by efficiently generating the Algebraic Normal Form (ANF) via a divide-and-conquer butterfly algorithm of $f$ as outlined in [this paper](https://www.sciencedirect.com/science/article/pii/S0304397519307674), and checking that degree of $f$ is equal to 1.

For arity $n<6$, truth-tables are packed into `uint64_t's` for efficient access and modification through bitshifts. Larger truth-tables are packed into `std::vector<uint64_t>`.

## Build
This project uses CMake.

```bash
# Clone the repository
git clone https://github.com/romanjcoding/Propositional-Logic.git
cd Propositional-Logic

# Configure and build
mkdir build
cd build
cmake ..
cmake --build .
