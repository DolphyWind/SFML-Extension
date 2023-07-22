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

#include <SFEX/Numeric/AngleSystem.hpp>

namespace sfex
{

const AngleSystem AngleSystem::degrees(360.0f);
const AngleSystem AngleSystem::radians(sfex::Math::tau);
const AngleSystem AngleSystem::revolutions(1.0f);

AngleSystem::AngleSystem(float period): m_period(period)
{
}

void AngleSystem::setPeriod(float period)
{
    m_period = period;
}

float AngleSystem::getPeriod() const
{
    return m_period;
}

float AngleSystem::operator()(float value) const
{
    return toRadians(value);
}

float AngleSystem::operator()(const AngleSystem& to, float value) const
{
    return convertTo(to, value);
}

float AngleSystem::toRadians(float value) const
{
    return convertTo(AngleSystem::radians, value);
}

float AngleSystem::convertTo(const AngleSystem &to, float value) const
{
    return to.getPeriod() * value / m_period;
}

}