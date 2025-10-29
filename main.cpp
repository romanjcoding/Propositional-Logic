#include "connective.h"
#include "posts_criterion.h"
#include "anf.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstdint>
#include <random>
#include <string_view>
#include <charconv>

int main(int argc, char** argv) {
    if (argc < 2) { std::cerr << "usage: app <int> (arity), <double> (fraction sampled) \n"; return 1; }
    std::string_view s = argv[1];
    size_t arity{};
    std::from_chars(s.data(), s.data() + s.size(), arity);

    const uint64_t rows { 1ull << arity };
    const uint64_t total = { 1ull << rows };

    const double sample_fraction = { 1.0 };
    const uint64_t target { static_cast<uint64_t>(total * sample_fraction) };
    const uint64_t samples { target };
    uint64_t count_fc { 0 };


    for (uint64_t s = 0; s < samples; ++s) {
        Connective c(arity, s);

        bool p = is_preserving(c);
        bool sd = is_self_dual(c);
        // bool mono_naive = is_monotonic(c);
        bool mono_fast = is_monotonic_fast(c);
        // bool aff_naive = is_affine_naive(c);
        bool aff_fast = is_affine_divide(c);

        bool is_fc { !p && !sd && !mono_fast && !aff_fast };    
        if (is_fc) { count_fc++; }
    }

    std::cout << "\n";

    std::cout << "Sampled " << samples << " / " << total
              << " (≈ " << std::setprecision(3) << std::fixed
              << (100.0 * samples / double(total)) << "%) arity-" << arity << " functions.\n";
    std::cout << count_fc << " were functionally complete (estimated by sampling).\n\n";
}