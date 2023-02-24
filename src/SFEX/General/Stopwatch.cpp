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

#include <SFEX/General/Stopwatch.hpp>

namespace sfex
{

Stopwatch::Stopwatch()
{

}

sf::Time Stopwatch::getElapsedTime()
{
    if(m_paused) return m_time;
    return m_time + m_clock.getElapsedTime();
}

sf::Time Stopwatch::pause()
{
    if(m_paused) return m_time;

    m_paused = true;
    m_time = m_clock.getElapsedTime();
    return m_time;
}

void Stopwatch::resume()
{
    if(!m_paused) return;
    
    m_paused = false;
    m_clock.restart();
}

sf::Time Stopwatch::restart()
{
    sf::Time returnTime = m_time;
    m_time = sf::Time();
    m_clock.restart();

    return returnTime;
}

}