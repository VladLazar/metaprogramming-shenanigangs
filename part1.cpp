#include <iostream>

#include "expression.hpp"

int main() {
    /* The equivalent of x ^ 3 + 5 */
    Add<Exp<Var, Imm<3>>, Imm<5>> expression;
    static_assert(expression.eval(2.5) == 20.625,
            "Expressions must be evaluated at compile time.");
    
    std::cout << "Evaluated x ^ 3 + 5 at 2.5: " << expression.eval(2.5) << std::endl;
}
