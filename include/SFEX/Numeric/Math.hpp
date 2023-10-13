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

#ifndef _SFEX_NUMERIC_MATH_HPP_
#define _SFEX_NUMERIC_MATH_HPP_

// Headers
#include <SFEX/General/StaticClass.hpp>
#include <cmath>
#include <limits>
#include <vector>
#include <tuple>
#include <algorithm>
#define SFEX_MATHDEF static inline

namespace sfex
{

/// @brief A math class that contains some math constants and functions. Only contains static methods and constants so it doesn't meant to be instantiated.
class Math : StaticClass
{
public:

    /// @brief A functor that adds two different types of objects
    /// @tparam LeftType The type of the object on the left
    /// @tparam RightType The type of the object on the right
    template<typename LeftType, typename RightType>
    struct Adder
    {
        auto operator()(const LeftType& left, const RightType& right) -> decltype(left + right);
    };

    /// @brief A functor that subtracts two different types of objects
    /// @tparam LeftType The type of the object on the left
    /// @tparam RightType The type of the object on the right
    template<typename LeftType, typename RightType>
    struct Subtracter
    {
        auto operator()(const LeftType& left, const RightType& right) -> decltype(left - right);
    };

    /// @brief A functor that multiplies two different types of objects
    /// @tparam LeftType The type of the object on the left
    /// @tparam RightType The type of the object on the right
    template<typename LeftType, typename RightType>
    struct Multiplier
    {
        auto operator()(const LeftType& left, const RightType& right) -> decltype(left * right);
    };

    /// @brief A functor that divides two different types of objects
    /// @tparam LeftType The type of the object on the left
    /// @tparam RightType The type of the object on the right
    template<typename LeftType, typename RightType>
    struct Divider
    {
        auto operator()(const LeftType& left, const RightType& right) -> decltype(left / right);
    };

    /// @brief A functor that modulos two different types of objects
    /// @tparam LeftType The type of the object on the left
    /// @tparam RightType The type of the object on the right
    template<typename LeftType, typename RightType>
    struct Modulo
    {
        auto operator()(const LeftType& left, const RightType& right) -> decltype(left % right);
    };

    /// @brief A functor that takes the square root of given object
    /// @tparam Type Type of the object you want to take the square root of
    template<typename Type>
    struct SqrtTaker
    {
        auto operator()(const Type& input) -> decltype(std::sqrt(input));
    };

    /// @brief Half of the famous mathematical constant pi
    SFEX_MATHDEF constexpr float half_pi = 1.57079632679f;

    /// @brief Ratio of a circle's circumference to its diameter.
    SFEX_MATHDEF constexpr float pi = 3.1415926535f;

    /// @brief Ratio of a circle's circumference to its radius. Equals to 2*pi.
    SFEX_MATHDEF constexpr float tau = 6.2831853071f;

    /// @brief Euler's number
    SFEX_MATHDEF constexpr float e = 2.7182818284f;

    /// @brief The golden ratio. Namely (1+sqrt(5))/2
    SFEX_MATHDEF constexpr float phi = 1.6180339887f;

    /// @brief The smallest positive number that can be represented as float
    SFEX_MATHDEF const float positiveMin = std::nextafterf(0.0f, 1.0f);

    /// @brief The difference between 1 and the smallest value greater than 1 that is representable by a float
    SFEX_MATHDEF constexpr float epsilon = std::numeric_limits<float>::epsilon();

    /// @brief Returns the sign of val. Can be applied to any type as long as it supports less than operator.
    template<typename T>
    SFEX_MATHDEF int sign(const T &val);

    /// @brief Returns the absoulte value of the given value.
    template<typename T>
    SFEX_MATHDEF T abs(const T &val);

    /// @brief Returns true if abs(first - second) is less that the tolerance
    template<typename T>
    SFEX_MATHDEF bool isClose(const T &first, const T &second, const T &tolerance);

    /// @brief Converts value from degrees to radians
    /// @param value value you want to convert
    /// @returns value in radians
    SFEX_MATHDEF float deg2rad(float value);

    /// @brief Converts value from radians to degrees
    /// @param value value you want to convert
    /// @returns value in degrees
    SFEX_MATHDEF float rad2deg(float value);

