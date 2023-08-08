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
std::unordered_map<sfex::Keyboard::Key, bool> Keyboard::deltaStatesForDownPress;
std::unordered_map<sfex::Keyboard::Key, bool> Keyboard::deltaStatesForUpPress;
#endif
std::unordered_map<sfex::Keyboard::Key, bool> Keyboard::keyStatesForKeyDown;
std::unordered_map<sfex::Keyboard::Key, bool> Keyboard::keyStatesForKeyUp;

bool Keyboard::getKey(sfex::Keyboard::Key key)
{
    return sf::Keyboard::isKeyPressed(key);
}

bool Keyboard::getKeyDown(sfex::Keyboard::Key key)
{
    if(keyStatesForKeyDown[key])
    {
        keyStatesForKeyDown[key] = Keyboard::getKey(key);
        return false;
    }
#ifdef SFEX_USE_UPDATE_BASED_INPUT_HANDLING
    deltaStatesForDownPress[key] = Keyboard::getKey(key);
    if(!keyStatesForKeyDown[key] && deltaStatesForDownPress[key])
    {
        return true;
    }
    return false;
#else
    keyStatesForKeyDown[key] = Keyboard::getKey(key);
    return keyStatesForKeyDown[key];
#endif
}

bool Keyboard::getKeyUp(sfex::Keyboard::Key key)
{
    if(keyStatesForKeyUp[key])
    {
        keyStatesForKeyUp[key] = Keyboard::getKey(key);
        return !keyStatesForKeyUp[key];
    }
#ifdef SFEX_USE_UPDATE_BASED_INPUT_HANDLING
    deltaStatesForUpPress[key] = Keyboard::getKey(key);
    if(keyStatesForKeyUp[key] && !deltaStatesForUpPress[key])
    {
        return true;
    }
#else
    keyStatesForKeyUp[key] = Keyboard::getKey(key);
#endif
    return false;
}

void Keyboard::update()
{
#ifdef SFEX_USE_UPDATE_BASED_INPUT_HANDLING
    for(auto&[key, state] : deltaStatesForDownPress)
    {
        keyStatesForKeyDown[key] = state;
    }
    for(auto&[key, state] : deltaStatesForUpPress)
    {
        keyStatesForKeyUp[key] = state;
    }
    deltaStatesForDownPress.clear();
    deltaStatesForUpPress.clear();
#endif
}

} // namespace sfex
