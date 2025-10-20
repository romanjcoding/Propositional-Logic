#pragma once
#include "connective.h"

bool zero_preserving(const Connective& f);
bool one_preserving(const Connective& f);
bool is_preserving(const Connective& f);
bool is_self_dual(const Connective& f);
bool is_monotonic(const Connective& f);
bool is_affine_naive(const Connective& f);