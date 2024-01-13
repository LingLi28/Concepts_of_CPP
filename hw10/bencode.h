#pragma once

#include <optional>
#include <string_view>

namespace bencode {
// TODO: Implement int parsing for the bencode fromat
// Bencode encoded integers have the format `i<number>e`. Your function should return the number.
// The function returns a `std::optional<std::string_view>` to indicate success or failure.
// In the case of success, the optional should have the value of the integer number,
// which might be negative.
//
// We assume that the passed string_view contains only one encoding, and the last character
// of a valid encoding is 'e'. Therefore, you do not need to handle cases like 'i4ei42e'.
//
// Example of a valid encoding: "i42e", which should be parsed to the integer 42.
// Example of a valid encoding: "i-42e", which should be parsed to the integer -42.
//
// Edges cases you might need to look out for:
// - String not starting with 'i', or ending with 'e'
// - Handle empty string
// - Handle if a non-digit number is between 'i' and 'e'

consteval std::optional<int> parse_int(std::string_view str) {
    if (str.empty() || str[0] != 'i' || str.back() != 'e') {
        return std::nullopt;  // Not a valid integer encoding
    }
    if (str[0] == 'i' && str[1] == 'e') {
        return std::nullopt; 
    }

    int result = 0;
    bool is_negative = false;
    size_t index = 1;

    if (str[1] == '-') {
        is_negative = true;
        ++index;
    }

    for (; index < str.size() - 1; ++index) {
        if (str[index] >= '0' && str[index] <= '9') {
            result = result * 10 + (str[index] - '0');
        } else {
            return std::nullopt;  // Found non-digit character
        }
    }

    return is_negative ? -result : result;
}

// TODO: Implement byte string parsing for the bencode fromat
// Bencode byte strings have the format <length>:<string>, where `length` is a number.
// The colon ':' separates the length and the actual string.
// The function returns a `std::optional<std::string_view>` to indicate success or failure.
// In the case of success, the optional should have the value of the string.
// For failure, the optional should be empty.
//
// Example of a valid byte string: "5:hello", where the length is 5, and the string is "hello".
//
// You may assume that all characters in the byte string are ASCII characters.
//
// We do not check for all edge cases, important edgecases your implementation should handle:
// - The byte string doesn't start with a number
// - The byte string doesn't have a colon
// - It is fine for the length to be shorter than the string, just return the string according to the length
// - It is NOT valid for the string to be shorter than the specified length
// - The string may contain colons

consteval std::optional<std::string_view> parse_byte_string(std::string_view str) {
    size_t colon_pos = str.find(':');
    if (colon_pos == std::string_view::npos) {
        return std::nullopt;  // Colon not found
    }

    int length = 0;
    for (size_t i = 0; i < colon_pos; ++i) {
        if (!(str[i] >= '0' && str[i] <= '9')) {
            return std::nullopt;  // Invalid length encoding
        }
        length = length * 10 + (str[i] - '0');
    }

    if (length + colon_pos + 1 > str.size()) {
        return std::nullopt;  // Length specified is longer than available string
    }

    return str.substr(colon_pos + 1, length);
}
} // namespace bencode
