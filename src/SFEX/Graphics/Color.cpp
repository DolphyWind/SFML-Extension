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
#include <SFEX/Graphics/Color.hpp>

namespace sfex
{

Color::Color(): sf::Color()
{
}

Color::Color(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a): sf::Color(r, g, b, a)
{
}

Color Color::operator+=(const Color &rhs)
{
    // Prevent overflowing
    if(255 - rhs.r <= this->r) this->r = 255;
    else this->r += rhs.r;

    if(255 - rhs.g <= this->g) this->g = 255;
    else this->g += rhs.g;

    if(255 - rhs.b <= this->b) this->b = 255;
    else this->b += rhs.b;

    if(255 - rhs.a <= this->a) this->a = 255;
    else this->a += rhs.a;
    
    return *this;
}

Color Color::operator+(const Color &rhs) const
{
    Color result = *this;
    return (result += rhs);
}

Color Color::operator-=(const Color &rhs)
{
    // Prevent underflowing
    if(rhs.r > this->r) this->r = 0;
    else this->r -= rhs.r;

    if(rhs.g > this->g) this->g = 0;
    else this->g -= rhs.g;

    if(rhs.b > this->b) this->b = 0;
    else this->b -= rhs.b;

    if(rhs.a > this->a) this->a = 0;
    else this->a -= rhs.a;
    
    return *this;
}

Color Color::operator-(const Color &rhs) const
{
    Color result = *this;
    return (result -= rhs);
}

Color Color::operator*=(float scalar)
{
    // Prevent overflowing
    if(scalar > float(255) / float(this->r)) this->r = 255;
    else this->r *= scalar;

    if(scalar > float(255) / float(this->g)) this->g = 255;
    else this->g *= scalar;

    if(scalar > float(255) / float(this->b)) this->b = 255;
    else this->b *= scalar;

    if(scalar > float(255) / float(this->a)) this->a = 255;
    else this->a *= scalar;

    return *this;
}

Color Color::operator*(float scalar) const
{
    Color result = *this;
    return (result *= scalar);
}

Color Color::operator/=(float scalar)
{
    return (*this) *= (1/scalar);
}

Color Color::operator/(float scalar) const
{
    Color result = *this;
    return (result /= scalar);
}

const Color Color::Black = Color(0, 0, 0, 255);
const Color Color::Blue = Color(0, 0, 255, 255);
const Color Color::Cyan = Color(0, 255, 255, 255);
const Color Color::Magenta = Color(255, 0, 255, 255);
const Color Color::Green = Color(0, 255, 0, 255);
const Color Color::Red = Color(255, 0, 0, 255);
const Color Color::White = Color(255, 255, 255, 255);
const Color Color::Yellow = Color(255, 255, 0, 255);
const Color Color::Transparent = Color(0, 0, 0, 0);

} // namespace sfex
