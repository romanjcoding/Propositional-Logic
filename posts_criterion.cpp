#include "posts_criterion.h"
#include "connective.h"
#include "anf.h"

bool is_preserving(const Connective& f) {
    std::vector<bool> truth_table { f.get_table() };
    return !truth_table[0] || truth_table.at(f.get_size() - 1);
}

bool is_self_dual(const Connective& f) {
    const std::vector<bool> truth_table { f.get_table() };
    size_t length = f.get_size();
    for (size_t i = 0; i < (length / 2); i++) {
        if (truth_table[i] == truth_table[(length - 1) ^ i]) { return false; }
    }
    return true;
}

bool is_monotonic(const Connective& f) {
    const std::vector<bool> truth_table { f.get_table() };
    const size_t length = f.get_size();
    for (size_t x = 0; x < length; x++) {
        for (size_t y = 0; y < length; y++) {
            // x >= y
            if ((x | y) == x && truth_table[x] < truth_table[y]) { return false; }
        }
    }
    return true;
}

bool is_affine_naive(const Connective& f) {
    const std::vector<bool> vec { compute_anf_naive(f) };
    
    for (size_t i = 1; i < vec.size(); i++) {
        // i is not a power of two
        if (vec.at(i) && (i & (i - 1)) != 0) { return false; }
    }
    return true;
}

bool is_affine_divide(const Connective& f) {
    const std::vector<bool> vec { anf_divide_and_conquer(f) };
    
    for (size_t i = 1; i < vec.size(); i++) {
        // i is not a power of two
        if (vec.at(i) && (i & (i - 1)) != 0) { return false; }
    }
    return true;
}