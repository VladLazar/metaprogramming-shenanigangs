#pragma once

#include "expression.hpp"

template <typename T> struct differentiation;

template <> struct differentiation<Var> {
    using type = Imm<1>;
};

template <int imm> struct differentiation<Imm<imm>> {
    using type = Imm<0>;
};

template <typename L, typename R> struct differentiation<Add<L, R>> {
    using type = Add<typename differentiation<L>::type, typename differentiation<R>::type>;
};

template <typename L, typename R> struct differentiation<Sub<L, R>> {
    using type = Sub<typename differentiation<L>::type, typename differentiation<R>::type>;
};

template <typename L, typename R> struct differentiation<Mul<L, R>> {
private:
    using left  = Mul<L, typename differentiation<R>::type>;
    using right = Mul<R, typename differentiation<L>::type>;

public:
    using type = Add<left, right>;
};

template <typename L, typename R> struct differentiation<Div<L, R>> {
private:
    using denominator = Exp<R, Imm<2>>;
    using numerator   = Sub<Mul<R, typename differentiation<L>::type>,
                            Mul<L, typename differentiation<R>::type>>;

public:
    using type = Div<numerator, denominator>;
};

template <typename L, typename R> struct differentiation<Exp<L, R>> {
private:
    using new_exp = Exp<L, Sub<R, Imm<1>>>;

public:
    using type = Mul<R ,Mul<new_exp, typename differentiation<L>::type>>;
};
