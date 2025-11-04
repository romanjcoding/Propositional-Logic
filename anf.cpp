#include "anf.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdint>

uint64_t anf_divide_and_conquer(uint64_t t, unsigned arity) {
    // Masks for the lower half of each 2^(s+1)-sized block.
    static constexpr uint64_t M[6] = {
        0x5555555555555555ULL, // s=0 : 01 pattern (lower 1 of every 2)
        0x3333333333333333ULL, // s=1 : 0011 pattern (lower 2 of every 4)
        0x0F0F0F0F0F0F0F0FULL, // s=2 : 00001111 ...
        0x00FF00FF00FF00FFULL, // s=3 : bytes
        0x0000FFFF0000FFFFULL, // s=4 : 16-bit chunks
        0x00000000FFFFFFFFULL  // s=5 : 32-bit halves
    };

    for (unsigned s = 0; s < arity; ++s) {
        const uint64_t half = 1ULL << s;       // distance to partner within block
        // For each block, update the upper half: upper ^= lower.
        t ^= (t & M[s]) << half;
    }
    return t;
}

void print_anf(const std::vector<uint8_t>& coeffs) {
    bool first = true;
    for (size_t mask = 0; mask < coeffs.size(); mask++) {
        if (!coeffs[mask]) continue;

        std::ostringstream term;
        if (mask == 0) {
            term << "1";
        } else {
            size_t tmp { mask };
            size_t bit { 0 };
            while (tmp) {
                if (tmp & 1u) {
                    term << "x" << bit;
                }
                tmp >>= 1;
                ++bit;
            }
        }
        if (!first) std::cout << " ⊕ ";
        std::cout << term.str();
        first = false;
    }
    if (first) std::cout << "0";
    std::cout << "\n";
}