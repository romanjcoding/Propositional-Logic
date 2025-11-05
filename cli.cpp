#include "cli.h"
#include <cli.h>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <string>

void print_usage(const char* prog) {
    std::cout << "usage: " << prog << " <arity:int 0..5> <uint64_t: num_samples | "": all>\n"
              << "examples:\n"
              << "  " << prog << " 5 0.25\n"
              << "  " << prog << " 3 all \n";
}

void print_progress(uint64_t done, uint64_t total) {
    
    if (total == 0) { return; }

    static uint64_t next_tick  { 0 }; 
    static const int bar_width { 40 };

    // Only print occasionally
    if (done < next_tick && done + 1 != total) { return; }

    const double ratio { static_cast<double>(done) / static_cast<double>(total) };
    const int filled   { static_cast<int>(ratio * bar_width) };

    std::cout << '\r' << '[';
    for (int i = 0; i < bar_width; ++i) {
        std::cout << (i < filled ? '=' : ' ');
    }
    std::cout << "] "
              << std::setw(6) << std::fixed << std::setprecision(2)
              << (ratio * 100.0) << '%';

    if (done + 1 >= total) {
        std::cout << '\n';
        next_tick = 0;
    } else {
        std::cout.flush();
        std::uint64_t step = total / 100;
        if (step == 0) { step = 1; }
        next_tick = done + step;
    }
}

bool parse_args(int argc, char** argv, Args& out) {
    if (argc < 3) {
        print_usage(argv[0]);
        return false;
    }

    // argument 1: arity
    try {
        int a = std::stoi(argv[1]);
        if (a < 0) {
            std::cerr << "error: arity must > 0\n";
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
        out.num_samples = 1ULL << (1ULL << out.arity);
        out.generating_all = true;
    } else {
        try {
            uint64_t x = std::stoll(f);
            out.num_samples = x;
            out.generating_all = false;
        } catch (...) {
            std::cerr << "error: invalid num_samples: '" << f << "'. Use (0, std::numeric_limits<uint64_t>::max()] or 'all'.\n";
            return false;
        }
    }
   return true;
}