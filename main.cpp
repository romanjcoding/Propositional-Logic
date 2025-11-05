// TODO. 
// update_progress is quite slow

#include "cli.h"
#include "posts_criterion.h"
#include "sampling.h"
#include "timer.h"
#include <vector>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <iomanip>

inline bool do_work(uint64_t table, size_t arity) noexcept {
    if (is_preserving(table, arity))     { return false; } 
    if (is_self_dual(table, arity))      { return false; } 
    if (is_monotonic_fast(table, arity)) { return false; }
    if (is_affine_divide(table, arity))  { return false; }
    return true;
}

inline bool do_work(const std::vector<uint64_t>& table, size_t arity) noexcept {
    if (is_preserving(table, arity))     { return false; } 
    if (is_self_dual(table, arity))      { return false; } 
    if (is_monotonic_fast(table, arity)) { return false; }
    if (is_affine_divide(table, arity))  { return false; }
    return true;
}

int main(int argc, char** argv) {
    Args args;
    if (!parse_args(argc, argv, args)) { return 1; }

    const size_t arity          { args.arity };
    const uint64_t num_samples  { args.num_samples };
    const bool generating_all   { args.generating_all };

    uint64_t count{};
    if (generating_all) {
        timer t; 
        for (uint64_t i = 0; i < num_samples; i++) { 
            count += do_work(i, arity);
            print_progress(i, num_samples);
        }
    }
    else if (!generating_all) {
        timer t; 
        for (uint64_t i = 0; i < num_samples; i++) {
            std::vector<uint64_t> rand { get_sample(arity) };
            count += do_work(rand, arity);
            print_progress(i, num_samples);
        }
    }
    std::cout << "Sampled " << num_samples << " / " << num_samples
              << " arity-" << arity << " functions.\n";
    std::cout << count << " were functionally complete\n";
    return 0;
}