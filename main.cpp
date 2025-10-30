// TODO. Sampling w/o replacement that scales on sample size
// Fix how ugly the usage of generating_all [bool] is
// Fix Arity 6 stuff
// REFACTOR

#include "connective.h"
#include "posts_criterion.h"
#include "timer.h"
#include <iostream>
#include <iomanip>
#include <cstdint>
#include <random>
#include <vector>
#include <string>
#include <unordered_set>

// https://stackoverflow.com/questions/311703/algorithm-for-sampling-without-replacement
void sample_without_replacement_floyd(uint64_t N, uint64_t n, std::vector<uint64_t>& samples) {
    samples.clear();
    samples.reserve(n);

    std::unordered_set<uint64_t> picked;
    picked.reserve(static_cast<size_t>(n * 1.3));

    std::mt19937_64 rng(std::random_device{}());
    for (uint64_t i = N - n; i < N; ++i) {
        std::uniform_int_distribution<uint64_t> dist(0, i);
        uint64_t t = dist(rng);
        if (!picked.insert(t).second) picked.insert(i);
    }

    samples.assign(picked.begin(), picked.end()); // order doesn't matter
}

int main(int argc, char** argv) {

    if (argc < 3) { std::cerr << "usage: app <int> (arity), <uint64_t> (fraction sampled) \n"; return 1; }
    
    const size_t arity { static_cast<size_t>(std::stoi(argv[1])) };
    double sample_frac;
    bool generating_all;
    if (std::string(argv[2]) == "all") { 
        sample_frac = 1.0;
        generating_all = true; 
    } 
    else { 
        sample_frac = std::stof(argv[2]);
        generating_all = false; 
    }

    const uint64_t rows { 1ull << arity };
    if (rows > 64) {
        std::cerr << "arity " << arity
                  << " not supported: truth table requires more than 64 bits.\n";
        return 1;
    }
    const uint64_t total = { 1ull << rows };

    const uint64_t num_samples { static_cast<uint64_t>(total * sample_frac) };
    std::vector<uint64_t> samples;
    if (!generating_all) {
        {
            timer t;
            sample_without_replacement_floyd(total, num_samples, samples);  
        }
    }

    uint64_t count_fc { 0 };
    if (!generating_all) {
        timer t;
        for (uint64_t table : samples) {
            Connective c(arity, table);
            if (!is_preserving(c) && 
                !is_self_dual(c) && 
                !is_monotonic_fast(c) && 
                !is_affine_divide(c))  { count_fc++; }
        }
    } else {
        // {
        //     timer t;
        //     for (uint64_t i = 0; i < total; i++) {
        //         Connective c(arity, i);
        //         if (!is_preserving(c) && 
        //             !is_self_dual(c) && 
        //             !is_monotonic_fast(c) && 
        //             !is_affine_divide(c))  { count_fc++; }
        //     }
        // }
        {
            timer t;
            for (uint64_t i = 0; i < total; i++) {
                Connective c(arity, i);
                if (!is_preserving(i, arity) && 
                    !is_self_dual(i, arity) && 
                    !is_monotonic_fast(i, arity) && 
                    !is_affine_divide(i, arity))  { count_fc++; }
            }
        }
    }

    std::cout << "Sampled " << num_samples << " / " << total
              << " (≈ " << std::setprecision(3) << std::fixed
              << (100.0 * num_samples / double(total)) << "%) arity-" << arity << " functions.\n";
    std::cout << count_fc << " were functionally complete (estimate ~ " << count_fc * 1 / sample_frac << " total).\n";
}