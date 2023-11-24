#include "vector.h"

#include <iterator>
#include <algorithm>
#include <iostream>


namespace linalg {

    /// Construct non-initialized vector with given size
    Vector::Vector(std::size_t n) {
        std::vector<float> tempVector(n);
        this->data_ = tempVector;
    }

    /// Construct vector with given size and initialized with the given value
    Vector::Vector(std::size_t n, float val) {
        std::vector<float> tempVector(n, val);
        this->data_ = tempVector;
    }

    /// Construct vector with initialize list
    Vector::Vector(std::initializer_list<float> list) {
        std::vector<float> tempVector = list;
        
        this->data_ = tempVector;
    }

    /// Assign the given value to the vector, all coefficients in the vector are
    /// then equal to `val`
    auto Vector::operator=(float val) -> Vector & {
        Vector& copy = *this;
        for (auto & item : copy) {
            item = val;
        }
        return copy;
    }

    /// Assign a value to the vector, all coefficients in the vector are then
    /// equal to `val`
    auto Vector::assign(float val) -> void {
        for (auto & item : data_) {
            item = val;
        }
    }

    /// Assign `v` to this vector. The size and all coefficients are then equal to
    /// the coefficients of `v`.
    auto Vector::assign(Vector v) -> void {
        *this = v;
    }

    /// Return the size of the vector
    auto Vector::size() const -> std::size_t {
        return this->data_.size();
    }

    /// Return an begin iterator to the vector
    auto Vector::begin() -> iterator {
        return this->data_.begin();
    }

    /// Return an end iterator to the vector
    auto Vector::end() -> iterator {
        return this->data_.end();
    }

    /// Return an begin const_iterator to the vector
    auto Vector::begin() const -> const_iterator {
        return this->data_.cbegin();

    }

    /// Return an end const_iterator to the vector
    auto Vector::end() const -> const_iterator {
        return this->data_.cend();
    }

    /// Return an begin const_iterator to the vector
    auto Vector::cbegin() const -> const_iterator {
        return this->data_.cbegin();
    }

    /// Return an end const_iterator to the vector
    auto Vector::cend() const -> const_iterator {
         return this->data_.cend();
    }

    /// Access a modifiable reference to the idx-th element of the vector.#
    ///
    /// Additionally a python like behaviour access of negative indices should be
    /// possible. I.e. `vec[-1]` should return the last value in the vector It
    /// should only be wrapped once. I.e. given a vector of length 10, `vec[-15]`
    /// does not need to be supported. Also note that accessing values above the
    /// size of the vector is also undefined.
    auto Vector::operator[](int idx) -> float & {
        if (idx >= 0) {
           float & ref = this->data_[idx];
           return ref;
        }
        else {
            float & ref = data_[idx + data_.size()];
            return ref;
        }
    
    }

    /// Access a non-modifiable reference to the idx-th element of the vector.
    ///
    /// Additionally a python like behaviour access of negative indices should be
    /// possible. I.e. `vec[-1]` should return the last value in the vector. It
    /// should only be wrapped once. I.e. given a vector of length 10, `vec[-15]`
    /// does not need to be supported. Also note that accessing values above the
    /// size of the vector is also undefined.
    auto Vector::operator[](int idx) const -> const float &{
        if (idx >= 0) {
            return this->data_[idx];
        }
        else {
            return data_[idx + data_.size()];
        }
    }

    /// Access a modifiable reference to the idx-th element of the vector. No
    /// wrapping behaviour should be implemented.
    ///
    /// Throw an `std::out_of_range` exception if the index out of bounds.
    auto Vector::coeff(int idx) -> float & {
      
        if (idx >= 0 && idx < data_.size()){
            float & ref = data_[idx];
            return ref;
        } else {
            throw std::out_of_range("Out of range!");
        }

    }

    /// Access a non-modifiable reference to the idx-th element of the vector. No
    /// wrapping behaviour should be implemented.
    ///
    /// Throw an `std::out_of_range` exception if the index out of bounds.
    auto Vector::coeff(int idx) const -> const float & {
        
        if (idx >= 0 && idx < data_.size()){
            return data_[idx];
        } else {
            throw std::out_of_range("Out of range!");
        }

    }

    /* In place operators, modify the given Vector in-place, rather than a copy */

    /// Add a scalar value to the vector, i.e. for each coefficient `v_i` of the
    /// vector, the values after this operators are `v_i + val`
    auto Vector::operator+=(float val) -> Vector & {
        for (auto & item : data_){
            item += val;
        }
        Vector & ref = *this;
        return ref;
    }

