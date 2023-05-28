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

#include <SFEX/Numeric/Math.hpp>

namespace sfex
{

template<typename T>
int Math::sign(const T &val)
{
    return (T() < val) - (val < T());
}

template<typename T>
T Math::abs(const T &val)
{
    return val * Math::sign(val);
}

template<typename T>
bool Math::isClose(const T &first, const T &second, const T &tolerance)
{
    return Math::abs(first - second) < tolerance;
}

float Math::deg2rad(float val)
{
    return val * Math::pi / 180.0f;
}

float Math::rad2deg(float val)
{
    return val * 180.0f / (Math::pi);
}

template<typename T>
T Math::cos(T value)
{
    return std::cos(value);
}

template<typename T>
T Math::sin(T value)
{
    return std::sin(value);
}

template<typename T>
T Math::tan(T value)
{
    return std::tan(value);
}

template<typename T>
T Math::sec(T value)
{
    return (1.0f / Math::cos(value));
}

template<typename T>
T Math::csc(T value)
{
    return (1.0f / Math::sin(value));
}

template<typename T>
T Math::cot(T value)
{
    return (1.0f / Math::tan(value));
}

template<typename T>
T Math::arccos(T value)
{
    return std::acos(value);
}

template<typename T>
T Math::arcsin(T value)
{
    return std::asin(value);
}

template<typename T>
T Math::arctan(T value)
{
    return std::atan(value);
}

template<typename T>
T Math::arctan2(T y, T x)
{
    return std::atan2(y, x);
}

template<typename T>
T Math::arcsec(T value)
{
    return std::acos(1 / value);
}

template<typename T>
T Math::arccsc(T value)
{
    return std::asin(1 / value);
}

template<typename T>
T Math::arccot(T value)
{
    return Math::half_pi - std::atan(value);
}

template<typename T>
T Math::lerp(const T &A, const T &B, float time, bool bounded)
{
    if(bounded) time = std::clamp(time, 0.0f, 1.0f);
    return A * (1.0f - time) + B * time;
}

template<typename T>
T Math::bezier(const std::vector<T> &points, float time, bool bounded)
{
    if(points.size() == 0) return T();
    if(points.size() == 1) return points[0];
    if(points.size() == 2) return Math::lerp(points[0], points[1], time, bounded);
    return Math::lerp(
        Math::bezier(
            std::vector<T>(points.begin(), points.end() - 1),
            time,
            bounded
        ),
        Math::bezier(
            std::vector<T>(points.begin() + 1, points.end()),
            time,
            bounded
        ),
        time,
        bounded
    );
}

} // namespace sfex
