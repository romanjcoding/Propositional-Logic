#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
#include <stdexcept>

class Connective {
    const std::vector<bool> m_table; 
    const size_t m_size { m_table.size() };
    const size_t m_arity { deduce_arity(m_size) };

    static size_t deduce_arity(size_t size) {
        if (size == 0 || (size & (size - 1)) != 0) {
            throw std::invalid_argument("Truth table size must be a power of two.");
        }
        size_t n = 0;
        while ((1u << n) != size) { n++; }
        return n;
    }

    static std::vector<bool> make_table(unsigned arity, unsigned long long bits) {
        size_t rows = 1ull << arity;
        if (rows > 64) throw std::invalid_argument("Too many rows for bit mask.");
        std::vector<bool> t(rows);
        for (size_t i = 0; i < rows; ++i) {
            t[i] = (bits >> i) & 1ull;
        }
        return t;
    }


public:
    explicit Connective(std::initializer_list<bool> tv) : m_table(tv) {}
    explicit Connective(unsigned arity, unsigned long long bits)
        : m_table(make_table(arity, bits)) {}

    const std::vector<bool>& get_table() const { return m_table; }
    const size_t get_size() const { return m_size; }

    static char tf(bool b) { return b ? 'T' : 'F'; }

    void print_table() const {

        std::vector<std::string> vars;
        const std::string var_set = "pqrsuvwxyz";
        for (unsigned i = 0; i < m_arity; ++i) {
            vars.push_back(std::string(1, var_set[i])); 
        }

        // Column width
        const int w = 3;

        // Header
        for (unsigned i = 0; i < m_arity; ++i) std::cout << std::setw(w) << vars[i];
        std::cout << " │ " << std::setw(w) << '\n';

        // Separator
        int total_width = (int)m_arity * w + 3 + w;
        for (int i = 0; i < total_width; ++i) std::cout << (i == (int)m_arity*w + 1 ? "┼" : "─");
        std::cout << '\n';

        for (size_t i = 0; i < m_size; ++i) {
            for (unsigned j = 0; j < m_arity; ++j) {
                bool bit = (i >> (m_arity - 1 - j)) & 1u;
                std::cout << std::setw(w) << tf(bit);
            }
            std::cout << " │ " << std::setw(w) << tf(m_table[i]) << '\n';
        }
    }
};