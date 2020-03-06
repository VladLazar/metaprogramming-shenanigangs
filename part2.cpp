#include <cstdlib>
#include <iostream>

#include "expression.hpp"
#include "integrate.hpp"

constexpr double eps = 1.0e-2;

int main() {
    /* (x^2) + (2*x) - 3 */
    using poly = Add<Exp<Var, Imm<2>>, Sub<Mul<Imm<2>, Var>, Imm<3>>>;
    using rect = integration<poly, rectangular_interpolation, 200>;
    using trap = integration<poly, trapezoidal_interpolation, 200>;

    static_assert(
            std::abs(rect::integrate(0, 10) - 403.331) < eps,
            "Compile time rectangular_interpolation yielded the wrong result");

    static_assert(
            std::abs(trap::integrate(0, 10) - 403.337) < eps,
            "Compile time rectangular_interpolation yielded the wrong result");

    std::cout << "Integrate (x^2) + (2*x) - 3 with rectangular interpolation "
              << "between 0 and 10: " 
              << rect::integrate(0, 10)
              << std::endl;

    std::cout << "Integrate (x^2) + (2*x) - 3 with trapezoidal interpolation "
              << "between 0 and 10: "
              << trap::integrate(0, 10)
              << std::endl;
}
