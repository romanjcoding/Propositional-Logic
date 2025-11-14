#include "sampling.h"
#include "bitpack.h"
#include <random>
#include <vector>
#include <cstdint>

std::vector<uint64_t> get_sample(size_t arity) {

    const size_t words { bitpack::word_count(arity) };
    if (words > (1ULL << 30)) {
        throw std::bad_alloc();
    }

    std::vector<uint64_t> vec(words);

    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64_t> dis;
    for (int i = 0; i < words; i++) {
        vec[i] = dis(gen);
    }
    return vec;
}