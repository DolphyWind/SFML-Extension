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

#ifndef _SFEX_NUMERIC_VECTOR_HPP_
#define _SFEX_NUMERIC_VECTOR_HPP_

// Headers
#include <array>
#include <cmath>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

namespace sfex
{

template<typename T>
class Vector2
{
public:
    T x;
    T y;

    Vector2();
    Vector2(const T &x, const T &y);

    double magnitude() const;
    void setMagnitude(double magnitude);
    void normalize();
    Vector2 normalized();
    T dot(const Vector2<T> &right);
    void scale(const T &scalar);
    Vector2 scaled(const T &scalar) const;

    bool operator==(const Vector2 &right) const;
    bool operator!=(const Vector2 &right) const;

    Vector2<T> operator+=(const Vector2 &right);
    Vector2<T> operator+(const Vector2 &right) const;

    Vector2<T> operator-=(const Vector2 &right);
    Vector2<T> operator-(const Vector2 &right) const;
    Vector2<T> operator-() const;

    Vector2<T> operator*=(const T &scalar);
    Vector2<T> operator*(const T &scalar) const;
    T operator*(const Vector2 &right) const;

    Vector2<T> operator/=(const T &scalar);
    Vector2<T> operator/(const T &scalar) const;

    template<typename T2>
    sf::Vector2<T2> toSFMLVector() const;
    sf::Vector2f toVector2f() const;
    sf::Vector2i toVector2i() const;
    sf::Vector2u toVector2u() const;

    template<typename T2>
    operator sf::Vector2<T2>() const;
    
    static Vector2<T> fromSFML(const sf::Vector2<T> &sfVec);
    template<typename T2>
    Vector2<T> operator=(const sf::Vector2<T2> &right);

};

typedef Vector2<float> Vec2;

} // namespace sfex

#include <SFEX/Numeric/Vector2.inl>

#endif // !_SFEX_NUMERIC_VECTOR_HPP_