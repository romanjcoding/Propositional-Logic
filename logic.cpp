#include <vector>
#include <iostream>
#include <string>

class Connective {

    const std::vector<bool> truth_values; 
    const size_t connective_size { truth_values.size() };

    public:
        explicit Connective(std::initializer_list<bool> tv) : truth_values(tv) {}

        bool result(std::vector<bool> inputs) { 
            
            const std::size_t arity { inputs.size() };
            if ((1u << arity) != connective_size) {
                throw std::invalid_argument("Inputs do not match the size of connective");
            }

            std::size_t idx = 0;
            for (bool b : inputs) { idx = (idx << 1) | (b ? 1u : 0u); }
            return truth_values[idx];
        }

        void view_truth_table_2d() {
            if (connective_size != 4) {
                throw std::invalid_argument("Connective must be 2 dimensional");
            }
            std::cout << "┌───┬───┬───┐\n";
            std::cout << "│q\\p│ T │ F │\n";
            std::cout << "├───┼───┼───┤\n";
            std::cout << "│ T │ " << (truth_values[3] ? 'T' : 'F')
                    <<  " │ "   << (truth_values[2] ? 'T' : 'F') << " │\n";
            std::cout << "├───┼───┼───┤\n";
            std::cout << "│ F │ " << (truth_values[1] ? 'T' : 'F')
                    <<  " │ "   << (truth_values[0] ? 'T' : 'F') << " │\n";
            std::cout << "└───┴───┴───┘\n";
        }
};

int main(){

    // FF, FT, TF, TT
    Connective c_xor {false, true, true, false};
    Connective c_imples {true, true, false, true};
    Connective c_and {false, false, false, true};
    Connective c_or {false, true, true, true};

    // F, T
    Connective c_not {true, false};

    std::cout << std::boolalpha;
    std::cout << c_xor.result({false, false}) << '\n'; // 1
    std::cout << c_xor.result({false, true}) << '\n'; // 1
    std::cout << c_xor.result({true, false}) << '\n'; // 1
    std::cout << c_xor.result({true, true}) << '\n'; // 0

    c_xor.view_truth_table_2d();


    std::string input {};
    std::cout << "Enter a propositional statement: ";
    std::cin >> input;

    return 0;
}