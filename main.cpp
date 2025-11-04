// TODO. Sampling w/o replacement that scales on sample size
// Fix how ugly the usage of generating_all [bool] is
// Fix Arity 6 stuff
// REFACTOR/
// progress bar
// std::vector<uint64_t> tables

#include "posts_criterion.h"
#include "sampling.h"
#include "timer.h"
#include <vector>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <string>

struct Args {
    size_t arity = 0;
    double sample_frac = 1.0;
};

static void print_usage(const char* prog) {
    std::cerr << "usage: " << prog << " <arity:int 0..5> <fraction: (0,1] | all>\n"
              << "examples:\n"
              << "  " << prog << " 5 0.25\n"
              << "  " << prog << " 3 all \n";
}

bool parse_args(int argc, char** argv, Args& out) {
    if (argc < 3) {
        print_usage(argv[0]);
        return false;
    }

    // argument 1: arity
    try {
        int a = std::stoi(argv[1]);
        if (a < 0 || a > 5) {
            std::cerr << "error: arity must be in [0,6] for a 64-bit table.\n";
            return false;
        }
        out.arity = static_cast<size_t>(a);
    } catch (...) {
        std::cerr << "error: invalid arity: '" << argv[1] << "'.\n";
        return false;
    }

    // argument 2: fraction <double> or "all"
    std::string f = argv[2];
    if (f == "all") {
        out.sample_frac = 1.0;
    } else {
        try {
            double x = std::stod(f);
            if (!(x > 0.0 && x <= 1.0)) {
                std::cerr << "error: fraction must be in (0,1] or the word 'all'.\n";
                return false;
            }
            out.sample_frac = x;
        } catch (...) {
            std::cerr << "error: invalid fraction: '" << f << "'. Use (0,1] or 'all'.\n";
            return false;
        }
    }
   return true;
}

inline bool do_work(uint64_t table, size_t arity) {
    if (is_preserving(table, arity))     { return false; } 
    if (is_self_dual(table, arity))      { return false; } 
    if (is_monotonic_fast(table, arity)) { return false; }
    if (is_affine_divide(table, arity))  { return false; }
    return true;
}

int main(int argc, char** argv) {
    Args args;
    if (!parse_args(argc, argv, args)) { return 1; }

    const size_t arity       { args.arity };
    const double sample_frac { args.sample_frac };

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
    if (sample_frac == 1.0) {
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
    return 0;
}