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

#include <SFEX/Managers/SceneManager.hpp>

namespace sfex
{

void SceneManager::setActiveScene(const std::string &key)
{
    if(!this->contains(key)) return;
    if(this->m_activeKey.has_value()) this->at(m_activeKey.value())->destroy();
    m_activeKey = key;
    this->at(key)->start();
}

std::optional<std::shared_ptr<Scene>> SceneManager::getActiveScene()
{
    if(!m_activeKey.has_value()) return std::nullopt;
    if(!this->contains(m_activeKey.value())) return std::nullopt;
    return this->at(m_activeKey.value());
}

std::optional<std::string> SceneManager::getActiveSceneKey()
{
    return m_activeKey;
}


void SceneManager::handleEvent(const sf::Event &e)
{
    if(!m_activeKey.has_value()) return;
    this->at(m_activeKey.value())->handleEvent(e);
}

void SceneManager::update(const sf::Time& deltaTime)
{
    if(!m_activeKey.has_value()) return;
    this->at(m_activeKey.value())->update(deltaTime);
}

void SceneManager::draw(sf::RenderTarget &target)
{
    if(!m_activeKey.has_value()) return;
    this->at(m_activeKey.value())->draw(target);
}

} // namespace sfex