    /// Subtract a scalar value from the vector, i.e. for each coefficient `v_i`
    /// of the vector, the values after this operators are `v_i - val`
    auto Vector::operator-=(float val) -> Vector & {
        for (auto & item : data_){
            item -= val;
        }
        Vector & ref = *this;
        return ref;

    }

    /// Multiply vector with a scalar, i.e. for each coefficient `v_i`
    /// of the vector, the values after this operators are `v_i * val`
    auto Vector::operator*=(float val) -> Vector & {
        for (auto & item : data_){
            item *= val;
        }
        Vector & ref = *this;
        return ref;

    }

    /// Divide vector by a scalar, i.e. for each coefficient `v_i`
    /// of the vector, the values after this operators are `v_i / val`
    auto Vector::operator/=(float val) -> Vector & {
        for (auto & item : data_){
            item /= val;
        }
        Vector & ref = *this;
        return ref;

    }

    /// In-place addition of two vectors, given the coefficients `x_i` and `y_i`
    /// of the vectors respectively, a new vector is returned, where the
    /// coefficients are equal to `x_i` + `y_i`
    ///
    /// Throw an `std::invalid_argument` exceptions, if the given vector is of a
    /// different size
    auto Vector::operator+=(const Vector &y) -> Vector & {
        if (data_.size() != y.size()) {
            throw std::invalid_argument("Size not equal!");
        }
        for (size_t i = 0; i < data_.size(); ++i){
            data_[i] += y[i];
        }
        Vector & ref = *this;
        return ref;
    }