    /// @brief Calculates the cosine of the given value.
    /// @param value The value you want to calculate the cosine of.
    /// @return Cosine of the given value.
    template<typename T>
    SFEX_MATHDEF T cos(T value);

    /// @brief Calculates the sine of the given value.
    /// @param value The value you want to calculate the sine of.
    /// @return Sine of the given value.
    template<typename T>
    SFEX_MATHDEF T sin(T value);

    /// @brief Calculates the tangent of the given value.
    /// @param value The value you want to calculate the tangent of.
    /// @return Tangent of the given value.
    template<typename T>
    SFEX_MATHDEF T tan(T value);

    /// @brief Calculates the secant of the given value.
    /// @param value The value you want to calculate the secant of.
    /// @return Secant of the given value.
    template<typename T>
    SFEX_MATHDEF T sec(T value);

    /// @brief Calculates the cosecant of the given value.
    /// @param value The value you want to calculate the cosecant of.
    /// @return Cosecant of the given value.
    template<typename T>
    SFEX_MATHDEF T csc(T value);

    /// @brief Calculates the cotangent of the given value.
    /// @param value The value you want to calculate the cotangent of.
    /// @return Cotangent of the given value.
    template<typename T>
    SFEX_MATHDEF T cot(T value);

    /// @brief Calculates the inverse cosine of the given value.
    /// @param value The value you want to calculate the inverse cosine of.
    /// @return Inverse cosine of the given value.
    template<typename T>
    SFEX_MATHDEF T arccos(T value);

    /// @brief Calculates the inverse sine of the given value.
    /// @param value The value you want to calculate the inverse sine of.
    /// @return Inverse sine of the given value.
    template<typename T>
    SFEX_MATHDEF T arcsin(T value);

    /// @brief Calculates the inverse tangent of the given value.
    /// @param value The value you want to calculate the inverse tangent of.
    /// @return Inverse tangent of the given value.
    template<typename T>
    SFEX_MATHDEF T arctan(T value);

    /// @brief Calculates the inverse tangent of the ratio y/x
    /// @param y numerator of the ratio
    /// @param x denominator of the ratio
    /// @return Invers tangent of the ration y / x
    template<typename T>
    SFEX_MATHDEF T arctan2(T y, T x);

    /// @brief Calculates the inverse secant of the given value.
    /// @param value The value you want to calculate the inverse secant of.
    /// @return Inverse secant of the given value.
    template<typename T>
    SFEX_MATHDEF T arcsec(T value);

    /// @brief Calculates the inverse cosecant of the given value.
    /// @param value The value you want to calculate the inverse cosecant of.
    /// @return Inverse cosecant of the given value.
    template<typename T>
    SFEX_MATHDEF T arccsc(T value);

    /// @brief Calculates the inverse cotangent of the given value.
    /// @param value The value you want to calculate the inverse cotangent of.
    /// @return Inverse cotangent of the given value.
    template<typename T>
    SFEX_MATHDEF T arccot(T value);

    /// @brief Calculates linear interpolation between A and B. Namely A*(1-t) + B*t
    /// @param A The value at time=0
    /// @param B The value at time=1
    /// @param time Time value
    /// @param bounded If true, time is forced to be between 0 and 1 (both inclusive)
    /// @return Linear interpolation between A and B. Namely A*(1-t) + B*t
    template<typename T, typename AdderType=Adder<T, T>, typename MultiplierType=Multiplier<T, float>>
    SFEX_MATHDEF T lerp(const T &A, const T &B, float time, bool bounded=true);

    /// @brief Recursively calculates the point on the bézier curve based on give time
    /// @param points Points to construct bézier curve
    /// @param time Time value
    /// @param bounded If true, time is forced to be between 0 and 1 (both inclusive)
    /// @return Calculated point on the bézier curve
    template<typename T, typename AdderType=Adder<T, T>, typename MultiplierType=Multiplier<T, float>>
    SFEX_MATHDEF T bezier(const std::vector<T> &points, float time, bool bounded=true);
};

} // namespace sfex

#include <SFEX/Numeric/Math.inl>

#endif // !_SFEX_NUMERIC_MATH_HPP_
