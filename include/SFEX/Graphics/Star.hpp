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

#ifndef _SFEX_GRAPHICS_STAR_HPP_
#define _SFEX_GRAPHICS_STAR_HPP_
#include <SFML/Graphics/Shape.hpp>
#include <SFEX/Numeric/Vector2.hpp>
#include <SFEX/Numeric/Math.hpp>
#include <iostream>

namespace sfex
{

/// @brief A star shape. Uses 2 polygons to draw a star. Does this by connecting a point of the first polygon with some point on the second polygon.
class Star : public sf::Shape
{
public:
    /// @brief Main constructor
    /// @param numberOfCorners Number of corners that the star shape has
    /// @param innerRadius Radius of the inner polygon
    /// @param outerRadius Radius of the outer polygon
    explicit Star(std::size_t numberOfCorners, float innerRadius, float outerRadius);

    /// @brief Create a star shape with default values.
    /// Number of corners: 5
    /// Inner radius: 40.0f
    /// Outer radius: 100.0f
    Star();

    /// @brief Set the number of corners that the star shape has
    /// @param nCorners New number of corners that the star shape has
    void setNumberOfCorners(std::size_t nCorners);

    /// @brief Get the number of corners that the star shape has
    /// @return Number of corners that the star shape has
    std::size_t getNumberOfCorners() const;
    
    /// @brief Set the radius of the inner polygon
    /// @param innerRadius New radius of the inner polygon
    void setInnerRadius(float innerRadius);

    /// @brief Get the radius of the inner polygon
    /// @return Radius of the inner polygon
    float getInnerRadius() const;
    
    /// @brief Set the radius of the outer polygon
    /// @param outerRadius New radius of the outer polygon
    void setOuterRadius(float outerRadius);

    /// @brief Get the radius of the outer polygon
    /// @return Radius of the outer polygon
    float getOuterRadius() const;

    /// @brief Get number of points of the star shape
    /// @return Number of points of the star shape
    virtual std::size_t getPointCount() const override;

    /// @brief Returns the coordinates of point corresponding to the index in local coordinates
    /// @param index The index of the point to get
    /// @return Coordinates of index-th point on the star shape
    virtual sf::Vector2f getPoint(std::size_t index) const override;
private:
    std::size_t m_numberOfCorners;
    float m_innerRadius;
    float m_outerRadius;
};

}

#endif //!_SFEX_GRAPHICS_STAR_HPP_