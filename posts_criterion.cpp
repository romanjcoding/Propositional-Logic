#include "posts_criterion.h"
#include "connective.h"

bool is_preserving(const Connective& f) {
    std::vector<bool> truth_table { f.get_table() };
    return truth_table[0] == false || truth_table.at(f.get_size() - 1) == true;
}

bool is_self_dual(const Connective& f) {
    const std::vector<bool> truth_table { f.get_table() };
    size_t length = f.get_size();
    for (size_t i = 0; i < (length / 2); i++) {

        // since length - 1 = 01111..., ^ (XOR) will negative the bits of i
        if (truth_table[i] == truth_table[(length - 1) ^ i]) { return false; }
    }
    return true;
}

bool is_monotonic(const Connective& f) {
    const std::vector<bool> truth_table { f.get_table() };
    const size_t length = f.get_size();
    for (size_t x = 0; x < length; x++) {
        for (size_t y = 0; y < length; y++) {
            // x >= y
            if ((x & y) == x && truth_table[x] > truth_table[y]) { return false; }
        }
    }
    return true;
}

bool is_affine(const Connective& f) {
    return true;
}
