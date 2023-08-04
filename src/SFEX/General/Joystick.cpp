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


#ifdef SFEX_USE_UPDATE_BASED_INPUT_HANDLING
std::unordered_map<Joystick::JoystickButtonPair, bool, Joystick::JoystickPairHash> Joystick::m_buttonStates;
std::unordered_map<Joystick::JoystickButtonPair, bool, Joystick::JoystickPairHash> Joystick::m_buttonStatesNew;
#else
std::unordered_map<Joystick::JoystickButtonPair, bool, Joystick::JoystickPairHash> Joystick::m_buttonStatesForDown;
std::unordered_map<Joystick::JoystickButtonPair, bool, Joystick::JoystickPairHash> Joystick::m_buttonStatesForUp;
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
#ifdef SFEX_USE_UPDATE_BASED_INPUT_HANDLING
    if(!m_buttonStates[{joystick, button}] && Joystick::getButton(joystick, button))
    {
        m_buttonStatesNew[{joystick, button}] = true;
        return true;
    }
    return false;
#else
    if(Joystick::m_buttonStatesForDown[{joystick, button}])
    {
        Joystick::m_buttonStatesForDown[{joystick, button}] = Joystick::getButton(joystick, button);
        return false;
    }
    Joystick::m_buttonStatesForDown[{joystick, button}] = Joystick::getButton(joystick, button);
    return Joystick::m_buttonStatesForDown[{joystick, button}];
#endif
}

bool Joystick::getButtonUp(unsigned int joystick, unsigned int button)
{
#ifdef SFEX_USE_UPDATE_BASED_INPUT_HANDLING
    if(m_buttonStates[{joystick, button}] && !Joystick::getButton(joystick, button))
    {
        m_buttonStatesNew[{joystick, button}] = false;
        return true;
    }
    return false;
#else
    if(Joystick::m_buttonStatesForUp[{joystick, button}])
    {
        Joystick::m_buttonStatesForUp[{joystick, button}] = Joystick::getButton(joystick, button);
        return !Joystick::m_buttonStatesForUp[{joystick, button}];
    }
    Joystick::m_buttonStatesForUp[{joystick, button}] = Joystick::getButton(joystick, button);
    return false;
#endif
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
    for(auto&[idButtonPair, state] : m_buttonStatesNew)
    {
        m_buttonStates[idButtonPair] = state;
    }
#endif
}

} // namespace sfex
