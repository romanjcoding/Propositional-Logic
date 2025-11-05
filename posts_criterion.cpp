#include "posts_criterion.h"
#include "bitpack.h"
#include "anf.h"
#include <vector>
#include <cstdint>
#include <iostream>
#include <bit>

bool is_preserving(uint64_t table, size_t arity) {
    const size_t size { static_cast<size_t>(1) << arity };
    return !(table & 1) || table >> (size -  1);
}

bool is_preserving(const std::vector<std::uint64_t>& T, std::size_t arity) {
    const std::size_t N { bitpack::table_size(arity) };
    return bitpack::get_bit(T, 0) == 0 || bitpack::get_bit(T, N - 1) == 1;
}

bool is_self_dual(uint64_t table, size_t arity) {

    const size_t size { static_cast<size_t>(1) << arity };
    const size_t mask { size - 1 };

    for (size_t i = 0; i < (size / 2); i++) {
        unsigned bi = (table >> i) & 1ULL;
        unsigned bj = (table >> (mask ^ i)) & 1ULL;
        if (bi == bj) { return false; }
    }
    return true;
}

bool is_self_dual(const std::vector<std::uint64_t>& T, std::size_t arity) {

    const size_t size { bitpack::table_size(arity) };
    const size_t mask { size - 1 };

    for (size_t i = 0; i < (size / 2); i++) {
        const size_t j = mask ^ i;
        const bool bi = bitpack::get_bit(T, i);
        const bool bj = bitpack::get_bit(T, j);
        if (bi == bj) { return false; }
    }
    return true;
}

bool is_monotonic_fast(uint64_t table, size_t arity) {
    const size_t size { static_cast<size_t>(1) << arity };
    for (size_t x = 0; x < size; x++) {
        const size_t fx { (table >> x) & 1ULL };
        for (size_t b = 0; b < arity; b++) {
            const size_t bit { size_t(1) << b };
            if ((x & bit) == 0) {
                const size_t y  { x | bit };
                const size_t fy { (table >> y) & 1ULL };
                if (fy < fx) { return false; }
            }
        }
    }
    return true;
}

bool is_monotonic_fast(const std::vector<std::uint64_t>& T, std::size_t arity) {
    const size_t N { bitpack::table_size(arity) };
    for (size_t x = 0; x < N; x++) {
        const bool fx = bitpack::get_bit(T, x);
        for (size_t b = 0; b < arity; b++) {
            const size_t bit = size_t(1) << b;
            if ((x & bit) == 0) {
                const size_t y { x | bit };
                const bool fy  { bitpack::get_bit(T, y) };
                if (fy < fx) { return false; }
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

bool is_affine_divide(const std::vector<uint64_t>& table, size_t arity) {
    std::vector<uint64_t> anf { anf_divide_and_conquer(table, (unsigned)arity) };
    const size_t N = size_t{1} << arity;
    for (size_t w = 0; w < anf.size(); w++) {
        uint64_t word = anf[w];
        while (word) {
            unsigned i = std::countr_zero(word);
            size_t g = (w << 6) | i;
            word &= (word - 1);

            if (g >= N) continue;
            if (g == 0) continue;
            if ((g & (g - 1)) == 0) continue;
            return false;
        }
    }
    return true;
}