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

#include <SFEX/General/Listener.hpp>

namespace sfex
{

Listener::Listener()
{
    m_globalVolume = 100;
    m_position = sfex::Vec3::zero;
    m_direction = sfex::Vec3::back;
    m_upVector = sfex::Vec3::up;
}

void Listener::setGlobalVolume(float volume)
{
    m_globalVolume = volume;
}

float Listener::getGlobalVolume() const
{
    return m_globalVolume;
}

void Listener::setPosition(const sfex::Vec3 &position)
{
    m_position = position;
}

void Listener::setPosition(float x, float y, float z)
{
    setPosition({x, y, z});
}

sfex::Vec3 Listener::getPosition() const
{
    return m_position;
}

void Listener::setDirection(const sfex::Vec3 &direction)
{
    m_direction = direction;
}

void Listener::setDirection(float x, float y, float z)
{
    setDirection({x, y, z});
}

sfex::Vec3 Listener::getDirection() const
{
    return m_direction;
}

void Listener::setUpVector(const sfex::Vec3 &upvector)
{
    m_upVector = upvector;
}

void Listener::setUpVector(float x, float y, float z)
{
    setUpVector({x, y, z});
}

sfex::Vec3 Listener::getUpVector() const
{
    return m_upVector;
}

void Listener::activate() const
{
    sf::Listener::setGlobalVolume(m_globalVolume);
    sf::Listener::setPosition(m_position);
    sf::Listener::setDirection(m_direction);
    sf::Listener::setUpVector(m_upVector);
}

} // namespace sfex
