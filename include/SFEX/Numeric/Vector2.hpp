//
// MIT License
//
// Copyright (c) 2023 Yunus Emre Aydın
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#ifndef _SFEX_NUMERIC_VECTOR2_HPP_
#define _SFEX_NUMERIC_VECTOR2_HPP_

// Headers
#include <array>
#include <cmath>
#include <SFML/System/Vector2.hpp>
#include <ostream>

namespace sfex
{

/// @brief 2D Vector class that adds some linear algebra functions and operators to sf::Vector2<T>
template<typename T>
class Vector2 : public sf::Vector2<T>
{
public:
    /// @brief Default constructor. Creates a zero vector.
    Vector2();

    /// @brief Creates a sfex::Vector2<T> from SFML vector
    /// @param sfVec SFML vector
    Vector2(const sf::Vector2<T> &sfVec);

    /// @brief Creates a vector with components x and y
    Vector2(const T &x, const T &y);

    /// @brief Returns magnitude (length) of the vector
    /// @return Magnitude of the vector
    float magnitude() const;
    
    /// @brief Changes the vector's magnitude while keeping its direction same
    /// @param magnitude Target magnitude
    void setMagnitude(float magnitude);

    /// @brief Sets the vector's length to 1. Shorthand for setMagnitude(1) 
    void normalize();

    /// @brief Returns the normalized version of the vector
    /// @return Normalized version of vector
    Vector2<T> normalized() const;

    /// @brief Computates the dot product between this and rhs 
    /// @param rhs rhs vector
    /// @return Result of this . rhs
    T dot(const Vector2<T> &rhs);

    /// @brief Treats the vectors as three dimentional with z being equal to zero vectors and Computates the cross product between them. Returns the z component of the reult since x and y components are zero.
    /// @param rhs rhs vector
    /// @return Result of this x rhs
    T cross(const Vector2<T> &rhs);

    /// @brief Computates component-wise product aka hadamard product between two vectors
    /// @param rhs rhs vector
    /// @return Result of component-wise multiplication.
    Vector2<T> cwiseMul(const Vector2<T> &rhs);

    /// @brief Computates component-wise division aka hadamard division between two vectors
    /// @param rhs rhs vector
    /// @return Result of component-wise division.
    Vector2<T> cwiseDiv(const Vector2<T> &rhs);

    /// @brief Scales the vector with a scalar
    /// @param scalar scalar
    void scale(const T &scalar);

    /// @brief Returns a scaled version of the vector
    /// @param scalar scalar
    /// @return Scaled version of the vector
    Vector2<T> scaled(const T &scalar) const;

    /// @brief Rotates the vector around "rotateAround" vector by given angle.
    /// @param angle angle in radians
    /// @param rotateAround rotateAround vector (Defaults to Vector2<T>::zero)
    void rotate(float angle, const Vector2<T> &rotateAround = Vector2<T>::zero);

    /// @brief Returns Rotated version of the vector around "rotateAround" vector by given angle.
    /// @param angle angle in radians
    /// @param rotateAround rotateAround vector (Defaults to Vector2<T>::zero)
    /// @return Rotated version of vector
    Vector2<T> rotated(float angle, const Vector2<T> &rotateAround = Vector2<T>::zero) const;

    /// @brief Computates the angle between the vector and other vector
    /// @param other other vector. (Defaults to Vector2<T>::right)
    /// @return Angle between the vector and "other" as radians
    float angle(const Vector2<T> &other = Vector2<T>::right);

    /// @brief Projects this vector onto rhs vector
    /// @param rhs rhs vector
    void projectOnto(const Vector2<T> &rhs);

    /// @brief Returns projected version of this vector onto rhs vector
    /// @param rhs rhs vector
    /// @return Projected vector
    Vector2<T> projectedOnto(const Vector2<T> &rhs) const;
    
    bool operator==(const Vector2<T> &rhs) const;
    bool operator!=(const Vector2<T> &rhs) const;

    Vector2<T> operator+=(const Vector2<T> &rhs);
    Vector2<T> operator+(const Vector2<T> &rhs) const;

    Vector2<T> operator-=(const Vector2<T> &rhs);
    Vector2<T> operator-(const Vector2<T> &rhs) const;
    Vector2<T> operator-() const;

    Vector2<T> operator*=(const T &scalar);
    Vector2<T> operator*(const T &scalar) const;

    Vector2<T> operator/=(const T &scalar);
    Vector2<T> operator/(const T &scalar) const;

    /// @brief Converts sfex::Vector2<T> to sf::Vector2<T>
    /// @return Vector converted to sf::Vector2<T2>
    template<typename T2>
    sf::Vector2<T2> toSFMLVector() const;

    /// @brief Converts sfex::Vector2<T> to sf::Vector2f
    /// @return Vector converted to sf::Vector2f
    sf::Vector2f toVector2f() const;

    /// @brief Converts sfex::Vector2<T> to sf::Vector2i
    /// @return Vector converted to sf::Vector2i
    sf::Vector2i toVector2i() const;

    /// @brief Converts sfex::Vector2<T> to sf::Vector2u
    /// @return Vector converted to sf::Vector2u
    sf::Vector2u toVector2u() const;
    
    template<typename T2>
    operator sf::Vector2<T2>() const;
    
    template<typename T2>
    Vector2<T> operator=(const sf::Vector2<T2> &rhs);

    /// @brief Vector <1, 1>
    static const Vector2<T> one;

    /// @brief Vector <0, 0>
    static const Vector2<T> zero;

    /// @brief Vector <0, 1>
    static const Vector2<T> up;

    /// @brief Vector <0, -1>
    static const Vector2<T> down;

    /// @brief Vector <1, 0>
    static const Vector2<T> right;

    /// @brief Vector <-1, 0>
    static const Vector2<T> left;
};

typedef Vector2<float> Vec2;
typedef Vector2<int> Vec2i;
typedef Vector2<unsigned int> Vec2u;

template<typename T>
sfex::Vector2<T> operator*(const T &scalar, const sfex::Vector2<T> &vec);

template<typename T>
std::ostream &operator<<(std::ostream &left, const sfex::Vector2<T> &right);

} // namespace sfex

#include <SFEX/Numeric/Vector2.inl>

#endif // !_SFEX_NUMERIC_VECTOR2_HPP_