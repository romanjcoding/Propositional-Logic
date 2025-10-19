/* 
    -TODO: print_table() and result() DRY
    -
    -
*/

#include <vector>
#include <iostream>
#include <string>
#include <cstdint>
#include <stdexcept>
#include <array>
#include <algorithm>
#include <iomanip>

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

public:
    explicit Connective(std::initializer_list<bool> tv) : m_table(tv) {}

    bool result(const std::vector<bool>& inputs) const { 
        const std::size_t arity = inputs.size();
        if ((1u << arity) != m_size) {
            throw std::invalid_argument("Inputs do not match the size of connective");
        }
        std::size_t idx = 0;
        for (bool b : inputs) { idx = (idx << 1) | (b ? 1u : 0u); }
        return m_table[idx];
    }

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

int main() {
    Connective c_and({false, false, false, true});
    c_and.print_table();
    return 0;
}