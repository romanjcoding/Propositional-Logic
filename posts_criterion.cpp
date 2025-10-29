#include "posts_criterion.h"
#include "connective.h"
#include "anf.h"
#include <cstdint>

bool is_preserving(const Connective& f) {
    const std::vector<uint8_t> truth_table { f.get_table() };
    return !truth_table[0] || truth_table[f.get_size() - 1];
}

bool is_self_dual(const Connective& f) {
    const std::vector<uint8_t> truth_table { f.get_table() };
    size_t size = f.get_size();
    for (size_t i = 0; i < (size / 2); i++) {
        if (truth_table[i] == truth_table[(size - 1) ^ i]) { return false; }
    }
    return true;
}

bool is_monotonic(const Connective& f) {
    const std::vector<uint8_t> truth_table { f.get_table() };
    const size_t size = f.get_size();
    for (size_t x = 0; x < size; x++) {
        for (size_t y = 0; y < size; y++) {
            // x >= y
            if ((x | y) == x && truth_table[x] < truth_table[y]) { return false; }
        }
    }
    return true;
}

/*  y covers x if x <= y and there is no element z s.t. x <= z <= y.
    In our case, y covers x iff their bitmasks differ in exactly one 
    position, and that bit is 1 in y and 0 in x.
*/ 
bool is_monotonic_fast(const Connective& f) {
    const std::vector<uint8_t> truth_table { f.get_table() };
    const size_t size = f.get_size();
    const size_t arity = f.get_arity();
    for (size_t x = 0; x < size; x++) {
        for (size_t b = 0; b < arity; b++) {
            size_t bit = 1ULL << b;
            if ((x & bit) == 0) {
                size_t y = x | bit;
                if (truth_table[y] < truth_table[x]) { return false; }
            }
        }
    }
    return true;
}

bool is_affine_naive(const Connective& f) {
    const std::vector<uint8_t> anf { compute_anf_naive(f) };
    for (size_t i = 1; i < anf.size(); i++) {
        if (anf[i] && (i & (i - 1)) != 0) { return false; }
    }
    return true;
}

bool is_affine_divide(const Connective& f) {
    const std::vector<uint8_t> anf { anf_divide_and_conquer(f) };
    for (size_t i = 1; i < anf.size(); i++) {
        if (anf[i] && (i & (i - 1)) != 0) { return false; }
    }
    return true;
}