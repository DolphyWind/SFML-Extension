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

// Headers
#include <SFEX/Graphics/Squircle.hpp>

namespace sfex
{

Squircle::Squircle(float radius, std::size_t pointCount): m_radius(radius), m_pointCount(pointCount)
{
}

void Squircle::setRadius(float radius)
{
    m_radius = radius;
    this->update();
}

float Squircle::getRadius() const
{
    return m_radius;
}

void Squircle::setPointCount(std::size_t pointCount)
{
    m_pointCount = pointCount;
    this->update();
}

std::size_t Squircle::getPointCount() const
{
    return m_pointCount;
}

sf::Vector2f Squircle::getPoint(std::size_t index) const
{
    float angle = index * 2 * Math::pi / m_pointCount - Math::pi / 2;
    float ro = (std::pow(2.f, 0.25f) * m_radius) / std::pow(2 - std::sin(2 * angle) * std::sin(2 * angle), 0.25f);

    sfex::Vec2 coords(std::cos(angle), std::sin(angle));
    coords *= ro;
    coords += sfex::Vec2::one * m_radius;

    return coords;
}

} // namespace sfex
