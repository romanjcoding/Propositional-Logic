#pragma once
#include <chrono>
#include <iostream>

class timer {
    std::chrono::steady_clock::time_point m_start;
public:
    timer() {
        m_start = std::chrono::high_resolution_clock::now();
    }
    ~timer() {
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - m_start;
        std::cout << "Execution time: " << duration.count() << " seconds\n";
    }
};