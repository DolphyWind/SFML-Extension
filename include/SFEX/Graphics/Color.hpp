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

#ifndef _SFEX_GRAPHICS_COLOR_HPP_
#define _SFEX_GRAPHICS_COLOR_HPP_

#include <SFML/Graphics/Color.hpp>
#include <SFEX/Numeric/Math.hpp>
#include <cstdint>
#include <ostream>

namespace sfex
{

/// @brief A class that extends sf::Color
class Color : public sf::Color
{
public:

    Color();
    Color(std::uint32_t u32);
    Color(const sf::Color &color);
    Color(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a=255);
    
    /// @brief Add rhs to this color component by component 
    /// @param rhs The color you want to add 
    /// @param noalpha If set to true, function does not touch alpha values when performing the operation
    /// @return Result of addition
    Color add(const Color &rhs, bool noalpha=false) const;

    /// @brief Subtract rhs from this color
    /// @param rhs The color you want to subtract
    /// @param noalpha If set to true, function does not touch alpha values when performing the operation
    /// @return Result of subtraction
    Color subtract(const Color &rhs, bool noalpha=false) const;

    /// @brief Multiply this color with a scalar
    /// @param scalar Scalar you want to multiply with
    /// @param noalpha If set to true, function does not touch alpha values when performing the operation
    /// @return Result of multiplication
    Color multiply(float scalar, bool noalpha=false) const;

    /// @brief Divide this color by scalar
    /// @param scalar Scalar you want to divide by
    /// @param noalpha If set to true, function does not touch alpha values when performing the operation
    /// @return Result of division
    Color divide(float scalar, bool noalpha=false) const;
    
    Color operator+=(const Color &rhs);
    Color operator+(const Color &rhs) const;

    Color operator-=(const Color &rhs);
    Color operator-(const Color &rhs) const;

    Color operator*=(float scalar);
    Color operator*(float scalar) const;

    Color operator/=(float scalar);
    Color operator/(float scalar) const;

    inline bool operator==(const Color &rhs);
    inline bool operator!=(const Color &rhs);

    /// @brief Returns the hexadecimal representation of sfex::Color
    /// @return Hexadecimal representation of sfex::Color
    std::uint32_t toHex() const;
    
    /// @brief Returns the hexadecimal representation of sfex::Color
    /// @return Hexadecimal representation of sfex::Color
    operator std::uint32_t() const;

    /// @brief Converts any hexadecimal number into sfex::Color
    /// @param hex Number to convert
    /// @return The resulting Color after the conversion
    static Color fromHex(std::uint32_t hex);

    /// @brief Mixes two colors with each other. Shorthand for sfex::Math::lerp(a, b, 0.5f).
    /// @param a first color
    /// @param b second color
    /// @return Mixed color
    static Color mixColors(const Color &a, const Color &b);

    /// @brief Converts this color to grayscale
    /// @return Result of conversion
    Color toGrayscale() const;

    const static Color Red;
    const static Color Green;
    const static Color Blue;
    const static Color Yellow;
    const static Color Magenta;
    const static Color Cyan;
    const static Color Gray;
    const static Color White;
    const static Color Black;
    const static Color Transparent;
};

sfex::Color operator*(float scalar, const sfex::Color &color);
std::ostream &operator<<(std::ostream &left, const Color &right);

} // namespace sfex

#endif // !_SFEX_GRAPHICS_COLOR_HPP_