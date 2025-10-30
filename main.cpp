// TODO. Sampling w/o replacement that scales on sample size

#include "connective.h"
#include "posts_criterion.h"
#include "anf.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstdint>
#include <random>
#include <vector>
#include <cstdlib>

// https://stackoverflow.com/questions/311703/algorithm-for-sampling-without-replacement
void sample_without_replacement
(   uint64_t population_size, 
    uint64_t sample_size, 
    std::vector<uint64_t>& samples
) {
    // Use Knuth's variable names
    uint64_t& n { sample_size };
    uint64_t& N { population_size };

    int t { 0 }; // total input records dealt with
    int m { 0 }; // number of items selected so far

    std::default_random_engine re;
    std::uniform_real_distribution<double> dist(0,1);

    while (m < n) {
        double u = dist(re); // call a uniform(0,1) random number generator
        if ((N - t) * u >= n - m ) { t++; }
        else {
            samples[m] = t;
            t++; 
            m++;
        }
    }
}

int main(int argc, char** argv) {

    if (argc < 3) { std::cerr << "usage: app <int> (arity), <uint64_t> (fraction sampled) \n"; return 1; }
    
    const size_t arity       { static_cast<size_t>(std::stoi(argv[1])) };
    const double sample_frac { std::stof(argv[2]) };

    const uint64_t rows { 1ull << arity };
    if (rows > 64) {
        std::cerr << "arity " << arity
                  << " not supported: truth table requires more than 64 bits.\n";
        return 1;
    }
    const uint64_t total = { 1ull << rows };

    const uint64_t num_samples { static_cast<uint64_t>(total * sample_frac) };
    uint64_t count_fc { 0 };

    std::vector<uint64_t> samples(num_samples);
    sample_without_replacement(total, num_samples, samples);

    for (int i = 0; i < num_samples; i++) {
        Connective c(arity, samples[i]);
        if (!is_preserving(c)     && 
            !is_self_dual(c)      && 
            !is_monotonic_fast(c) && 
            !is_affine_divide(c))  { count_fc++; }
    }

    std::cout << "Sampled " << num_samples << " / " << total
              << " (≈ " << std::setprecision(3) << std::fixed
              << (100.0 * num_samples / double(total)) << "%) arity-" << arity << " functions.\n";
    std::cout << count_fc << " were functionally complete (estimate ~ " << count_fc * 1 / sample_frac << " total).\n";
}