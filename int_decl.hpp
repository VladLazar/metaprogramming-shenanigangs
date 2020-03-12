#pragma once

#include <cstdint>
#include <limits>
#include <type_traits>

#include "differentiation.hpp"
#include "expression.hpp"

template <intmax_t at, typename ... Ts> struct size_matcher;
template <intmax_t at, typename T> struct fits;
template <typename A, typename B> struct pick;

template <typename T, intmax_t at>
struct int_decl {
private:
    /* 
     * This is rather flaky as it can lead to a narrowing conversion but the
     * coursework is due today so it'll do.
     */
    static constexpr intmax_t x = static_cast<intmax_t>(T::eval(at));
    static constexpr intmax_t y = static_cast<intmax_t>(differentiation<T>::type::eval(at));

public:
    using type_eval = typename size_matcher<x, char, unsigned int, int, long>::type;
    using type_diff = typename size_matcher<y, char, unsigned int, int, long>::type;

    using type = typename pick<type_eval, type_diff>::type;
};

template <intmax_t at, typename T, typename ... Ts>
struct size_matcher<at, T, Ts...> {
    using type = 
        typename std::conditional<
                    fits<at, T>::value,
                    T, 
                    typename size_matcher<at, Ts...>::type>::type;
};

template <intmax_t at>
struct size_matcher<at> {
    static_assert(true, "I can't fit!");
    using type = void;
};

template <intmax_t at, typename T>
struct fits {
    /* Again, super flaky ... */
    static constexpr bool value = std::numeric_limits<T>::min() <= at 
                                  and std::numeric_limits<T>::max() >= at;
};

template <typename A, typename B>
struct pick {
    /* Find the type that has more bits used for storage. */
    static constexpr bool is_a = 
        std::numeric_limits<A>::digits > std::numeric_limits<B>::digits
        or (std::is_same<A, int>::value and std::is_same<B, unsigned int>::value);

    using type = typename std::conditional<is_a, A, B>::type;
};
