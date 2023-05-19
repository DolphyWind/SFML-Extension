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

#include <SFEX/Managers/AnimationManager.hpp>

namespace sfex
{

AnimationManager::AnimationManager(sf::Sprite* targetSprite): m_targetSprite(targetSprite), m_activeKey(std::nullopt)
{
}

void AnimationManager::setTargetSprite(sf::Sprite *targetSprite)
{
    m_targetSprite = targetSprite;
}

const sf::Sprite* AnimationManager::getTargetSprite() const
{
    return m_targetSprite;
}

void AnimationManager::play(const std::string &key, bool restartAnimation)
{
    if(!this->contains(key)) return;
    if(m_activeKey.has_value() && m_activeKey.value() == key && !restartAnimation) return;
    if(m_activeKey.has_value()) this->at(m_activeKey.value())->pause();
    m_activeKey = key;
    this->at(m_activeKey.value())->play(restartAnimation);
}

void AnimationManager::pause()
{
    if(!m_activeKey.has_value()) return;
    this->at(m_activeKey.value())->pause();
}

void AnimationManager::restart()
{
    if(!m_activeKey.has_value()) return;
    this->at(m_activeKey.value())->restart();
}

std::optional<std::shared_ptr<Animation>> AnimationManager::getCurrentAnimation()
{
    if(!m_activeKey.has_value()) return std::nullopt;
    return this->at(m_activeKey.value());
}

std::optional<std::string> AnimationManager::getCurrentAnimationKey()
{
    return m_activeKey;
}

void AnimationManager::update()
{
    for(auto& p : this->m_hashmap)
        p.second->update();
}

}