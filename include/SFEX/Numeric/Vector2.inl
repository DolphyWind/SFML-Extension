// MIT License

// Copyright (c) 2023 Yunus Emre Aydın

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <SFEX/Numeric/Vector2.hpp>

namespace sfex
{

template<typename T>
Vector2<T>::Vector2(): x(T(0)), y(T(0))
{
}

template<typename T>
Vector2<T>::Vector2(const T &_x, const T &_y): x(_x), y(_y) 
{
}

template<typename T>
double Vector2<T>::getMagnitude() const
{
    return std::sqrt(x*x + y*y);
}

template<typename T>
void Vector2<T>::setMagnitude(double magnitude)
{
    double mag = this->getMagnitude();
    x *= (magnitude / mag);
    y *= (magnitude / mag);
}

template<typename T>
void Vector2<T>::normalize()
{
    this->setMagnitude(1);
}

template<typename T>
Vector2<T> Vector2<T>::normalized()
{
    Vector2<T> resultVector = *this;
    resultVector.normalize();
    return resultVector;
}

template<typename T>
T Vector2<T>::dot(const Vector2<T> &right)
{
    return x * right.x + y * right.y;
}

template<typename T>
void Vector2<T>::scale(const T &scalar)
{
    x *= scalar;
    y *= scalar;
}

template<typename T>
Vector2<T> Vector2<T>::scaled(const T &scalar) const 
{
    Vector2<T> resultVector = *this;
    resultVector.scale(scalar);
    return resultVector;
}

//////////////////////////////////////////////////////////
// Logical operators
//////////////////////////////////////////////////////////

template<typename T>
bool Vector2<T>::operator==(const Vector2<T> &right) const
{
    return (x == right.x) && (y == right.y);
}

template<typename T>
bool Vector2<T>::operator!=(const Vector2<T> &right) const
{
    return !(*this == right);
}

//////////////////////////////////////////////////////////
// Addition
//////////////////////////////////////////////////////////

template<typename T>
Vector2<T> Vector2<T>::operator+=(const Vector2 &right)
{
    x += right.x;
    y += right.y;
    return *this;
}

template<typename T>
Vector2<T> Vector2<T>::operator+(const Vector2 &right) const
{
    Vector2<T> resultVector = *this;
    return (resultVector += right);
}

//////////////////////////////////////////////////////////
// Subtraction
//////////////////////////////////////////////////////////

template<typename T>
Vector2<T> Vector2<T>::operator-=(const Vector2 &right)
{
    x -= right.x;
    y -= right.y;
    return *this;
}

template<typename T>
Vector2<T> Vector2<T>::operator-(const Vector2 &right) const
{
    Vector2<T> resultVector = *this;
    return (resultVector -= right);
}

template<typename T>
Vector2<T> Vector2<T>::operator-() const
{
    Vector2<T> resultVector;
    resultVector.x = -x;
    resultVector.y = -y;
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
T Vector2<T>::operator*(const Vector2 &right) const
{
    return this->dot(right);
    return T(0);
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
    this->scale(1 / scalar);
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
    return sf::Vector2<T2>(T2(x), T2(y));
}

template<typename T>
sf::Vector2f Vector2<T>::toVector2f() const
{
    return {float(x), float(y)};
}

template<typename T>
sf::Vector2i Vector2<T>::toVector2i() const
{
    return {int(x), int(y)};
}

template<typename T>
sf::Vector2u Vector2<T>::toVector2u() const
{
    return {unsigned(x), unsigned(y)};
}

template<typename T>
template<typename T2>
Vector2<T>::operator sf::Vector2<T2>() const
{
    return toSFMLVector<T2>();
}

template<typename T>
Vector2<T>::operator sf::Vector2<float>() const
{
    return toVector2f();
}

template<typename T>
Vector2<T>::operator sf::Vector2<int>() const
{
    return toVector2i();
}

template<typename T>
Vector2<T>::operator sf::Vector2<unsigned>() const
{
    return toVector2u();
}

// No need to call this TemporaryFunction() function,
// it's just to avoid link error.
void TemporaryFunction ()
{
    Vector2<int> TempObj;
}

} // namespace sfex
