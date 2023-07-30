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

#include <SFEX/General/Keyboard.hpp>

namespace sfex
{

#ifdef SFEX_USE_UPDATE_BASED_INPUT_HANDLING
std::unordered_map<sfex::Keyboard::Key, bool> Keyboard::m_keyStates;
#else
std::unordered_map<sfex::Keyboard::Key, bool> Keyboard::m_keyStatesForDown;
std::unordered_map<sfex::Keyboard::Key, bool> Keyboard::m_keyStatesForUp;
#endif

bool Keyboard::getKey(sfex::Keyboard::Key key)
{
    return sf::Keyboard::isKeyPressed(key);
}

bool Keyboard::getKeyDown(sfex::Keyboard::Key key)
{
#ifdef SFEX_USE_UPDATE_BASED_INPUT_HANDLING
    if(!Keyboard::m_keyStates[key] && Keyboard::getKey(key))
    {
        return true;
    }
    return false;
#else
    if(Keyboard::m_keyStatesForDown[key])
    {
        Keyboard::m_keyStatesForDown[key] = Keyboard::getKey(key);
        return false;
    }
    Keyboard::m_keyStatesForDown[key] = Keyboard::getKey(key);
    return sfex::Keyboard::m_keyStatesForDown[key];
#endif
}

bool Keyboard::getKeyUp(sfex::Keyboard::Key key)
{
#ifdef SFEX_USE_UPDATE_BASED_INPUT_HANDLING
    if(Keyboard::m_keyStates[key] && !Keyboard::getKey(key))
    {
        return true;
    }
    return false;
#else
    if(Keyboard::m_keyStatesForUp[key])
    {
        Keyboard::m_keyStatesForUp[key] = Keyboard::getKey(key);
        return !Keyboard::m_keyStatesForUp[key];
    }
    Keyboard::m_keyStatesForUp[key] = Keyboard::getKey(key);
    return false;
#endif
}

void Keyboard::update()
{
#ifdef SFEX_USE_UPDATE_BASED_INPUT_HANDLING
    for(auto&[key, state] : m_keyStates)
    {
        m_keyStates[key] = Keyboard::getKey(key);
    }
#endif
}

} // namespace sfex
