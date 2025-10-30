#pragma once
#include "connective.h"

bool zero_preserving(const Connective& f);
bool one_preserving(const Connective& f);
bool is_preserving(const Connective& f);
bool is_preserving(uint64_t table, size_t arity);

bool is_self_dual(const Connective& f);
bool is_self_dual(uint64_t table, size_t arity);

bool is_monotonic(const Connective& f);
bool is_monotonic_fast(const Connective& f);
bool is_monotonic_fast(uint64_t table, size_t arity);

bool is_affine_naive(const Connective& f);
bool is_affine_divide(const Connective& f);
bool is_affine_divide(uint64_t table, size_t arity);