#pragma once
#include <cstdint>
#include <vector>

void sample_without_replacement(uint64_t N, uint64_t n, std::vector<uint64_t>& samples);
std::vector<uint64_t> get_sample(size_t arity);