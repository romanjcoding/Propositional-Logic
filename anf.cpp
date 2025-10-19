#include "anf.h"
#include "connective.h"
#include <vector>
#include <iostream>
#include <sstream>

std::vector<bool> compute_anf(const Connective& f) {
    const std::vector<bool> truth_table { f.get_table() };
    const size_t length = f.get_size();
    std::vector<bool> result;
    result.reserve(length);
    for (size_t i = 0; i < length; i++) {
        bool parity { 0 };
        for (size_t j = 0; j < length; j++) {
            // i >= j
            if ((i | j) == i) { parity ^= truth_table[j]; }
        }
        result.push_back(parity);
    }
    return result;
}

void print_anf(const std::vector<bool>& coeffs) {
    bool first = true;
    for (size_t mask = 0; mask < coeffs.size(); ++mask) {
        if (!coeffs[mask]) continue;

        std::ostringstream term;
        if (mask == 0) {
            term << "1";
        } else {
            size_t tmp = mask, bit = 0;
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
