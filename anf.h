#pragma once
#include <cstdint>
#include <vector>

uint64_t anf_divide_and_conquer(uint64_t t, unsigned arity);
void print_anf(const std::vector<uint8_t>& coeffs);