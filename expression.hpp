#pragma once

#include "exponentiation.hpp"

struct Var {
    static constexpr double eval(double var) {
        return var;
    }
};

template <int imm>
struct Imm {
    static constexpr double eval(double /* var */) {
        return static_cast<double>(imm);
    }
};

template <typename L, typename R> struct Add {
    static constexpr double eval(double var) {
        return L::eval(var) + R::eval(var);
    }
};

template <typename L, typename R> struct Sub {
    static constexpr double eval(double var) {
        return L::eval(var) - R::eval(var);
    }
};

template <typename L, typename R> struct Mul {
    static constexpr double eval(double var) {
        return L::eval(var) * R::eval(var);
    }
};

template <typename L, typename R> struct Div {
    static constexpr double eval(double var) {
        return L::eval(var) / R::eval(var);
    }
};

template <typename L, typename R> struct Exp {
    static constexpr double eval(double var) {
        return expo(L::eval(var), static_cast<int>(R::eval(var)));
    }
};
