#pragma once
#include <cstdint>
#include <vector>
#include <cassert>
#include <limits>

namespace bitpack {

inline size_t table_size(size_t arity) {
    return size_t(1) << arity;
}

inline size_t word_count(size_t arity) {
    const size_t bits = table_size(arity);
    return (bits + 63) >> 6;
}

inline bool get_bit(const std::vector<uint64_t>& T, size_t i) {
    return (T[i >> 6] >> (i & 63)) & 1ULL;
}

inline void set_bit(std::vector<uint64_t>& T, size_t i, bool v) {
    const size_t w = i >> 6, b = i & 63;
    const uint64_t mask = 1ULL << b;
    if (v) T[w] |= mask; else T[w] &= ~mask;
}
}