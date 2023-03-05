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

#ifndef _SFEX_GRAPHICS_SQUIRCLE_HPP_
#define _SFEX_GRAPHICS_SQUIRCLE_HPP_

#include <SFML/Graphics/Shape.hpp>
#include <SFEX/Numeric/Vector2.hpp>
#include <SFEX/Numeric/Math.hpp>
#include <cmath>

namespace sfex
{

/// @brief A squircle class based on x^4 + y^4 = r^4 definition.
/// I'll post mathemathical background soon in a pdf format or maybe as a medium article. (If I don't forget)
class Squircle : public sf::Shape
{
public:

    /// @brief Main constructor
    /// @param radius Radius of squircle
    /// @param pointCount Number of points composing the squircle
    Squircle(float radius=0, std::size_t m_pointCount=30U);

    /// @brief Change the radius of the squircle
    /// @param radius New radius of squircle
    void setRadius(float radius);

    /// @brief Get the radius of the squircle
    /// @return Radius of squircle
    float getRadius() const;

    /// @brief Set number of points of the squircle
    /// @param pointCount New number of points of the squircle
    void setPointCount(std::size_t pointCount);

    /// @brief Get number of points of the squircle
    /// @return Number of points of the squircle
    virtual std::size_t getPointCount() const override;

    /// @brief Returns the coordinates of point corresponding to the index in local coordinates
    /// @param index The index of the point to get
    /// @return Coordinates of index-th point on the squircle
    virtual sf::Vector2f getPoint(std::size_t index) const override;

private:

    float m_radius;
    std::size_t m_pointCount;

};

} // namespace sfex


#endif // !_SFEX_GRAPHICS_SQUIRCLE_HPP_