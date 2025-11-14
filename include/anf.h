#pragma once
#include <cstdint>
#include <vector>

uint64_t anf_divide_and_conquer(uint64_t t, size_t arity);
std::vector<uint64_t> anf_divide_and_conquer(std::vector<uint64_t> table, size_t arity);
void print_anf(const std::vector<uint8_t>& coeffs);