#include "expression.hpp"
#include "differentiation.hpp"
#include "int_decl.hpp"

#include <type_traits>
#include <iostream>

int main() {
    /* 4(x ^ 3) + 2(x ^ 2) + 50 */
    using poly = Add<Mul<Imm<4>, Exp<Var, Imm<3>>>, 
                     Add<Mul<Imm<2>, Exp<Var, Imm<2>>>, Imm<50>>>;

    static_assert(std::is_same<int_decl<poly, 0>::type, char>::value, "Wrong!");

    static_assert(std::is_same<int_decl<poly, 10>::type, unsigned int>::value, "Wrong!");
    static_assert(std::is_same<int_decl<poly, 20>::type, unsigned int>::value, "Wrong!");
    static_assert(std::is_same<int_decl<poly, 30>::type, unsigned int>::value, "Wrong!");

    static_assert(std::is_same<int_decl<poly, -10>::type, int>::value, "Wrong!");
    static_assert(std::is_same<int_decl<poly, -20>::type, int>::value, "Wrong!");
    static_assert(std::is_same<int_decl<poly, -30>::type, int>::value, "Wrong!");

    int_decl<poly, 0>::type value = poly::eval(0);
    std::cout << "The type char was deduced for the expression "
              << "4(x ^ 3) + 2(x ^ 2) + 50 evaluated at 0" << std::endl; 

    std::cout << "The value of 4(x ^ 3) + 2(x ^ 2) + 50 at 0 is: " << value << std::endl;
}
