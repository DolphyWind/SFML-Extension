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

// Headers
#include <SFEX/Graphics/Ellipse.hpp>

namespace sfex
{

Ellipse::Ellipse(const sfex::Vec2 &radius, std::size_t pointCount): m_radius(radius), m_pointCount(pointCount)
{
}

Ellipse::Ellipse(float horizontalRadius, float verticalRadius, std::size_t pointCount): m_pointCount(pointCount)
{
    m_radius = {horizontalRadius, verticalRadius};
}

void Ellipse::setRadius(const sfex::Vec2 &radius)
{
    m_radius = radius;
    this->update();
}

void Ellipse::setRadius(float horizontalRadius, float verticalRadius)
{
    m_radius = {horizontalRadius, verticalRadius};
    this->update();
}

void Ellipse::setHorizontalRadius(float horizontalRadius)
{
    m_radius.x = horizontalRadius;
    this->update();
}

void Ellipse::setVerticalRadius(float verticalRadius)
{
    m_radius.y = verticalRadius;
    this->update();
}

sfex::Vec2 Ellipse::getRadius() const
{
    return m_radius;
}

float Ellipse::getHorizontalRadius() const
{
    return m_radius.x;
}

float Ellipse::getVerticalRadius() const
{
    return m_radius.y;
}

void Ellipse::setPointCount(std::size_t pointCount)
{
    m_pointCount = pointCount;
    this->update();
}

std::size_t Ellipse::getPointCount() const
{
    return m_pointCount;
}

sf::Vector2f Ellipse::getPoint(std::size_t index) const
{
    float angle = index * 2 * Math::pi / m_pointCount - Math::pi / 2;
    sfex::Vec2 coords;
    coords.x = m_radius.x + m_radius.x * std::cos(angle);
    coords.y = m_radius.y + m_radius.y * std::sin(angle);

    return coords;
}

} // namespace sfex
