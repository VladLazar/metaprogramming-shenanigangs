#pragma once

#include "expression.hpp"

template <typename T, template<typename> class Fn, int divisions>
struct integration {
    static constexpr double integrate(double lower, double upper) {
        return Fn<T>::value(lower, lower + step(lower, upper))
               + integration<T, Fn, divisions - 1>::integrate(
                 lower + step(lower, upper), upper);
    } 

private:
    static constexpr double step(double lower, double upper) {
        return (upper - lower) / divisions;
    }
};

template <typename T, template<typename> class Fn>
struct integration<T, Fn, 0> {
    static constexpr double integrate(double /* lower */, double /* upper */) {
        return 0;
    }
};

template <typename T = void>
struct rectangular_interpolation {
    static constexpr double value(double lower, double upper) {
        return (upper - lower) * T::eval((upper + lower) / 2);
    }
};

template <typename T = void>
struct trapezoidal_interpolation {
    static constexpr double value(double lower, double upper) {
        return (upper - lower) * (T::eval(lower) + T::eval(upper)) / 2;
    }
};
