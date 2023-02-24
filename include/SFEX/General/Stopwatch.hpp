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

#ifndef _SFEX_GENERAL_STOPWATCH_HPP_
#define _SFEX_GENERAL_STOPWATCH_HPP_

// Headers
#include <SFEX/Config.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

namespace sfex
{

class Stopwatch
{
public:
    Stopwatch();
    sf::Time getElapsedTime();
    sf::Time pause();
    void resume();
    sf::Time restart();

private:
    // Member data
    sf::Clock m_clock;
    sf::Time m_time;
    bool m_paused = false;
};

}

#endif // _SFEX_GENERAL_STOPWATCH_HPP_