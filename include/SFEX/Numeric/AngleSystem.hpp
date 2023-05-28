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

#ifndef _SFEX_NUMERIC_ANGLESYSTEM_HPP_
#define _SFEX_NUMERIC_ANGLESYSTEM_HPP_

#include <SFEX/Numeric/Math.hpp>

namespace sfex
{

/// @brief A class for representing angle measurement systems.
class AngleSystem
{
public:
    /// @brief Construct a new angle masurement system
    /// @param period Period of the angle measurement system
    AngleSystem(float period);

    /// @brief Set the period of the angle measurement system
    /// @param period New period of the angle measurement system
    void setPeriod(float period);

    /// @brief Get the period of the angle measurement system
    /// @return Period of the angle measurement system
    float getPeriod() const;

    /// @brief Convert an angle from this angle measurement system to radians
    /// @param value Angle to convert
    /// @return Given angle converted to radians
    float operator()(float value) const;

    /// @brief Convert an angle from this angle measurement system to the specified angle system
    /// @param to Angle measurement system to convert to
    /// @param value Angle to convert
    /// @return Given value converted to given angle measurement system
    float convertTo(const AngleSystem &to, float value) const;

    static const AngleSystem degrees;
    static const AngleSystem radians;
    static const AngleSystem revolutions;

private:
    float m_period;
};

}

#endif // !_SFEX_NUMERIC_ANGLESYSTEM_HPP_