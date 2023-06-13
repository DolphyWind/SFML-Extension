#include "GameObject.hpp"

namespace sfex
{

template<typename T, typename... Args>
void GameObject::addComponent(Args&&... args)
{
    GameComponent_Ptr newComponent = std::make_unique<T>(this, std::forward(args)...);
    if(newComponent->isSingleton() && hasComponent<T>()) return;

    newComponent->start();
    m_components.push_back(GameComponent_Ptr(newComponent.release()));
}

template<typename T>
bool GameObject::hasComponent() const
{
    for(auto& component : m_components)
    {
        if(dynamic_cast<T>(component.get())) return true;
    }
    return false;
}

template<typename T>
T* GameObject::getComponent() const
{
    for(auto& component : m_components)
    {
        if(dynamic_cast<T>(component.get())) return component.get();
    }
    return nullptr;
}

template<typename T>
std::vector<T*> GameObject::getComponents() const
{
    std::vector<T*> output;
    for(auto& component : m_components)
    {
        if(dynamic_cast<T>(component.get())) output.push_back(component.get());
    }
    return output;
}


}