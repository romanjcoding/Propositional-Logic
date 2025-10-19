#include "connective.h"
#include <vector>

std::vector<bool> compute_anf(const Connective& f) {
    const std::vector<bool> truth_table { f.get_table() };
    const size_t length = f.get_size();
    std::vector<bool> result;
    result.reserve(length);
    for (size_t i = 0; i < length; i++) {
        int sum { 0 };
        for (size_t j = 0; j < length; j++) {
            // i >= j
            if ((i & j) == i) { sum += truth_table[j]; } // parity ^= truth_table[j]
        }
        result.push_back(static_cast<bool>(sum % 2));
    }
    return result;
}