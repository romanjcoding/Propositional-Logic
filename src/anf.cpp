#include "anf.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdint>

uint64_t anf_divide_and_conquer(uint64_t table, size_t arity) {
    // Masks for the lower half of each 2^(s+1)-sized block.
    static constexpr uint64_t M[6] = {
        0x5555555555555555ULL, // s=0 : 01010101...
        0x3333333333333333ULL, // s=1 : 00110011...
        0x0F0F0F0F0F0F0F0FULL, // s=2 : 00001111...
        0x00FF00FF00FF00FFULL, // s=3 : bytes
        0x0000FFFF0000FFFFULL, // s=4 : 16-bit chunks
        0x00000000FFFFFFFFULL  // s=5 : 32-bit halves
    };

    for (size_t s = 0; s < arity; s++) {
        const uint64_t half = 1ULL << s;
        table ^= (table & M[s]) << half;
    }
    return table;
}

std::vector<uint64_t> anf_divide_and_conquer(std::vector<uint64_t> table, size_t arity) {
    static constexpr uint64_t M[6] = {
        0x5555555555555555ULL, 0x3333333333333333ULL,
        0x0F0F0F0F0F0F0F0FULL, 0x00FF00FF00FF00FFULL,
        0x0000FFFF0000FFFFULL, 0x00000000FFFFFFFFULL
    };

    const size_t upto = (arity < 6) ? arity : 6;
    for (size_t s = 0; s < upto; s++) {
        const uint64_t half = 1ULL << s;
        const uint64_t mask = M[s];
        for (uint64_t& v : table) {
            v ^= (v & mask) << half;
        }
    }

    // when arity >= 6
    for (size_t s = 6; s < arity; s++) {
        const size_t word_off    { size_t{1} << (s - 6) };
        const size_t block_words { word_off << 1 };
        for (size_t base = 0; base < table.size(); base += block_words)
            for (size_t i = 0; i < word_off; i++)
                table[base + word_off + i] ^= table[base + i];
    }
    return table;
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