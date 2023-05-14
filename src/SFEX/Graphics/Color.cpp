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
#include <SFEX/Graphics/Color.hpp>
#include <SFML/Config.hpp>
#include <cstdint>

namespace sfex
{

Color::Color(): sf::Color()
{
}

Color::Color(std::uint32_t hex)
{
    *this = Color::fromHex(hex);
}

Color::Color(const sf::Color &color): sf::Color(color)
{
}

Color::Color(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a): sf::Color(r, g, b, a)
{
}

Color Color::add(const Color &rhs, bool noalpha) const
{
    Color resultColor = *this;
    
    resultColor.r = sf::Uint8(std::min(short(resultColor.r) + short(rhs.r), 255));
    resultColor.g = sf::Uint8(std::min(short(resultColor.g) + short(rhs.g), 255));
    resultColor.b = sf::Uint8(std::min(short(resultColor.b) + short(rhs.b), 255));
    if(!noalpha) resultColor.a = sf::Uint8(std::min(short(resultColor.a) + short(rhs.a), 255));

    return resultColor;
}

Color Color::operator+=(const Color &rhs)
{
    *this = this->add(rhs);
    return *this;
}

Color Color::operator+(const Color &rhs) const
{
    return this->add(rhs);
}

Color Color::subtract(const Color &rhs, bool noalpha) const
{
    Color resultColor = *this;

    resultColor.r = sf::Uint8(std::max(short(resultColor.r) - short(rhs.r), 0));
    resultColor.g = sf::Uint8(std::max(short(resultColor.g) - short(rhs.g), 0));
    resultColor.b = sf::Uint8(std::max(short(resultColor.b) - short(rhs.b), 0));
    if(!noalpha) resultColor.a = sf::Uint8(std::max(short(resultColor.a) - short(rhs.a), 0));

    return resultColor;
}

Color Color::operator-=(const Color &rhs)
{
    *this = this->subtract(rhs);
    return *this;
}

Color Color::operator-(const Color &rhs) const
{
    return this->subtract(rhs);
}

Color Color::multiply(float scalar, bool noalpha) const
{
    Color resultColor = *this;
    
    if(scalar < 0) return resultColor;

    resultColor.r = sf::Uint8(std::min(float(resultColor.r) * scalar, 255.0f));
    resultColor.g = sf::Uint8(std::min(float(resultColor.g) * scalar, 255.0f));
    resultColor.b = sf::Uint8(std::min(float(resultColor.b) * scalar, 255.0f));
    if(!noalpha) resultColor.a = sf::Uint8(std::min(float(resultColor.a) * scalar, 255.0f));

    return resultColor;
}

Color Color::operator*=(float scalar)
{
    *this = this->multiply(scalar);
    return *this;
}

Color Color::operator*(float scalar) const
{
    return this->multiply(scalar);
}

Color operator*(float scalar, const Color &color)
{
    return color.multiply(scalar);
}

Color Color::divide(float scalar, bool noalpha) const
{
    return this->multiply(1.f / scalar, noalpha);
}

Color Color::operator/(float scalar) const
{
    return this->divide(scalar);
}

Color Color::operator/=(float scalar)
{
    *this = this->divide(scalar);
    return *this;
}

bool Color::operator==(const Color &rhs)
{
    return (this->r == rhs.r) &&
           (this->g == rhs.g) &&
           (this->b == rhs.b) &&
           (this->a == rhs.a);
}

bool Color::operator!=(const Color &rhs)
{
    return !(*this == rhs);
}

std::uint32_t Color::toHex() const
{
    return (this->r << 24) | (this->g << 16) | (this->b << 8) | (this->a);
}

Color::operator std::uint32_t() const
{
    return this->toHex();
}

Color Color::fromHex(std::uint32_t hex)
{
    sf::Uint8 components[4];
    for(char i = 0; hex; i++)
    {
        components[i] = hex & 255;
        hex >>= 8;
    }
    return {
        components[3],
        components[2],
        components[1],
        components[0],
    };
}

Color Color::mixColors(const Color &a, const Color &b)
{
    return Math::lerp(a, b, 0.5f);
}

Color Color::toGrayscale() const
{
    // I divide each channel seperately to prevent overflowing
    std::uint32_t grayChannel = this->r / 3 + this-> g / 3 + this->b / 3;
    return Color(grayChannel, grayChannel, grayChannel, this->a);
}

std::ostream &operator<<(std::ostream &left, const Color &right)
{
    return left << "(r: " << +right.r << ", g: " << +right.g << ", b: " << +right.b << ", a: " << +right.a << ")";
}

const Color Color::Red = Color(255, 0, 0, 255);
const Color Color::Green = Color(0, 255, 0, 255);
const Color Color::Blue = Color(0, 0, 255, 255);
const Color Color::Yellow = Color(255, 255, 0, 255);
const Color Color::Magenta = Color(255, 0, 255, 255);
const Color Color::Cyan = Color(0, 255, 255, 255);
const Color Color::Gray = Color(128, 128, 128, 255);
const Color Color::White = Color(255, 255, 255, 255);
const Color Color::Black = Color(0, 0, 0, 255);
const Color Color::Transparent = Color(0, 0, 0, 0);

} // namespace sfex
