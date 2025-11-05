#pragma once
#include <cstddef>
#include <cstdint>

struct Args {
    size_t arity;
    uint64_t num_samples;
    bool generating_all;
};

void print_usage(const char* prog);
void print_progress(uint64_t done, uint64_t total);
bool parse_args(int argc, char** argv, Args& out);
