#pragma once

#include <type_traits>

template <typename T, typename U>
T constexpr expo(T base, U exponent) {
    static_assert(std::is_integral<U>::value, "Exponent must be of integral type");
    return exponent > 0 ? base * expo(base, exponent - 1) : 1;
}
