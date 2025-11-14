#pragma once
#include <cstdint>
#include <cstddef>
#include <vector>

bool is_preserving(uint64_t table, size_t arity);
bool is_preserving(const std::vector<std::uint64_t>& T, std::size_t arity);

bool is_self_dual(uint64_t table, size_t arity);
bool is_self_dual(const std::vector<uint64_t>&, size_t arity);

bool is_monotonic_fast(uint64_t table, size_t arity);
bool is_monotonic_fast(const std::vector<uint64_t>& table, size_t arity);

bool is_affine_divide(uint64_t table, size_t arity);
bool is_affine_divide(const std::vector<uint64_t>& table, size_t arity);