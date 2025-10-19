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

    // 00, 01, 10, 11
    Connective c_and({false, false, false, true});
    Connective c_or({false, true, true, true});
    Connective c_nand({true, true, true, false});

    // 000, 001, 010, 011, 100, 101, 110, 111
    Connective c_test({false, false, false, true, true, true, false, true});

    std::vector<bool> vec { compute_anf(c_test) };
    print_anf(vec);


    return 0;
}