#include "connective.h"

std::vector<bool> compute_anf_naive(const Connective& f);
std::vector<bool> anf_divide_and_conquer(const Connective& f);
int compute_anf_deg(const Connective& f);

void print_anf(const std::vector<bool>& coeffs);