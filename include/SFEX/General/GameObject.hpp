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
#include <type_traits>
#include <optional>

namespace sfex
{

class ExtendedScene;
class GameObject : public GameBehaviour
{
public:
    /// @brief Default constructor
    /// @param parent The scene containing this Game Object
    GameObject(ExtendedScene* parent, const std::string& name);

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

    /// @brief Check if the game object has a component with the given type
    /// @tparam T Type of the component
    /// @return True, if the game object has the component with type T. False otherwise.
    template<typename T>
    bool hasComponent();

    /// @brief Get the first component with specific type.
    /// @tparam T The type of the game component to find.
    /// @return A pointer to the first component with specific type.
    template<typename T>
    T* getComponent() const;

    /// @brief Get the first component with specific name.
    /// @param name Name of the component.
    /// @return A pointer to the first component with the given name.
    GameComponent* getComponent(const std::string& name) const;

    /// @brief Get all components with specific type.
    /// @tparam T The type of the game components to find.
    /// @return A vector of pointers to all components with specific type.
    template<typename T>
    std::vector<T*> getComponents() const;

    /// @brief Get all components with specific name.
    /// @param name Name of the components.
    /// @return A vector of pointers to all components with the given name.
    std::vector<GameComponent*> getComponents(const std::string& name) const;

    /// @brief Remove a game component by value
    /// @param ptr A pointer to the game component to delete
    void removeComponent(GameComponent* ptr);

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

typedef std::unique_ptr<GameObject, BehaviourDeleter<GameObject>> GameObject_Ptr;

}

#include "GameObject.inl"

#endif // !_SFEX_GENERAL_GAMEOBJECT_HPP_