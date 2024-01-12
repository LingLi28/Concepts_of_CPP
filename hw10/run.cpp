#include <iostream>
#include <string>

#include "bencode.h"
#include "hw10.h"


int main() {
    // Exercise 1
    auto quad = Quadruple<int, int, int, int>(1, 2, 3, 4);
    std::cout << quad.get_first() << ", "
              << quad.get_second() << ", "
              << quad.get_third() << ", "
              << quad.get_fourth() << ", " << std::endl;

    auto string_quad = Quadruple<std::string, std::string,
                                 std::string, std::string>("abc", "def", "ghi", "...");
    std::cout << string_quad.get_first() << ", "
              << string_quad.get_second() << ", "
              << string_quad.get_third() << ", "
              << string_quad.get_fourth() << ", " << std::endl;

    auto mixed_quad = Quadruple<std::string, int,
                                char, bool>("abc", 42, '\n', 0);
    std::cout << mixed_quad.get_first() << ", "
              << mixed_quad.get_second() << ", "
              << mixed_quad.get_third() << ", "
              << mixed_quad.get_fourth() << ", " << std::endl;

    // Exercise 2
    std::cout << gcd(1345, 7) << std::endl
              << gcd(4004, 102) << std::endl
              << gcd(2, 4, 6, 8, 10) << std::endl;

    // Exercise 3
    std::cout << mcm(1345, 7) << std::endl
              << mcm(4004, 102) << std::endl
              << mcm(2, 4, 6, 8, 10) << std::endl;

    // Exercise 4
    std::cout << "10^0 mod 3 = "
              << Power<10, 0, 3>::value << std::endl;
    std::cout << "1^0 mod 3 = "
              << Power<1, 0, 3>::value << std::endl;
    std::cout << "5^3 mod 13 = "
              << Power<5, 3, 13>::value << std::endl;
    std::cout << "4^13 mod 497 = "
              << Power<4, 13, 497>::value << std::endl;

    // Exercise 5
    // Pst, usually you should check if a value is contained, but it's easier here!
    std::cout << "i42e decoded is '" << bencode::parse_int("i42e").value() << "'\n";
    std::cout << "i-42e decoded is '" << bencode::parse_int("i-42e").value() << "'\n";
    std::cout << "'11:hello world' decoded is '" << bencode::parse_byte_string("11:hello world").value() << "'\n";

    return 0;
}
