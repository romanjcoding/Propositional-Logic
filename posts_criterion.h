#pragma once
#include "connective.h"

bool is_preserving(const Connective& f);
bool is_self_dual(const Connective& f);
bool is_monotonic(const Connective& f);
bool is_affine(const Connective& f);