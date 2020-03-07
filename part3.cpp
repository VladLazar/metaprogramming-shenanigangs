#include <iostream>
#include <limits>

#include "expression.hpp"
#include "differentiation.hpp"

constexpr double at5 = 1.66893e+14;
constexpr double at10 = 2.65306e+19;

template <typename T>
constexpr const T& min(const T& a, const T& b) {
    return (b < a) ? b : a;
}

/*
 * Check for equivalence of two doubles.
 *
 * Courtesy of: https://stackoverflow.com/questions/4010240/comparing-doubles
 */
constexpr bool logically_equal(double a, double b, double error_factor = 1.0) {
    return a==b || 
           std::abs(a-b) < std::abs(min(a,b)) * 
                           std::numeric_limits<double>::epsilon() *
                           error_factor;
}

int main() {
    /* (x^20 + 3) / (x-3) */
    using poly = Div<Add<Exp<Var, Imm<20>>, Imm<3>>, Sub<Var, Imm<3>>>;
    using dif_poly = differentiation<poly>::type;

    static_assert(logically_equal(dif_poly::eval(5), at5, 1e10),
            "Result of evaluating differentiation at 5 is wrong");

    static_assert(logically_equal(dif_poly::eval(10), at10, 1e10),
            "Result of evaluating differentiation at 5 is wrong");

    std::cout << "Derivative of (x^20 + 3) / (x-3) at 5: " 
              << dif_poly::eval(5) << "\n"
              << "Derivative of (x^20 + 3) / (x-3) at 10: "
              << dif_poly::eval(10) << std::endl;

    return 0;
}
