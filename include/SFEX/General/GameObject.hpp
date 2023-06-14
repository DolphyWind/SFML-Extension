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

#ifndef _SFEX_GENERAL_GAMEOBJECT_HPP_
#define _SFEX_GENERAL_GAMEOBJECT_HPP_

#include <SFEX/General/GameBehaviour.hpp>
#include <SFEX/General/GameComponent.hpp>
#include <vector>

namespace sfex
{

class ExtendedScene;
class GameObject : public GameBehaviour
{
public:
    /// @brief Default constructor
    /// @param parent The scene containing this Game Object
    GameObject(ExtendedScene* parent);

    /// @brief Default destructor
    virtual ~GameObject();

    /// @brief Get the scene that this game object sits in
    /// @return The scene that this game object sits in
    ExtendedScene* getScene();

    /// @brief Add new GameComponent to 
    /// @tparam T Type of the GameComponent
    /// @param args Parameters to pass to the constructor of T. this GameObject will be passed automatically to first parameter.
    template<typename T, typename... Args>
    void addComponent(Args&&... args);

    /// Add hasComponent, getComponent, getComponents, removeComponents

    /// @brief Event hadling function for a scene
    /// @param e Event to handle
    virtual void onEvent(const sf::Event& e) override;

    /// @brief Start function runs once when the scene has been loaded.
    virtual void start() override;

    /// @brief Update function runs on each frame.
    virtual void update() override;

    /// @brief Late Update function runs each frame after update. A little bit after the update function.
    virtual void lateUpdate() override;

    /// @brief Draw function draws the scene drawables to a target
    /// @param target Target to draw onto
    virtual void render(sf::RenderTarget &target) override;

    /// @brief Destroy functiun runs when a scene manager switchs to a new scene.
    virtual void onDestroy() override;

private:
    ExtendedScene* m_parent;
    std::vector<GameComponent_Ptr> m_components;
};


template<typename T, typename... Args>
void GameObject::addComponent(Args&&... args)
{
    // m_components.push_back(std::make_unique<T>(this, args...));
}

}

#endif // !_SFEX_GENERAL_GAMEOBJECT_HPP_