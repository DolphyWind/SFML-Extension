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

#include <SFEX/General/Joystick.hpp>

namespace sfex
{

std::unordered_map<std::pair<unsigned int, unsigned int>, bool, PairHash> Joystick::m_buttonsForDown;
std::unordered_map<std::pair<unsigned int, unsigned int>, bool, PairHash> Joystick::m_buttonsForUp;

bool Joystick::isConnected(unsigned int id)
{
    return sf::Joystick::isConnected(id);
}

unsigned int Joystick::getButtonCount(unsigned int id)
{
    return sf::Joystick::getButtonCount(id);
}

bool Joystick::hasAxis(unsigned int id, Axis axis)
{
    return sf::Joystick::hasAxis(id, axis);
}

bool Joystick::getButton(unsigned int id, unsigned int button)
{
    return sf::Joystick::isButtonPressed(id, button);
}

bool Joystick::getButtonDown(unsigned int id, unsigned int button)
{
    if(Joystick::m_buttonsForDown[{id, button}])
    {
        Joystick::m_buttonsForDown[{id, button}] = Joystick::getButton(id, button);
        return false;
    }
    Joystick::m_buttonsForDown[{id, button}] = Joystick::getButton(id, button);
    return Joystick::m_buttonsForDown[{id, button}];
}

bool Joystick::getButtonUp(unsigned int id, unsigned int button)
{
    if(Joystick::m_buttonsForUp[{id, button}])
    {
        Joystick::m_buttonsForUp[{id, button}] = Joystick::getButton(id, button);
        return !Joystick::m_buttonsForUp[{id, button}];
    }
    Joystick::m_buttonsForUp[{id, button}] = Joystick::getButton(id, button);
    return false;
}

float Joystick::getAxisPosition(unsigned int id, Axis axis, float minSensitivity)
{
    if(!Joystick::hasAxis(id, axis)) return 0.0f;
    float axisPos = sf::Joystick::getAxisPosition(id, axis) / 100.0f;
    if(axisPos*axisPos < minSensitivity*minSensitivity) return 0.0f;
    return axisPos;
}

Joystick::Identification Joystick::getIdentification(unsigned int id)
{
    return sf::Joystick::getIdentification(id);
}

void Joystick::update()
{
    sf::Joystick::update();
}

} // namespace sfex
