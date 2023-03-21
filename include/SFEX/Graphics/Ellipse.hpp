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

#ifndef _SFEX_GRAPHICS_ELLIPSE_HPP_
#define _SFEX_GRAPHICS_ELLIPSE_HPP_

#include <SFML/Graphics/Shape.hpp>
#include <SFEX/Numeric/Vector2.hpp>
#include <SFEX/Numeric/Math.hpp>
#include <cmath>

namespace sfex
{

/// @brief An ellipse shape class.
class Ellipse : public sf::Shape
{
public:

    /// @brief Main constructor
    /// @param radius A 2D vector that contains horizontal and vertical coordinates respectively
    /// @param pointCount Number of points composing the ellipse
    explicit Ellipse(const sfex::Vec2 &radius=sfex::Vec2::zero, std::size_t pointCount=30);
    
    /// @brief Main constructor
    /// @param horizontalRadius Horizontal radius
    /// @param verticalRadius Vertical radius
    /// @param pointCount umber of points composing the circle
    explicit Ellipse(float horizontalRadius, float verticalRadius, std::size_t pointCount=30);

    /// @brief Changes the radius of the ellipse
    /// @param radius A 2D vector that contains new horizontal and vertical radius of the ellipse respectively
    void setRadius(const sfex::Vec2 &radius);
    
    /// @brief Changes the radius of the ellipse
    /// @param horizontalRadius New horizontal radius of the ellipse
    /// @param verticalRadius New vertical radius of the ellipse
    void setRadius(float horizontalRadius, float verticalRadius);

    /// @brief Changes the horizontal radius of the ellipse
    /// @param horizontalRadius New horizontal radius of the ellipse
    void setHorizontalRadius(float horizontalRadius);

    /// @brief Changes the vertical radius of the ellipse
    /// @param verticalRadius New vertical radius of the ellipse
    void setVerticalRadius(float verticalRadius);

    /// @brief Returns the current radius of ellipse as 2D vector
    /// @return Current radius of the ellipse as 2D vector
    sfex::Vec2 getRadius() const;

    /// @brief Returns the horizontal radius of the ellipse
    /// @return Horizontal radius of the ellipse
    float getHorizontalRadius() const;

    /// @brief Returns the vertical radius of the ellipse
    /// @return Vertical radius of the ellipse
    float getVerticalRadius() const;

    /// @brief Set number of points of the ellipse
    /// @param pointCount New number of points of the ellipse
    void setPointCount(std::size_t pointCount);

    /// @brief Get number of points of the ellipse
    /// @return Number of points of the ellipse
    virtual std::size_t getPointCount() const override;

    /// @brief Returns the coordinates of point corresponding to the index in local coordinates
    /// @param index The index of the point to get
    /// @return Coordinates of index-th point on the ellipse
    virtual sf::Vector2f getPoint(std::size_t index) const override;

private:

    sfex::Vec2 m_radius;
    std::size_t m_pointCount;

};

} // namespace sfex


#endif // !_SFEX_GRAPHICS_ELLIPSE_HPP_