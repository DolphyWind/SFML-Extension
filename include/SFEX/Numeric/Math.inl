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

#include <SFEX/Numeric/Math.hpp>

namespace sfex
{

const float Math::pi = 3.1415926535;
const float Math::tau = 6.2831853071;
const float Math::e  = 2.7182818284;
const float Math::phi = 1.6180339887;
const float Math::positiveMin = nextafterf(0.0, 1.0);
const float Math::epsilon = std::numeric_limits<float>::epsilon();

template<typename T>
int Math::sign(const T &val)
{
    return (T(0) < val) - (val < T(0));
}

template<typename T>
T Math::abs(const T &val)
{
    return val * T(Math::sign(val));
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
T Math::lerp(const T &A, const T &B, float t, bool bounded)
{
    if(bounded)
    {
        if(t > 1) t = 1;
        if(t < 0) t = 0;
    }
    return A * (1 - t) + B * t;
}

template<typename T>
T Math::bezier(const std::vector<T> &points, float t, bool bounded)
{
    if(points.size() == 0) return T();
    if(points.size() == 1) return points[0];
    if(points.size() == 2) return Math::lerp(points[0], points[1], t, bounded);
    return Math::lerp(
        Math::bezier(
            std::vector<T>(points.begin(), points.end() - 1),
            t,
            bounded
        ),
        Math::bezier(
            std::vector<T>(points.begin() + 1, points.end()),
            t,
            bounded
        ),
        t,
        bounded
    );
}

} // namespace sfex
