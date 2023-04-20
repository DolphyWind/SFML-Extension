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

#ifndef _SFEX_GRAPHICS_ANIMATION_HPP_
#define _SFEX_GRAPHICS_ANIMATION_HPP_

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFEX/General/Stopwatch.hpp>
#include <memory>
#include <vector>
#include <limits>

namespace sfex
{

/// @brief Stores Frames in a std::vector<> provides methods to manage them.
class Animation
{
public:
    struct Frame
    {
        sf::IntRect rect;
        sf::Time duration;
    };

    /// @brief Construct a new Animation object
    Animation();

    /// @brief Construct a new Animation object with a sprite.
    /// @param targetSprite Reference to a sprite that you want to apply animations to.
    /// @param texture Texture of the 
    Animation(sf::Sprite& targetSprite, sf::Texture& texture, bool loop=true);


    /// @brief Set the looping status
    /// @param loop New looping status
    void setLoop(bool loop);

    /// @brief Get the looping status
    /// @return Looping status
    bool getLoop();

    /// @brief Change the speed of the animation.
    /// @param animSpeed New animation speed
    void setAnimationSpeed(float animSpeed);

    /// @brief Get the animation speed
    /// @return Animation speed
    float getAnimationSpeed();

    /// @brief Set the Texture of this animation
    /// @param texture New texture of this animation.
    void setTexture(sf::Texture& texture);

    /// @brief Get the Texture of this animation
    /// @return Texture of this animation
    const sf::Texture& getTexture() const;

    /// @brief Set the sprite that you want to apply animations to.
    /// @param sprite Reference to a sprite that you want to apply animations to.
    void setSprite(sf::Sprite& sprite);

    /// @brief Get the Sprite of this animation
    /// @return Sprite of this animations
    const sf::Sprite& getSprite() const;

    /// @brief Automatically generates multiple frames from sprite by give sf::IntRect
    /// @param topleftRect Top left frame of sprite
    /// @param duration Duration of the each frame
    void autoGenerateFrames(const sf::IntRect& topleftRect, const sf::Time& duration);
    
    /// @brief Adds a frame to the end of the frame vector or the specified index. 
    /// @param rect IntRect of the frame
    /// @param duration Duration of the frame
    /// @param index The index you want to insert. Inserts to the end of the vector if index is greater than frame count.
    void insertFrame(const sf::IntRect& rect, const sf::Time& duration, std::size_t index=std::numeric_limits<std::size_t>::max());
    
    /// @brief Adds a frame to the end of the frame vector or the specified index.
    /// @param frame Frame you want to insert
    /// @param index The index you want to insert. Inserts to the end of the vector if index is greater than frame count.
    void insertFrame(const Frame& frame, std::size_t index=std::numeric_limits<std::size_t>::max());

    /// @brief Removes the frame at the given index
    void removeFrame(std::size_t index);

    /// @brief Clears all frames.
    void clearFrames();

    /// @brief Set the current frame
    /// @param index Index of the new current frame
    void setFrameIndex(std::size_t index);

    /// @brief Get the current frame index
    /// @return Current frame index
    std::size_t getFrameIndex() const;


    /// @brief Update the animation. Switch to the next frame if needed.
    void update();
    
    /// @brief Pause the animation.
    void pause();
    
    /// @brief Resume/Play the animation.
    /// @param restartAnimation Restart animation when played.
    void play(bool restartAnimation=true);

    /// @brief Restart the animation
    void restart();

    /// @brief Returns true if the stopwatch has been paused. Returns false otherwise.
    bool isPaused();

private:
    std::size_t m_currentIndex;
    bool m_loop = true;
    float m_animationSpeed = 1;
    sfex::Stopwatch m_stopwatch;
    sf::Sprite* m_spritePtr;
    sf::Texture* m_texturePtr;
    std::vector<Frame> m_frames;
};

}

#endif // !_SFEX_GRAPHICS_ANIMATION_HPP_