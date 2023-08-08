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

#include <SFEX/General/Mouse.hpp>

namespace sfex
{

#ifdef SFEX_USE_UPDATE_BASED_INPUT_HANDLING
std::unordered_map<sfex::Mouse::Button, bool> Mouse::deltaButtonStatesForButtonDown;
std::unordered_map<sfex::Mouse::Button, bool> Mouse::deltaButtonStatesForButtonUp;
#endif
std::unordered_map<sfex::Mouse::Button, bool> Mouse::buttonStatesForButtonDown;
std::unordered_map<sfex::Mouse::Button, bool> Mouse::buttonStatesForButtonUp;


bool Mouse::getButton(sfex::Mouse::Button button)
{
    return sf::Mouse::isButtonPressed(button);
}

bool Mouse::getButtonDown(sfex::Mouse::Button button)
{
    if(buttonStatesForButtonDown[button])
    {
        buttonStatesForButtonDown[button] = Mouse::getButton(button);
        return false;
    }
#ifdef SFEX_USE_UPDATE_BASED_INPUT_HANDLING
    deltaButtonStatesForButtonDown[button] = Mouse::getButton(button);
    if(!buttonStatesForButtonDown[button] && deltaButtonStatesForButtonDown[button])
    {
        return true;
    }
    return false;
#else
    buttonStatesForButtonDown[button] = Mouse::getButton(button);
    return buttonStatesForButtonDown[button];
#endif
}

bool Mouse::getButtonUp(sfex::Mouse::Button button)
{
    if(buttonStatesForButtonUp[button])
    {
        buttonStatesForButtonUp[button] = Mouse::getButton(button);
        return !buttonStatesForButtonUp[button];
    }
#ifdef SFEX_USE_UPDATE_BASED_INPUT_HANDLING
    deltaButtonStatesForButtonUp[button] = Mouse::getButton(button);
    if(buttonStatesForButtonUp[button] && !deltaButtonStatesForButtonUp[button])
    {
        return true;
    }
#else
    buttonStatesForButtonUp[button] = Mouse::getButton(button);
#endif
    return false;
}

void Mouse::update()
{
#ifdef SFEX_USE_UPDATE_BASED_INPUT_HANDLING
    for(auto&[key, state] : deltaButtonStatesForButtonDown)
    {
        buttonStatesForButtonDown[key] = state;
    }
    for(auto&[key, state] : deltaButtonStatesForButtonUp)
    {
        buttonStatesForButtonUp[key] = state;
    }
    deltaButtonStatesForButtonDown.clear();
    deltaButtonStatesForButtonUp.clear();
#endif
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
