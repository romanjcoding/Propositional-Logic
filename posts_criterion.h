#pragma once
#include <cstdint>
#include <cstddef>

bool is_preserving(uint64_t table, size_t arity);
bool is_self_dual(uint64_t table, size_t arity);
bool is_monotonic_fast(uint64_t table, size_t arity);
bool is_affine_divide(uint64_t table, size_t arity);