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

#include <SFEX/General/Keyboard.hpp>

namespace sfex
{

std::unordered_map<sfex::Keyboard::Key, bool> Keyboard::m_keysForDown;
std::unordered_map<sfex::Keyboard::Key, bool> Keyboard::m_keysForUp;

bool Keyboard::getKey(sfex::Keyboard::Key key)
{
    return sf::Keyboard::isKeyPressed(key);
}

bool Keyboard::getKeyDown(sfex::Keyboard::Key key)
{
    if(m_keysForDown[key])
    {
        m_keysForDown[key] = Keyboard::getKey(key);
        return false;
    }
    m_keysForDown[key] = Keyboard::getKey(key);
    return m_keysForDown[key];
}

bool Keyboard::getKeyUp(sfex::Keyboard::Key key)
{
    if(m_keysForUp[key])
    {
        m_keysForUp[key] = Keyboard::getKey(key);
        return !m_keysForUp[key];
    }
    m_keysForUp[key] = Keyboard::getKey(key);
    return false;
}

} // namespace sfex
