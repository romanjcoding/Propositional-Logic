#include "sampling.h"
#include "bitpack.h"
#include <random>
#include <vector>
#include <unordered_set>
#include <cstdint>
#include <iostream>

// https://stackoverflow.com/questions/311703/algorithm-for-sampling-without-replacement
void sample_without_replacement(uint64_t N, uint64_t n, std::vector<uint64_t>& samples) {
    samples.clear();
    samples.reserve(n);

    std::unordered_set<uint64_t> picked;
    picked.reserve(static_cast<size_t>(n * 1.3));

    std::mt19937_64 rng(std::random_device{}());
    for (uint64_t i = N - n; i < N; ++i) {
        std::uniform_int_distribution<uint64_t> dist(0, i);
        uint64_t t = dist(rng);
        if (!picked.insert(t).second) picked.insert(i);
    }

    samples.assign(picked.begin(), picked.end());
}

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