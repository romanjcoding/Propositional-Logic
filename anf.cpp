#include "anf.h"
#include "connective.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdint>

std::vector<uint8_t> compute_anf_naive(const Connective& f) {
    const std::vector<uint8_t> truth_table { f.get_table() };
    const size_t size { f.get_size() };

    std::vector<uint8_t> result;
    result.reserve(size);
    for (size_t i = 0; i < size; i++) {
        bool parity { 0 };
        for (size_t j = 0; j < size; j++) {
            // i >= j
            if ((i | j) == i) { parity ^= truth_table[j]; }
        }
        result.push_back(parity);
    }
    return result;
}

std::vector<uint8_t> anf_divide_and_conquer(const Connective& f) {
    std::vector<uint8_t> a = f.get_table();
    const size_t arity = f.get_arity();

    for (size_t k = 1; k <= arity; ++k) {
        const size_t tmp = size_t{1} << k;           // block size
        const size_t half = tmp >> 1;                // half block
        const size_t outer = size_t{1} << (arity - k);   // number of blocks

        for (size_t i = 0; i < outer; ++i) {
            const size_t base = tmp * i;
            for (size_t j = 0; j < half; ++j) {
                a[base + half + j] ^= a[base + j];
            }
        }
    }
    return a;
}

void print_anf(const std::vector<uint8_t>& coeffs) {
    bool first = true;
    for (size_t mask = 0; mask < coeffs.size(); ++mask) {
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