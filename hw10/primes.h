#pragma once

#include <cmath>

// TODO:
// Exercise 2:
// Implement greated common divisor using constexpr, such that it can be evaluated at compile time.
// Your implementation should use variadic templates, to enable calling it
// with any number of arguments, ensure that at least two arguments are provided.
//

template <typename T>
constexpr T gcd(T a, T b) {
    while (b != 0) {
        T temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Recursive variadic template for GCD computation: GCD of more than two numbers
template <typename T, typename... Args>
constexpr T gcd(T first, T second, Args... args) {
    return gcd(first, gcd(second, args...));
}
// Exercise 3:
// Implement minimum common multiple using constexpr, such that it can be evaluated at compile time.
// As with GCD, your implementation should use variadic templates, to enable calling it
// with arbitrary number of arguments, but at least two

template <typename T>
constexpr T mcm(T a, T b) {
    return (a * b) / gcd(a, b);
}

// Recursive variadic template for LCM computation
template <typename T, typename... Args>
constexpr T mcm(T first, T second, Args... args) {
    return mcm(first, mcm(second, args...));
}
//
// Exercise 4:
// Implement power using template metaprogramming. The template struct must be
// called `Power`, and be callable with `Power<base, exponent, modulus>::value`.
// I.e. it needs a compile time evaluation `value`, which holds the result of
// the computation.
// Think about your base cases

template <int Base, int Exponent, int Modulus> 
struct Power {
    static constexpr int value = (Power<Base, Exponent - 1, Modulus>::value * Base) % Modulus;
};

// Base case for exponentiation where exponent is 0
template <int Base, int Modulus>
struct Power<Base, 0, Modulus> {
    static constexpr int value = 1;
};

template <int Base>
struct Power<Base, 0, 1> {
    static constexpr int value = 0;
};
