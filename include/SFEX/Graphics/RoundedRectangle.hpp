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

#ifndef _SFEX_GRAPHICS_ROUNDEDRECTANGLE_HPP_
#define _SFEX_GRAPHICS_ROUNDEDRECTANGLE_HPP_

#include <SFML/Graphics/ConvexShape.hpp>
#include <SFEX/Numeric/Vector2.hpp>
#include <SFEX/Numeric/Math.hpp>
#include <vector>

namespace sfex
{

class RoundedRectangle : public sf::Shape
{
public:

    /// @brief Default contructor
    /// @param size Size of the rounded rectangle
    /// @param cornerRadius Number of ponits of each corner
    explicit RoundedRectangle(const sfex::Vec2 &size = sfex::Vec2::zero, float cornerRadius=5);

    /// @brief Changes the size of the rounded rectangle
    /// @param size New size of the rounded rectangle
    void setSize(const sfex::Vec2 &size);

    /// @brief Changes the size of the rounded rectangle
    /// @param width New width of the rounded rectangle
    /// @param height New height of the rounded rectangle
    void setSize(float width, float height);

    /// @brief Returns the size of the rounded rectangle
    /// @return Size of the rounded rectangle
    sfex::Vec2 getSize() const;

    /// @brief Changes the radius of the rounded rectangle
    /// @param radius New radius of the rounded rectangle
    void setCornerRadius(float radius);

    /// @brief Returns the radius of the rounded rectangle
    /// @return The radius of the rounded rectangle
    float getCornerRadius() const;

    /// @brief Changes the point count of each corner
    /// @param cornerPointCount New point count of each corner
    void setCornerPointCount(std::size_t cornerPointCount);

    /// @brief Returns the point count of each corner
    /// @return The point count of each corner
    std::size_t getCornerPointCount() const;

    /// @brief Returns the number of points in the shape
    /// @return The number of the points in the shape
    virtual std::size_t getPointCount() const override;

    /// @brief Returns the coordinates of point corresponding to the index
    /// @param index The index of the point
    /// @return Coordinates of point corresponding to the index
    virtual sf::Vector2f getPoint(std::size_t index) const override;

private:

    sfex::Vec2 m_size;
    float m_cornerRadius;
    std::size_t m_cornerPointCount;
    std::vector<sf::Vector2f> m_points;
    void updatePoints();

};

} // namespace sfex


#endif // !_SFEX_GRAPHICS_ROUNDEDRECTANGLE_HPP_