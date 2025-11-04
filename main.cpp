// TODO. Sampling w/o replacement that scales on sample size
// Fix how ugly the usage of generating_all [bool] is
// Fix Arity 6 stuff
// REFACTOR/
// progress bar
// std::vector<uint64_t> tables

#include "posts_criterion.h"
#include "sampling.h"
#include "timer.h"
#include <iostream>
#include <iomanip>
#include <cstdint>
#include <vector>
#include <string>

inline bool do_work(uint64_t table, size_t arity) {
    if (is_preserving(table, arity))     { return false; } 
    if (is_self_dual(table, arity))      { return false; } 
    if (is_monotonic_fast(table, arity)) { return false; }
    if (is_affine_divide(table, arity))  { return false; }
    return true;
}

inline bool do_work(std::vector<uint64_t> table, size_t arity); // TODO

int main(int argc, char** argv) {

    if (argc < 3) { std::cerr << "usage: app <int> (arity), <uint64_t> (fraction sampled) \n"; return 1; }
    
    const size_t arity { static_cast<size_t>(std::stoi(argv[1])) };

    double sample_frac;
    if (std::string(argv[2]) == "all") { sample_frac = 1.0; } 
    else { sample_frac = std::stof(argv[2]); }

    const uint64_t rows  { 1ull << arity };
    const uint64_t total { 1ull << rows };

    const uint64_t num_samples { static_cast<uint64_t>(total * sample_frac) };
    std::vector<std::vector<uint64_t>> samples;
    if (sample_frac != 1.0) {
        {
            timer t;
            // sample_with_replacement(arity, num_samples, samples);  
        }
    }

    uint64_t count_fc { 0 };
    if (sample_frac = 1.0) {
        timer t;
        for (uint64_t i = 0; i < total; i++) {
            count_fc += do_work(i, arity);
        }

    } else {
        timer t;
        for (std::vector<uint64_t> table : samples) {
            // count_fc += do_work(table, arity);
        }
    }

    std::cout << "Sampled " << num_samples << " / " << total
              << " (≈ " << std::setprecision(3) << std::fixed
              << (100.0 * num_samples / double(total)) << "%) arity-" << arity << " functions.\n";
    std::cout << count_fc << " were functionally complete (estimate ~ " << count_fc * 1 / sample_frac << " total).\n";
}