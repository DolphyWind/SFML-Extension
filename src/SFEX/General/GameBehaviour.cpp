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

#include <SFEX/General/GameBehaviour.hpp>

namespace sfex
{

GameBehaviour::GameBehaviour(const std::string& name):
    m_name(name)
{
}

GameBehaviour::~GameBehaviour()
{
}


void GameBehaviour::onEvent(const sf::Event &e)
{
}

void GameBehaviour::start()
{
}

void GameBehaviour::update()
{
}

void GameBehaviour::lateUpdate()
{
}

void GameBehaviour::render(sf::RenderTarget &target)
{
}

void onDestroy()
{
}

std::string GameBehaviour::getName() const
{
    return m_name;
}

void GameBehaviour::setName(const std::string &name)
{
    m_name = name;
}

}