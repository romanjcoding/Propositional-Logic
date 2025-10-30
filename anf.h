#pragma once
#include "connective.h"
#include <cstdint>

std::vector<uint8_t> compute_anf_naive(const Connective& f);
std::vector<uint8_t> anf_divide_and_conquer(const Connective& f);
uint64_t anf_divide_and_conquer(uint64_t t, unsigned arity);
int compute_anf_deg(const Connective& f);

void print_anf(const std::vector<uint8_t>& coeffs);