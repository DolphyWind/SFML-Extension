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

#ifndef _SFEX_GENERAL_GAMEBEHAVIOUR_HPP_
#define _SFEX_GENERAL_GAMEBEHAVIOUR_HPP_
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <memory>

namespace sfex
{

class GameBehaviour
{
public:
    /// @brief Default constructor
    GameBehaviour(const std::string& name);

    /// @brief Default destructor
    virtual ~GameBehaviour();
    

    /// @brief On Event should be run when there is a new sf::Event
    /// @param e sf::Event to handle
    virtual void onEvent(const sf::Event& e);

    /// @brief Start function should run once when the behaviour has been loaded.
    virtual void start();

    /// @brief Update function should run each frame.
    virtual void update();

    /// @brief Late Update function should be run each frame after update, after the update function and before the render function.
    virtual void lateUpdate();

    /// @brief Render function should run each frame after update and late update functions.
    /// @param target Render target to render on.
    virtual void render(sf::RenderTarget& target);

    /// @brief On Destroy should be called when the Behaviour has been destroyed.
    virtual void onDestroy();


    /// @brief Get the name of the game behaviour
    virtual std::string getName() const final;

    /// @brief Set the name of the game behaviour
    /// @param name New name of the game behaviour
    virtual void setName(const std::string& name) final;

private:
    std::string m_name;
};

template<typename T>
struct BehaviourDeleter
{
    void operator()(T* ptr) const;
};

typedef std::unique_ptr<GameBehaviour, BehaviourDeleter<GameBehaviour>> GameBehaviour_Ptr;

}

#include "GameBehaviour.inl"

#endif // !_SFEX_GENERAL_GAMEBEHAVIOUR_HPP_