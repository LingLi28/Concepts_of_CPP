#pragma once

#include <algorithm>
#include <memory>
#include <ostream>
#include <stdexcept>

template <typename T>
class Vector {
public:
    /**
     * TODO: Define the following associated types (i.e. `using blabla = T`, then blabla is an associated type)
     *       - `size_type`: should be an unsigned integer type
     *       - `difference_type`: should be a signed integer type
     *       - `reference`: reference to value_type
     *       - `const_reference`: const reference to value_type
     *       - `pointer`: pointer to value_type
     *       - `const_pointer`: const pointer to value_type
     *       - `iterator`: a random access iterator to the underlying data
     *       - `const_iterator`: a random access iterator to the underlying data
     *       - `reverse_iterator`: a random access iterator to the underlying data
     *       - `const_reverse_iterator`: a random access iterator to the underlying data
     *
     *       All of these are types aliases, and all of them are easy. Check e.g. the reference
     *       of `std::vector` (hint, pointers are iterators too), check reverse
     */
    using value_type = T;

    Vector() = default;

    /**
     * Creates a vector of size n with values default_val.
     */
    Vector(size_type n, const_reference default_val) {
    }

    /**
     * Creates a vector containing the elements in l.
     */
    Vector(std::initializer_list<value_type> l) {
    }

    Vector(const Vector& copy) : _size(copy._size), _capacity(copy._capacity) {
    }

    Vector(Vector&& move) : _size(move._size), _capacity(move._capacity) {
    }

    /**
     * Replaces the contents of the vector.
     */
    Vector& operator=(const Vector& copy) {
    }


    /**
     * Replaces the contents of the vector.
     */
    Vector& operator=(Vector&& move) noexcept {
    }

    size_type size() const noexcept { return _size; }

    size_type capacity() const noexcept { return _capacity; }

    /**
     * Appends the given element value to the end of the vector.
     */
    void push_back(const_reference value) {
    }

    /**
     * Appends the given element value to the end of the vector.
     */
    void push_back(T&& value) {
    }

    /**
     * Removes the last element of the vector.
     */
    void pop_back() {
    }

    /**
     * Returns a reference to the element at specified location pos, with bounds checking.
     * If pos is not within the range of the vector, an exception of type std::out_of_range is thrown.
     */
    reference at(const size_type pos) const {
    }

    /**
     * Returns a reference to the element at specified location pos, with bounds checking.
     * If pos is not within the range of the vector, an exception of type std::out_of_range is thrown.
     */
    reference at(const size_type pos) {
    }

    /**
     * Returns a reference to the element at specified location pos.
     * No bounds checking is performed.
     */
    const_reference operator[](size_type index) const {
    }

    /**
     * Returns a reference to the element at specified location pos.
     * No bounds checking is performed.
     */
    reference operator[](const size_type index) {
    }

    // TODO: implement: 
    //           - begin, end (both const and non-const)
    //           - cbegin, cend,
    //           - rbegin, rend (const and non-const)
    //           - crbegin, crend (see e.g. https://en.cppreference.com/w/cpp/iterator/rbegin)
    //       This isn't necessarily very complicated, but a little tiresome, but that's part of C++ (yeah....)

    /**
     * Stream a Vector to an output stream textually.
     */
    friend std::ostream& operator<<(std::ostream& o, Vector<value_type> v) {
        o << "Size: " << v._size << ", Capacity: " << v._capacity << std::endl;
        for (size_type i = 0; i < v._size; ++i) {
            if (i > 0)
                o << ", ";
            o << v._data[i];
        }
        o << std::endl;
        return o;
    }

    ~Vector() = default;

private:
    // Defines how the `_capacity` is increased.
    size_type growth_factor = 2;
    size_type _size;
    size_type _capacity;

    // Holds vector's data.
    std::unique_ptr<value_type[]> _data;

    /**
     * Calculates the necessary capacity for new_size.
     * If necessary, double `_capacity` using `growth_factor`.
     */
    size_type calculate_capacity(size_type new_size) {
    }

    /**
     * Resizes the vector to new_capacity.
     * If the current capacity is less than new_capacity
     * the vector moves all elements to a new array.
     */
    void resize(size_type new_capacity) {
    }
};
