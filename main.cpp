/* 
    TODO: 
    -print_table() and result() DRY
    -is_monotonic() with caching? 
    -
*/

#include "connective.h"
#include "posts_criterion.h"
#include "anf.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstdint>
#include <chrono>

static void print_progress(uint64_t done, uint64_t total) {
    if (total == 0) return;
    double frac = static_cast<double>(done) / static_cast<double>(total);
    const int width = 28;
    int filled = static_cast<int>(frac * width);
    std::cout << '\r' << '[';
    for (int i = 0; i < width; ++i) std::cout << (i < filled ? '#' : ' ');
    std::cout << "] " << std::setw(3) << static_cast<int>(frac * 100.0) << "% "
              << '(' << done << '/' << total << ')'
              << std::flush;
}

int main() {

    // 00, 01, 10, 11
    Connective c_and({false, false, false, true});
    Connective c_or({false, true, true, true});
    Connective c_nand({true, true, true, false});
    Connective c_affine({true, true, false, false});

    // 000, 001, 010, 011, 100, 101, 110, 111
    Connective c_test({false, false, false, true, true, true, false, true});

    for (size_t arity = 0; arity < 6; arity++) {
        uint64_t count = 0;
        const uint64_t total = (1ull << (1u << arity));

        // progress throttling: update at most ~200 times
        const uint64_t step = std::max<uint64_t>(1, total / 10000);

        auto last_tick = std::chrono::steady_clock::now();

        for (uint64_t mask = 0; mask < total; ++mask) {
            Connective c(arity, mask);
            if (!is_preserving(c) && !is_self_dual(c) &&
                !is_monotonic(c) && !is_affine_divide(c)) {
                count++;
            }

            if ((mask % step) == 0) {
                // also throttle by time to avoid excessive flushing on tiny totals
                auto now = std::chrono::steady_clock::now();
                if (now - last_tick >= std::chrono::milliseconds(50) || mask == 0) {
                    print_progress(mask, total);
                    last_tick = now;
                }
            }
        }

        print_progress(total, total);
        std::cout << '\n';

        std::cout << count
                  << " functionally complete boolean connectives of arity "
                  << arity << " found.\n";
    }
    return 0;
}