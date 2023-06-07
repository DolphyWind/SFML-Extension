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
#include <SFEX/Graphics/Star.hpp>

namespace sfex
{

Star::Star(std::size_t numberOfCorners, float innerRadius, float outerRadius):
    m_numberOfCorners(numberOfCorners), m_innerRadius(innerRadius), m_outerRadius(outerRadius)
{
    this->update();
}

Star::Star()
    : m_numberOfCorners(5), m_innerRadius(40.0f), m_outerRadius(100.0f)
{
    this->update();
}

void Star::setNumberOfCorners(std::size_t nCorners)
{
    m_numberOfCorners = nCorners;
    this->update();
}

std::size_t Star::getNumberOfCorners() const
{
    return m_numberOfCorners;
}

void Star::setInnerRadius(float innerRadius)
{
    m_innerRadius = innerRadius;
    this->update();
}

float Star::getInnerRadius() const
{
    return m_innerRadius;
}

void Star::setOuterRadius(float outerRadius)
{
    m_outerRadius = outerRadius;
    this->update();
}

float Star::getOuterRadius() const
{
    return m_outerRadius;
}

std::size_t Star::getPointCount() const
{
    return m_numberOfCorners * 2;
}

sf::Vector2f Star::getPoint(std::size_t index) const
{
    // If the index is even, return a point on the outer polygon
    if( (index & 1) == 0)
    {
        index = index / 2;
        float angle = (sfex::Math::tau / m_numberOfCorners) * index;
        return m_outerRadius * sfex::Vec2{std::sin(angle), -std::cos(angle)};
    }

    // If the index is odd, return a point on the inner polygon
    index = (index - 1) / 2;
    float angle = (sfex::Math::tau / m_numberOfCorners) * index + sfex::Math::pi / m_numberOfCorners;
    return m_innerRadius * sfex::Vec2{std::sin(angle), -std::cos(angle)};
}

}