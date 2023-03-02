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

#ifndef _SFEX_GRAPHICS_COLOR_HPP_
#define _SFEX_GRAPHICS_COLOR_HPP_

#include <SFML/Graphics/Color.hpp>
#include <SFEX/Numeric/Math.hpp>

namespace sfex
{

/// @brief Extends sf::Color class. Overloads a lot of operators.
class Color : public sf::Color
{
public:

Color();
Color(const sf::Color &color);
Color(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a=255);

Color operator+=(const Color &rhs);
Color operator+(const Color &rhs) const;

Color operator-=(const Color &rhs);
Color operator-(const Color &rhs) const;

Color operator*=(float scalar);
Color operator*(float scalar) const;

Color operator/=(float scalar);
Color operator/(float scalar) const;

bool operator==(const Color &rhs);
bool operator!=(const Color &rhs);

/// @brief Mixes two colors with each other. Shorthand for lerp(a, b, 0.5)
/// @param a first color
/// @param b second color
/// @return Mixed color
static Color mixColors(const Color &a, const Color &b);

const static Color Black;
const static Color Blue;
const static Color Cyan;
const static Color Magenta;
const static Color Green;
const static Color Red;
const static Color White;
const static Color Yellow;
const static Color Transparent;

private:
};

sfex::Color operator*(float scalar, const sfex::Color &color);

} // namespace sfex

#endif // !_SFEX_GRAPHICS_COLOR_HPP_