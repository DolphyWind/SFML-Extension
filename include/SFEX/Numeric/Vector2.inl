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
#ifndef _SFEX_NUMERIC_VECTOR2_INL_
#define _SFEX_NUMERIC_VECTOR2_INL_

// Headers
#include <SFEX/Numeric/Vector2.hpp>
#include <ostream>

namespace sfex
{

template<typename T>
Vector2<T>::Vector2(): sf::Vector2<T>(T(), T())
{
}

template<typename T>
template<typename V>
Vector2<T>::Vector2(const sf::Vector2<V> &sfVec):
    sf::Vector2<T>(sfVec)
{
}

template<typename T>
template<typename V>
Vector2<T>::Vector2(const sfex::Vector2<V>& otherVec):
    sf::Vector2<T>(otherVec)
{
}

template<typename T>
Vector2<T>::Vector2(const T &_x, const T &_y): sf::Vector2<T>(_x, _y)
{
}

template<typename T>
float Vector2<T>::magnitude() const
{
    return std::sqrt(this->magnitude2());
}

template<typename T>
float Vector2<T>::magnitude2() const
{
    return (this->x*this->x + this->y*this->y);
}

template<typename T>
void Vector2<T>::setMagnitude(float magnitude)
{
    float mag = this->magnitude();
    this->x *= (magnitude / mag);
    this->y *= (magnitude / mag);
}

template<typename T>
void Vector2<T>::normalize()
{
    this->setMagnitude(1);
}

template<typename T>
Vector2<T> Vector2<T>::normalized() const
{
    Vector2<T> resultVector = *this;
    resultVector.normalize();
    return resultVector;
}

template<typename T>
template<typename V>
auto Vector2<T>::dot(const Vector2<V> &rhs) const -> typename std::common_type<T, V>::type
{
    return this->x * rhs.x + this->y * rhs.y;
}

template<typename T>
T Vector2<T>::dot(const Vector2<T> &rhs) const
{
    return this->x * rhs.x + this->y * rhs.y;
}

template<typename T>
template<typename V>
auto Vector2<T>::cross(const Vector2<V> &rhs) const -> typename std::common_type<T, V>::type
{
    return this->x * rhs.y - this->y * rhs.x;
}

template<typename T>
T Vector2<T>::cross(const Vector2<T> &rhs) const
{
    return this->x * rhs.y - this->y * rhs.x;
}

template<typename T>
template<typename V>
auto Vector2<T>::cwiseMul(const Vector2<V> &rhs) const -> Vector2<typename std::common_type<T, V>::type>
{
    return {this->x * rhs.x, this->y * rhs.y};
}

template<typename T>
Vector2<T> Vector2<T>::cwiseMul(const Vector2<T> &rhs) const
{
    return {this->x * rhs.x, this->y * rhs.y};
}

template<typename T>
template<typename V>
auto Vector2<T>::cwiseDiv(const Vector2<V> &rhs) const -> Vector2<typename std::common_type<T, V>::type>
{
    return {this->x / rhs.x, this->y / rhs.y};
}

template<typename T>
Vector2<T> Vector2<T>::cwiseDiv(const Vector2<T> &rhs) const
{
    return {this->x / rhs.x, this->y / rhs.y};
}


template<typename T>
template<typename V>
void Vector2<T>::scale(const V &scalar)
{
    *this = this->cwiseMul({scalar, scalar});
}

template<typename T>
template<typename V>
auto Vector2<T>::scaled(const V &scalar) const -> Vector2<typename std::common_type<T, V>::type>
{
    Vector2<typename std::common_type<T, V>::type> resultVector = *this;
    resultVector.scale(scalar);
    return resultVector;
}

template<typename T>
void Vector2<T>::rotate(float angle, const Vector2<T> &rotateAround)
{
    Vector2<T> resultVector = *this - rotateAround;
    resultVector = {resultVector.x * std::cos(angle) - resultVector.y * std::sin(angle), resultVector.x * std::sin(angle) + resultVector.y * std::cos(angle)};
    *this = resultVector + rotateAround;
}

template<typename T>
Vector2<T> Vector2<T>::rotated(float angle, const Vector2<T> &rotateAround) const
{
    Vector2<T> resultVector = *this;
    resultVector.rotate(angle, rotateAround);
    return resultVector;
}

template<typename T>
float Vector2<T>::angle(const Vector2<T> &other)
{
    return std::acos(this->dot(other) / (this->magnitude() * other.magnitude()));
}

template<typename T>
void Vector2<T>::projectOnto(const Vector2<T> &rhs)
{
    float magnitude_squared = rhs.magnitude() * rhs.magnitude();
    *this = rhs * this->dot(rhs)/magnitude_squared;
}

template<typename T>
Vector2<T> Vector2<T>::projectedOnto(const Vector2<T> &rhs) const
{
    Vector2<T> resultVector = *this;
    resultVector.projectOnto(rhs);
    return resultVector;
}

//////////////////////////////////////////////////////////
// Logical operators
//////////////////////////////////////////////////////////

template<typename T>
bool Vector2<T>::operator==(const Vector2<T> &rhs) const
{
    return (this->x == rhs.x) && (this->y == rhs.y);
}

template<typename T>
bool Vector2<T>::operator!=(const Vector2<T> &rhs) const
{
    return !(*this == rhs);
}

//////////////////////////////////////////////////////////
// Addition
//////////////////////////////////////////////////////////

template<typename T>
Vector2<T> Vector2<T>::operator+=(const Vector2 &rhs)
{
    this->x += rhs.x;
    this->y += rhs.y;
    return *this;
}

template<typename T>
Vector2<T> Vector2<T>::operator+(const Vector2 &rhs) const
{
    Vector2<T> resultVector = *this;
    return (resultVector += rhs);
}

//////////////////////////////////////////////////////////
// Subtraction
//////////////////////////////////////////////////////////

template<typename T>
Vector2<T> Vector2<T>::operator-=(const Vector2 &rhs)
{
    this->x -= rhs.x;
    this->y -= rhs.y;
    return *this;
}

template<typename T>
Vector2<T> Vector2<T>::operator-(const Vector2 &rhs) const
{
    Vector2<T> resultVector = *this;
    return (resultVector -= rhs);
}

template<typename T>
Vector2<T> Vector2<T>::operator-() const
{
    Vector2<T> resultVector;
    resultVector.x = -this->x;
    resultVector.y = -this->y;
    return resultVector;
}

//////////////////////////////////////////////////////////
// Multiplication
//////////////////////////////////////////////////////////

template<typename T>
Vector2<T> Vector2<T>::operator*=(const T &scalar)
{
    this->scale(scalar);
    return *this;
}

template<typename T>
Vector2<T> Vector2<T>::operator*(const T &scalar) const
{
    Vector2<T> resultVector = *this;
    return (resultVector *= scalar);
}

template<typename T>
Vector2<T> operator*(const T &scalar, const Vector2<T> &vec)
{
    return vec.scaled(scalar);
}

//////////////////////////////////////////////////////////
// Division
//////////////////////////////////////////////////////////

template<typename T>
Vector2<T> Vector2<T>::operator/=(const T &scalar)
{
    this->x /= scalar;
    this->y /= scalar;
    return *this;
}

template<typename T>
Vector2<T> Vector2<T>::operator/(const T &scalar) const
{
    Vector2<T> resultVector = *this;
    return (resultVector /= scalar);
}

//////////////////////////////////////////////////////////
// SFML Vector Conversion
//////////////////////////////////////////////////////////

template<typename T>
template<typename T2>
sf::Vector2<T2> Vector2<T>::toSFMLVector() const
{
    return sf::Vector2<T2>(T2(this->x), T2(this->y));
}

template<typename T>
sf::Vector2f Vector2<T>::toVector2f() const
{
    return toSFMLVector<float>();
}

template<typename T>
sf::Vector2i Vector2<T>::toVector2i() const
{
    return toSFMLVector<int>();
}

template<typename T>
sf::Vector2u Vector2<T>::toVector2u() const
{
    return toSFMLVector<unsigned int>();
}

template<typename T>
template<typename T2>
Vector2<T>::operator sf::Vector2<T2>() const
{
    return toSFMLVector<T2>();
}

template<typename T>
template<typename T2>
Vector2<T> Vector2<T>::operator=(const sf::Vector2<T2> &rhs)
{
    (*this) = {static_cast<T>(rhs.x), static_cast<T>(rhs.y)};
    return *this;
}

//////////////////////////////////////////////////////////
// Ostream
//////////////////////////////////////////////////////////

template<typename T>
std::ostream &operator<<(std::ostream &left, const sfex::Vector2<T> &right)
{
    return left << "(x: " << right.x << ", y: " << right.y << ")";
}

//////////////////////////////////////////////////////////
// Static properties
//////////////////////////////////////////////////////////

template<typename T>
const Vector2<T> Vector2<T>::one = {1, 1};
template<typename T>
const Vector2<T> Vector2<T>::zero = {0, 0};
template<typename T>
const Vector2<T> Vector2<T>::up = {0, 1};
template<typename T>
const Vector2<T> Vector2<T>::down = {0, -1};
template<typename T>
const Vector2<T> Vector2<T>::left = {-1, 0};
template<typename T>
const Vector2<T> Vector2<T>::right = {1, 0};

} // namespace sfex

#endif // !_SFEX_NUMERIC_VECTOR3_INL_