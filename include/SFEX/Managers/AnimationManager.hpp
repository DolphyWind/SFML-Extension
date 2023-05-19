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

#ifndef _SFEX_MANAGERS_ANIMATION_MANAGER_HPP_
#define _SFEX_MANAGERS_ANIMATION_MANAGER_HPP_

#include <SFEX/Managers/ManagerBase.hpp>
#include <SFEX/Graphics/Animation.hpp>
#include <optional>

namespace sfex
{

/// @brief Manages animations for one sprite.
class AnimationManager : public ManagerBase<std::shared_ptr<Animation>>
{
public:
    /// @brief Construct a new Animation Manager object
    /// @param targetSprite Target sprite of the animation manager. Defaults to nullptr.
    AnimationManager(sf::Sprite* targetSprite=nullptr);


    /// @brief Set the target sprite of the animation manager
    /// @param targetSprite New target sprite of the animation manager
    void setTargetSprite(sf::Sprite* targetSprite);

    /// @brief Get the target sprite of the animation manager
    const sf::Sprite* getTargetSprite() const;

    /// @brief Play the animation corresponding to given key. Does nothing if key is invalid.
    /// @param key Key corresponding to animation you want to play.
    /// @param restartAnimation Restart animation when played.
    void play(const std::string& key, bool restartAnimation=false);

    /// @brief Pauses the current animation.
    void pause();

    /// @brief Restarts the current animation.
    void restart();

    /// @brief Updates the states of the animations
    void update();

    
    /// @brief Get a shared pointer to the current animation. 
    /// @return A shared pointer to the current animation.
    std::optional<std::shared_ptr<Animation>> getCurrentAnimation();
    
    /// @brief Get the key of the current scene.
    /// @return The key of the current scene
    std::optional<std::string> getCurrentAnimationKey();
    

private:
    sf::Sprite* m_targetSprite;
    std::optional<std::string> m_activeKey;
};

}

#endif //!_SFEX_MANAGERS_ANIMATION_MANAGER_HPP_
