#include "connective.h"

std::vector<bool> compute_anf(const Connective& f);
int compute_anf_deg(const Connective& f);

void print_anf(const std::vector<bool>& coeffs);