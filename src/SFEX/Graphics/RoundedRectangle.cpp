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
#include <SFEX/Graphics/RoundedRectangle.hpp>

namespace sfex
{

RoundedRectangle::RoundedRectangle(const sfex::Vec2 &size, float cornerRadius, std::size_t cornerPointCount): m_size(size), m_cornerPointCount(cornerPointCount)
{
    setCornerRadius(cornerRadius);
}

void RoundedRectangle::setSize(const sfex::Vec2 &size)
{
    m_size = size;
}

void RoundedRectangle::setSize(float width, float height)
{
    setSize({width, height});
}

sfex::Vec2 RoundedRectangle::getSize() const
{
    return m_size;
}

void RoundedRectangle::setCornerRadius(float cornerRadius)
{
    if(cornerRadius > std::min(m_size.x, m_size.y) / 2)
        m_cornerRadius = std::min(m_size.x, m_size.y) / 2;
    else
        m_cornerRadius = cornerRadius;
}

float RoundedRectangle::getCornerRadius() const
{
    return m_cornerRadius;
}

void RoundedRectangle::setCornerPointCount(std::size_t cornerPointCount)
{
    m_cornerPointCount = cornerPointCount;
}

std::size_t RoundedRectangle::getCornerPointCount() const
{
    return m_cornerPointCount;
}

std::size_t RoundedRectangle::getPointCount() const
{
    return 4 * m_cornerPointCount;
}

sf::Vector2f RoundedRectangle::getPoint(std::size_t index) const 
{
    // Ninety degrees as radians
    const float ninetyDegrees = 1.570796327;
    
    if(index <= m_cornerPointCount)
    {
        float angle = float(index) * ninetyDegrees / float(m_cornerPointCount);
        return {
            m_cornerRadius * (1 - std::cos(angle)),
            m_cornerRadius * (1 - std::sin(angle)),
        };
    }
    else if(index <= 2 * m_cornerPointCount)
    {
        float angle = float(index - m_cornerPointCount) * ninetyDegrees / float(m_cornerPointCount);
        return {
            (m_size.x - m_cornerRadius) + m_cornerRadius * std::cos(ninetyDegrees - angle),
            m_cornerRadius * (1 - std::sin(ninetyDegrees - angle)),
        };
    }
    else if(index <= 3 * m_cornerPointCount)
    {
        float angle = float(index - 2 * m_cornerPointCount) * ninetyDegrees / float(m_cornerPointCount);
        return {
            (m_size.x - m_cornerRadius) + m_cornerRadius * std::cos(angle),
            (m_size.y - m_cornerRadius) + m_cornerRadius * std::sin(angle),
        };
    }

    float angle = float(index -= 3 * m_cornerPointCount) * ninetyDegrees / float(m_cornerPointCount);
    return {
        m_cornerRadius * (1 - std::cos(ninetyDegrees - angle)),
        (m_size.y - m_cornerRadius) + m_cornerRadius * std::sin(ninetyDegrees - angle),
    };
}

} // namespace sfex
