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

#include <SFEX/General/GameObject.hpp>
// #include <SFEX/General/ExtendedScene.hpp>

namespace sfex
{

GameObject::GameObject(ExtendedScene* parent, const std::string& name):
    GameBehaviour(name), m_parent(parent)
{
}

GameObject::~GameObject()
{
}

ExtendedScene* GameObject::getScene()
{
    return m_parent;
}


void GameObject::onEvent(const sf::Event &e)
{
    for(auto& component : m_components)
    {
        component->onEvent(e);
    }
}

void GameObject::start()
{
    for(auto& component : m_components)
    {
        component->start();
    }
}

void GameObject::update()
{
    for(auto& component : m_components)
    {
        component->update();
    }
}

void GameObject::lateUpdate()
{
    for(auto& component : m_components)
    {
        component->lateUpdate();
    }
}

void GameObject::render(sf::RenderTarget& target)
{
    for(auto& component : m_components)
    {
        component->render(target);
    }
}

void GameObject::onDestroy()
{
    for(auto& component : m_components)
    {
        component->onDestroy();
    }
}

GameComponent* GameObject::getComponent(const std::string& name) const
{
    for(auto& component : m_components)
    {
        if(component->getName() == name) return component.get();
    }
    return nullptr;
}

std::vector<GameComponent*> GameObject::getComponents(const std::string& name) const
{
    std::vector<GameComponent*> output;
    for(auto& component : m_components)
    {
        if(component->getName() == name) output.push_back(component.get());
    }
    return output;
}

void GameObject::removeComponent(GameComponent *ptr)
{
    m_components.erase(std::remove_if(m_components.begin(), m_components.end(), [ptr](const GameComponent_Ptr& p){
        return p.get() == ptr;
    }), m_components.end());
}

}