    /// In-place addition of two vectors, given the coefficients `x_i` and `y_i`
    /// of the vectors respectively, a new vector is returned, where the
    /// coefficients are equal to `x_i` - `y_i`
    ///
    /// Throw an `std::invalid_argument` exceptions, if the given vector is of a
    /// different size
    auto Vector::operator-=(const Vector &y) -> Vector & {
        if (data_.size() != y.size()) {
            throw std::invalid_argument("Size not equal!");
        }
        for (std::size_t i = 0; i < data_.size(); ++i){
            data_[i] -= y[i];
        }
        Vector & ref = *this;
        return ref;
    }

    
auto operator<<(std::ostream& ostr, const Vector& x) -> std::ostream& {
    ostr << "[ ";
    std::copy(x.begin(), x.end(), std::ostream_iterator<float>(ostr, " "));
    ostr << "]";
    return ostr;
}

/// Return the minimum value of Vector
///
/// Throw an `std::invalid_argument` exceptions, if the given vector is empty.
auto min(const Vector &x) -> float {
    if (x.size() == 0) {
        throw std::invalid_argument("Empty vector!");
    }
    return *std::min_element(x.begin(), x.end());

}

/// Return the maximum value of Vector
///
/// Throw an `std::invalid_argument` exceptions, if the given vector is empty.
auto max(const Vector &x) -> float {
    if (x.size() == 0) {
        throw std::invalid_argument("");
    }
    return *std::max_element(x.begin(), x.end());

}

/// Return the index into the vector of the minimum value of Vector
///
/// Throw an `std::invalid_argument` exceptions, if the given vector is empty.
auto argmin(const Vector &x) -> std::size_t {
    if (x.size() == 0) {
        throw std::invalid_argument("");
    }

    return std::distance(x.begin(), std::min_element(x.begin(), x.end()));
}

/// Return the index into the vector of the maximum value of Vector
///
/// Throw an `std::invalid_argument` exceptions, if the given vector is empty.
auto argmax(const Vector &x) -> std::size_t {
    if (x.size() == 0) {
        throw std::invalid_argument("");
    }
    
    return std::distance(x.begin(), std::max_element(x.begin(), x.end()));
}

/// Return the number of non-zero elements in the vector
auto non_zeros(const Vector &x) -> std::size_t {
    std::size_t number{0};
    for (auto item : x){
        if (std::abs(item) > 1e-6) {
            number += 1;
        }
    }
    return number;
}

/// Return the sum of the coefficients of the given vector
auto sum(const Vector &x) -> float {
    float number{0.0f};
    for (auto item : x){
        number += item;
    }
    return number;


}

/// Return the product of the coefficients of the given vector
auto prod(const Vector &x) -> float {
    float number{1.0f};
    for (auto item : x){
        number *= item;
    }
    return number;

}

/// Return the dot product of the two vectors. i.e. the sum of products of the
/// coefficients: `sum(x_i * y_i) forall i in [0, x.size())`
///
/// Throw an `std::invalid_argument` exceptions, if the given vector is of a
/// different size
auto dot(const Vector &x, const Vector &y) -> float {
    if (x.size() != y.size()) {
        throw std::invalid_argument("Size not equal!");
    }
    float number{0.0f};
    for (std::size_t i = 0; i < x.size(); ++i) {
        number += x[i] * y[i];
    }
    return number;

}

/// Return the euclidean norm of the vector. i.e. the sum of the square of the
/// coefficients: `sum(x_i * x_i) forall i in [0, x.size())`
auto norm(const Vector &x) -> float {
    float number{0.0f};
    for (std::size_t i = 0; i < x.size(); ++i) {
        number += x[i] * x[i];
    }
    return std::sqrt(number);
}

/// Normalize the vector, i.e. the norm should be 1 after the normalization
auto normalize(Vector &x) -> void {
    float total_num = norm(x);
    for (auto & item : x) {
        item /= total_num;
    }
}

/// Return a normalized copy of the vector
auto normalized(const Vector &x) -> Vector {
    Vector copy = x;

    float total_num = norm(x);
    for (auto & item : copy) {
        item /= total_num;
    }
    return copy;

}

/// Return a copy for which every coefficient is the floored, i.e. `v_i =
/// floor(x_i)`
auto floor(const Vector &x) -> Vector {
    Vector copy = x;
    for (auto & item : copy) {
        item = std::floor(item);
    }
    return copy;

}

/// Return a copy for which every coefficient is the ceiled, i.e. `v_i =
/// ceil(x_i)`
auto ceil(const Vector &x) -> Vector {
    Vector copy = x;

    for (auto & item : copy) {
        item = std::ceil(item);
    }
    return copy;
}

/// Unary operator+, returns a copy of x
auto operator+(const Vector &x) -> Vector {
    Vector copy = x;
    return copy;

}

/// Unary operator-, returns a copy of x, where all values are negated , i.e.
/// `v_i = -x_i`
auto operator-(const Vector &x) -> Vector {
    Vector copy = x;
    for (auto & item : copy) {  
            item = -item;  
    }

    return copy;
}

/// Return a vector, for which every coefficient is the sum of the coefficients
/// of the arguments
auto operator+(const Vector &x, const Vector &y) -> Vector {
    Vector copy = x;
    for (std::size_t i = 0; i < x.size(); ++i){
        copy[i] += y[i];
    }
    return copy;

}

/// Return a vector, for which every coefficient is the subtraction of the
/// coefficients of the arguments
auto operator-(const Vector &x, const Vector &y) -> Vector {
    Vector copy = x;
    for (std::size_t i = 0; i < x.size(); ++i){
        copy[i] -= y[i];
    }
    return copy;

}

/// Return a vector, which is the addition of each coefficient of the given
/// vector and the scalar
auto operator+(const Vector &x, float val) -> Vector {
    Vector copy = x;
    copy += val;
    return copy;
}

/// Return a vector, which is the subtraction of each coefficient of the given
/// vector and the scalar
auto operator-(const Vector &x, float val) -> Vector {
    Vector copy = x;
    copy -= val;
    return copy;
}

/// Return a vector, which is the multiplication of each coefficient of the
/// given vector and the scalar
auto operator*(const Vector &x, float val) -> Vector {
    Vector copy = x;
    copy *= val;
    return copy;
}

/// Return a vector, which is the division of each coefficient of the given
/// vector and the scalar
auto operator/(const Vector &x, float val) -> Vector {
    Vector copy = x;
    copy /= val;
    return copy;
}

/// Return a vector, which is the addition of each coefficient of the given
/// vector and the scalar
auto operator+(float val, const Vector &x) -> Vector {
    Vector copy = x;
    copy += val;
    return copy;
}

/// Return a vector, which is the subtraction of each coefficient of the given
/// vector and the scalar
auto operator-(float val, const Vector &x) -> Vector {
    Vector copy = x;
    for (auto & item : copy){
        item = val - item;
    }
    return copy;
}

/// Return a vector, which is the multiplication of each coefficient of the
/// given vector and the scalar
auto operator*(float val, const Vector &x) -> Vector {
    Vector copy = x;
    copy *= val;
    return copy;
}




}



/*
 * Please Implement all functions from the header file here!#
 * Have fun! :-) And don't forget maybe you can use standard algorithms ;-)
 */
