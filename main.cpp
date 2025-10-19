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

int main() {
    Connective c_and({false, false, false, true});
    Connective c_or({false, true, true, true});
    Connective c_nand({true, true, true, false});
    // 000, 001, 010, 
    Connective c_test({false, true, false, false, false, true, true, true});

    std::vector<bool> vec { compute_anf(c_test) };
    for (bool b : vec) {
        std::cout << b;
    }
    std::cout << '\n';

    return 0;
}