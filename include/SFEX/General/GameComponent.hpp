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

#ifndef _SFEX_GENERAL_GAMECOMPONENT_HPP_
#define _SFEX_GENERAL_GAMECOMPONENT_HPP_

#include <SFEX/General/GameBehaviour.hpp>
#include <memory>

namespace sfex
{

class GameObject;
class GameComponent : public GameBehaviour
{
public:
    /// @brief Default constructor. Stores a pointer for the parent game object.
    /// @param parent Parent Game Object.
    GameComponent(GameObject* parent, const std::string& name);

    /// @brief Default destructor
    virtual ~GameComponent();

    /// @brief Get the parent game object
    /// @return The parent game object
    GameObject* getGameObject();

    /// @brief On Event function when there is a new sf::Event
    /// @param e sf::Event to handle
    virtual void onEvent(const sf::Event& e) override;

    /// @brief Start function runs once when the component has been loaded.
    virtual void start() override;

    /// @brief Update function runs on each frame.
    virtual void update() override;

    /// @brief Late Update function runs each frame after update. A little bit after the update function.
    virtual void lateUpdate() override;

    /// @brief Render function runs each frame after update and late update functions.
    /// @param target Render target to render on.
    virtual void render(sf::RenderTarget& target) override;

    /// @brief On Destroy should be called when the Behaviour has been destroyed.
    virtual void onDestroy() override;

    /// @brief Return whether the game component is a singleton or not. A gameobject can't contain more than one singleton components.
    /// @return True if the game component is a singleton. False otherwise.
    virtual bool isSingleton() const;
private:
    GameObject* m_parent;
};

typedef std::unique_ptr<GameComponent, BehaviourDeleter<GameComponent>> GameComponent_Ptr;

}

#endif