#include "posts_criterion.h"
#include "anf.h"
#include <cstdint>
#include <iostream>

bool is_preserving(uint64_t table, size_t arity) {
    const size_t size { static_cast<size_t>(1) << arity };
    return !(table & 1) || table >> (size -  1);
}

bool is_self_dual(uint64_t table, size_t arity) {
    const size_t size { static_cast<size_t>(1) << arity };
    for (size_t i = 0; i < (size / 2); i++) {
        unsigned bi = (table >> i) & 1ULL;
        unsigned bj = (table >> ((size - 1) ^ i)) & 1ULL;
        if (bi == bj) { return false; }
    }
    return true;
}

bool is_monotonic_fast(uint64_t table, size_t arity) {
    const size_t size { static_cast<size_t>(1) << arity };
    for (size_t x = 0; x < size; x++) {
        for (size_t b = 0; b < arity; b++) {
            size_t bit = 1ULL << b;
            if ((x & bit) == 0) {
                size_t y = x | bit;
                if (((table >> y) & 1ULL) < ((table >> x) & 1ULL)) { return false; }
            }
        }
    }
    return true;
}

bool is_affine_divide(uint64_t table, size_t arity) {
    const uint64_t anf { anf_divide_and_conquer(table, arity) };
    for (size_t i = 1; i < 64; i++) {
        if (((anf >> i) & 1ULL) && (i & (i - 1)) != 0) { return false; }
    }
    return true;
}