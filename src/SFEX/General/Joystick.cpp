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

#include <SFEX/General/Joystick.hpp>

namespace sfex
{


std::unordered_map<Joystick::JoystickButtonPair, bool, Joystick::JoystickPairHash> Joystick::buttonStatesForButtonDown;
std::unordered_map<Joystick::JoystickButtonPair, bool, Joystick::JoystickPairHash> Joystick::buttonStatesForButtonUp;
#ifdef SFEX_USE_UPDATE_BASED_INPUT_HANDLING
std::unordered_map<Joystick::JoystickButtonPair, bool, Joystick::JoystickPairHash> Joystick::deltaButtonStatesForButtonDown;
std::unordered_map<Joystick::JoystickButtonPair, bool, Joystick::JoystickPairHash> Joystick::deltaButtonStatesForButtonUp;
#endif

std::size_t Joystick::JoystickPairHash::operator()(const JoystickButtonPair& p) const
{
    return std::hash<std::size_t>()(p.joystickId * sf::Joystick::ButtonCount + p.button);
}

bool Joystick::JoystickButtonPair::operator==(const JoystickButtonPair& other) const
{
    return (this->joystickId == other.joystickId) && (this->button == other.button);
}

bool Joystick::isConnected(unsigned int joystick)
{
    return sf::Joystick::isConnected(joystick);
}

unsigned int Joystick::getButtonCount(unsigned int joystick)
{
    return sf::Joystick::getButtonCount(joystick);
}

bool Joystick::hasAxis(unsigned int joystick, Axis axis)
{
    return sf::Joystick::hasAxis(joystick, axis);
}

bool Joystick::getButton(unsigned int joystick, unsigned int button)
{
    return sf::Joystick::isButtonPressed(joystick, button);
}

bool Joystick::getButtonDown(unsigned int joystick, unsigned int button)
{
    if(buttonStatesForButtonDown[{joystick, button}])
    {
        buttonStatesForButtonDown[{joystick, button}] = Joystick::getButton(joystick, button);
        return false;
    }
#ifdef SFEX_USE_UPDATE_BASED_INPUT_HANDLING
    deltaButtonStatesForButtonDown[{joystick, button}] = Joystick::getButton(joystick, button);
    if(!buttonStatesForButtonDown[{joystick, button}] && deltaButtonStatesForButtonDown[{joystick, button}])
    {
        return true;
    }
    return false;
#else
    buttonStatesForButtonDown[{joystick, button}] = Joystick::getButton(joystick, button);
    return buttonStatesForButtonDown[{joystick, button}];
#endif
}

bool Joystick::getButtonUp(unsigned int joystick, unsigned int button)
{
    if(buttonStatesForButtonUp[{joystick, button}])
    {
        buttonStatesForButtonUp[{joystick, button}] = Joystick::getButton(joystick, button);
        return !buttonStatesForButtonUp[{joystick, button}];
    }
#ifdef SFEX_USE_UPDATE_BASED_INPUT_HANDLING
    deltaButtonStatesForButtonUp[{joystick, button}] = Joystick::getButton(joystick, button);
    if(buttonStatesForButtonUp[{joystick, button}] && !deltaButtonStatesForButtonUp[{joystick, button}])
    {
        return true;
    }
#else
    buttonStatesForButtonUp[{joystick, button}] = Joystick::getButton(joystick, button);
#endif
    return false;
}

float Joystick::getAxisPosition(unsigned int joystick, Axis axis, float minSensitivity)
{
    if(!Joystick::hasAxis(joystick, axis)) return 0.0f;
    float axisPos = sf::Joystick::getAxisPosition(joystick, axis) / 100.0f;
    if(axisPos*axisPos < minSensitivity*minSensitivity) return 0.0f;
    return axisPos;
}

Joystick::Identification Joystick::getIdentification(unsigned int joystick)
{
    return sf::Joystick::getIdentification(joystick);
}

void Joystick::update()
{
    sf::Joystick::update();
#ifdef SFEX_USE_UPDATE_BASED_INPUT_HANDLING
    for(auto& [idButtonPair, state] : deltaButtonStatesForButtonDown)
    {
        buttonStatesForButtonDown[idButtonPair] = state;
    }
    for(auto& [idButtonPair, state] : deltaButtonStatesForButtonUp)
    {
        buttonStatesForButtonUp[idButtonPair] = state;
    }

    deltaButtonStatesForButtonDown.clear();
    deltaButtonStatesForButtonUp.clear();
#endif
}

} // namespace sfex
