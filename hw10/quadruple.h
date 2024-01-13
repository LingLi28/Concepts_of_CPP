#pragma once

#include <array>

// TODO: Implement the Quadruple struct, with the required specialisations
// - The general case should store types and have getters for each called `get_first`, `get_second`,
// etc
// - Implement once specialization if all types are ints. Store them in a publicly accessible
// `std::array`, again provide the getters.
// - Implement once specialization if all types are the same. Store them in a publicly accessible
// `std::array`, again provide the getters.
template <typename T, typename U, typename V, typename W> struct Quadruple {
public:
    Quadruple(const T& t, const U& u, const V& v, const W& w) : first(t), second(u), third(v), fourth(w) {}

   // Getters for each member
    T get_first() const { return first; }
    U get_second() const { return second; }
    V get_third() const { return third; }
    W get_fourth() const { return fourth; }

private:
    T first;
    U second;
    V third;
    W fourth;
};

// Specialization for Quadruple with four ints
template <>
struct Quadruple<int, int, int, int> {
public:
    std::array<int, 4> members;

    // Constructor to initialize the array
    Quadruple(int a, int b, int c, int d) : members({a, b, c, d}) {}

    // Getters for each member
    int get_first() const { return members[0]; }
    int get_second() const { return members[1]; }
    int get_third() const { return members[2]; }
    int get_fourth() const { return members[3]; }
};

// Partial specialization for Quadruple with the same type T
template <typename T>
struct Quadruple<T, T, T, T> {
public:
    std::array<T, 4> members;

    // Constructor to initialize the array
    Quadruple(T a, T b, T c, T d) : members({a, b, c, d}) {}

    // Getters for each member
    T get_first() const { return members[0]; }
    T get_second() const { return members[1]; }
    T get_third() const { return members[2]; }
    T get_fourth() const { return members[3]; }
};


