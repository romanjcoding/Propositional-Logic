#pragma once
#include <cstdint>
#include <vector>

void sample_without_replacement(uint64_t N, uint64_t n, std::vector<uint64_t>& samples);
void sample_with_replacement(size_t arity, uint64_t num_samples, std::vector<std::vector<uint64_t>>& samples);