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

#ifndef _SFEX_NUMERIC_MATH_HPP_
#define _SFEX_NUMERIC_MATH_HPP_

// Headers
#include <cmath>
#include <limits>
#include <vector>
#include <complex>

namespace sfex
{

class Math
{
public:
    /// @brief Ratio of a circle's circumference to its diameter.
    static const float pi;

    /// @brief Ratio of a circle's circumference to its radius. Equals to 2*pi.
    static const float tau;

    /// @brief Euler's number
    static const float e;

    /// @brief The golden ratio. Namely (1+sqrt(5))/2
    static const float phi;

    /// @brief The smallest positive number that can be represented as double
    static const float positiveMin;

    /// @brief The difference between 1 and the smallest value greater than 1 that is representable by a double
    static const float epsilon;

    /// @brief Returns the sign of val.
    template<typename T>
    static int sign(const T &val);

    /// @brief Returns the absoulte value of val.
    template<typename T>
    static T abs(const T &val);

    /// @brief Returns true if abs(first - second) is < tolerance
    template<typename T>
    static bool isClose(const T &first, const T &second, const T &tolerance);

    /// @brief Converts value from degrees to radians
    /// @param value value you want to convert
    /// @returns value in radians
    static float deg2rad(float value);

    /// @brief Converts value from radians to degrees
    /// @param value value you want to convert
    /// @returns value in degrees
    static float rad2deg(float value);

    /// @brief Linear interpolation between A and B.
    template<typename T>
    static T lerp(const T &A, const T &B, float t, bool bounded=true);

    /// @brief Recursive bezier curve computation function
    template<typename T>
    static T bezier(const std::vector<T> &points, float t, bool bounded=true);

protected:
    Math() {};
};

} // namespace sfex

#include <SFEX/Numeric/Math.inl>

#endif // !_SFEX_NUMERIC_MATH_HPP_