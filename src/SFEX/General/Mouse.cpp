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

#include <SFEX/General/Mouse.hpp>

namespace sfex
{

std::unordered_map<sfex::Mouse::Button, bool> Mouse::m_buttonsForDown;
std::unordered_map<sfex::Mouse::Button, bool> Mouse::m_buttonsForUp;

bool Mouse::getButton(sfex::Mouse::Button button)
{
    return sf::Mouse::isButtonPressed(button);
}

bool Mouse::getButtonDown(sfex::Mouse::Button button)
{
    if(m_buttonsForDown[button])
    {
        m_buttonsForDown[button] = Mouse::getButton(button);
        return false;
    }
    m_buttonsForDown[button] = Mouse::getButton(button);
    return m_buttonsForDown[button];
}

bool Mouse::getButtonUp(sfex::Mouse::Button button)
{
    if(m_buttonsForUp[button])
    {
        m_buttonsForUp[button] = Mouse::getButton(button);
        return !m_buttonsForUp[button];
    }
    m_buttonsForUp[button] = Mouse::getButton(button);
    return false;
}


sfex::Vec2i Mouse::getPosition(const sf::Window *relativeTo)
{
    if(relativeTo) return sf::Mouse::getPosition(*relativeTo);
    return sf::Mouse::getPosition();
}

void Mouse::setPosition(const sfex::Vec2i &position, const sf::Window *relativeTo)
{
    if(relativeTo) sf::Mouse::setPosition(position, *relativeTo);
    else sf::Mouse::setPosition(position);
}

} // namespace sfex
