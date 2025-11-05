#include "sampling.h"
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

    size_t size {arity / 6 + 1};
    std::vector<uint64_t> vec(size);

    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64_t> dis;
    for (int i = 0; i < size; i++) {
        vec[i] = dis(gen);
    }
    return vec;
}