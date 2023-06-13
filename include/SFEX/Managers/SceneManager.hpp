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

#ifndef _SFEX_MANAGERS_SCENEMANAGER_HPP_
#define _SFEX_MANAGERS_SCENEMANAGER_HPP_

#include <SFEX/Managers/ManagerBase.hpp>
#include <SFEX/General/Scene.hpp>
#include <SFEX/General/GameBehaviour.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <memory>
#include <string>
#include <optional>

namespace sfex
{

/// @brief Simple scene manager class. Stores shared pointers to Scene objects. Inherits from ManagerBase<std::shared_ptr<Scene>>.
class SceneManager : public ManagerBase<std::shared_ptr<Scene>>, public GameBehaviour
{
public:
    /// @brief Default constructor
    SceneManager();

    /// @brief Set active scene of the scene manager. It does nothing if key is not valid.
    /// @param key Unique identifier of key
    void setActiveScene(const std::string &key);
    
    /// @brief Get a shared pointer to the active scene. 
    /// @return A shared pointer to the active scene
    std::optional<std::shared_ptr<Scene>> getActiveScene();
    
    /// @brief Get the key of the active scene.
    /// @return The key of the active scene
    std::optional<std::string> getActiveSceneKey();


    /// @brief Call pollEvent function of the active scene. 
    /// @param e Event variable
    virtual void onEvent(const sf::Event &e) override;

    virtual void start() override;
    
    /// @brief Call update() function of the active scene. 
    virtual void update() override;

    virtual void lateUpdate() override;
    
    /// @brief Call draw() function of the active scene. 
    virtual void render(sf::RenderTarget &target) override;

    virtual void onDestroy() const;
private:
    std::optional<std::string> m_activeKey;
};

} // namespace sfex


#endif // !_SFEX_MANAGERS_SCENEMANAGER_HPP_