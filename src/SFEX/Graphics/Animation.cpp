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

#include <SFEX/Graphics/Animation.hpp>
#include <iostream>

namespace sfex
{

Animation::Animation():
    m_currentIndex(0), m_loop(true), m_animationSpeed(1.0f), m_timer(sf::Time::Zero), m_spritePtr(nullptr), m_texturePtr(nullptr), m_frames(), m_finished(false)
{
}

Animation::Animation(sf::Sprite &targetSprite, sf::Texture &texture, bool loop):
    m_currentIndex(0), m_animationSpeed(1.0f), m_loop(loop), m_timer(sf::Time::Zero), m_spritePtr(&targetSprite), m_texturePtr(&texture), m_frames(), m_finished(false)
{
    pause();
    restart();
}

void Animation::setLoop(bool loop)
{
    m_loop = loop;
}

bool Animation::getLoop()
{
    return m_loop;
}

void Animation::setAnimationSpeed(float animSpeed)
{
    m_animationSpeed = animSpeed;
}

float Animation::getAnimationSpeed()
{
    return m_animationSpeed;
}

void Animation::setTexture(sf::Texture &texture)
{
    m_texturePtr = &texture;
}

const sf::Texture& Animation::getTexture() const
{
    return *m_texturePtr;
}

void Animation::setSprite(sf::Sprite &sprite)
{
    m_spritePtr = &sprite;
}

const sf::Sprite& Animation::getSprite() const
{
    return *m_spritePtr;
}

void Animation::autoGenerateFrames(const sf::IntRect &topleftRect, const sf::Time &duration, bool clear_frames)
{
    if(!m_texturePtr) return;
    if (clear_frames) clearFrames();

    int left = topleftRect.left;
    int top = topleftRect.top;
    int rect_width = topleftRect.width;
    int rect_height = topleftRect.height;

    std::size_t width = m_texturePtr->getSize().x - left;
    std::size_t height = m_texturePtr->getSize().y - top;

    std::size_t frame_count_x = (width / rect_width);
    std::size_t frame_count_y = (height / rect_height);
    m_frames.reserve(frame_count_x * frame_count_y);

    for(std::size_t y = 0; y < frame_count_y; y++)
    {
        for(std::size_t x = 0; x < frame_count_x; x++)
        {
            insertFrame({sf::IntRect(left + x*rect_width, top + y*rect_height, rect_width, rect_height), duration});
        }
    }
    if(clear_frames) setFrameInternal(0);
}

void Animation::autoGenerateFrames(const sfex::Vec2u &size, const std::vector<sfex::Vec2u> &positions, const sf::Time &duration, bool clear_frames)
{
    if(clear_frames) clearFrames();

    for(auto& p : positions)
    {
        Frame frame;
        frame.duration = duration;
        frame.rect = sf::IntRect( p.x, p.y, size.x, size.y);
        insertFrame(frame);
    }
    if(clear_frames) setFrameInternal(0);
}

void Animation::autoGenerateFrames(const std::vector<Frame> &frames, bool clear_frames)
{
    if(clear_frames) clearFrames();

    for(auto& frame : frames) insertFrame(frame);
    if(clear_frames) setFrameInternal(0);
}

void Animation::insertFrame(const sf::IntRect &rect, const sf::Time &duration, std::size_t index)
{
    insertFrame({rect, duration}, index);
}

void Animation::insertFrame(const Frame& frame, std::size_t index)
{
    if(index >= m_frames.size())
    {
        if(m_frames.empty())
        {
            setFrameInternal(0);
        }
        m_frames.push_back(frame);
    }
    else
    {
        m_frames[index] = frame;
    }
}

void Animation::removeFrame(std::size_t index)
{
    if(index >= m_frames.size()) return;
    m_frames.erase(m_frames.begin() + index);
}

void Animation::clearFrames()
{
    m_currentIndex = 0;
    m_frames.clear();
}

void Animation::setFrame(std::size_t index)
{
    if(!m_spritePtr || !m_texturePtr) return;
    if(m_frames.empty()) return;
    m_spritePtr->setTexture(*m_texturePtr);

    if(index >= m_frames.size())
    {
        index = m_frames.size() - 1;
    }
    m_currentIndex = index;
    m_timer = sf::Time::Zero;

    m_spritePtr->setTextureRect(m_frames[m_currentIndex].rect);
}

void Animation::setFrameInternal(std::size_t index)
{
    if(!m_spritePtr || !m_texturePtr) return;
    if(m_frames.empty()) return;
    m_spritePtr->setTexture(*m_texturePtr);
    
    m_currentIndex = index;
    m_timer = sf::Time::Zero;

    if(m_loop)
    {
        // Allow negative indexing
        if(m_currentIndex > (std::numeric_limits<std::size_t>::max() - m_frames.size()) )
        {
            setFrameInternal(m_currentIndex + m_frames.size());
            return;
        }
        else if(m_currentIndex >= m_frames.size())
        {
            setFrameInternal(0);
            return;
        }
    }
    else
    {
        if(m_currentIndex > (std::numeric_limits<std::size_t>::max() - m_frames.size()) )
        {
            setFrameInternal(0);
            pause();
            m_finished = true;
            return;
        }
        else if(m_currentIndex >= m_frames.size())
        {
            setFrameInternal(m_frames.size() - 1);
            pause();
            m_finished = true;
            return;
        }
    }
    
    m_spritePtr->setTextureRect(m_frames[m_currentIndex].rect);
}

const std::size_t Animation::getCurrentFrameIndex() const
{
    return m_currentIndex;
}

const Animation::Frame Animation::getCurrentFrame() const
{
    return m_frames[m_currentIndex];
}

const std::vector<Animation::Frame> Animation::getFrames() const
{
    return m_frames;
}

void Animation::update(const sf::Time& deltaTime)
{
    if(m_frames.empty() || m_paused || m_finished) return;
    m_timer += deltaTime * sfex::Math::abs(m_animationSpeed);

    if(!m_loop)
    {
        if(m_animationSpeed <= 0 && m_currentIndex == std::numeric_limits<std::size_t>::max())
        {
            setFrameInternal(0);
            return;
        }
        else if(m_animationSpeed >= 0 && m_currentIndex >= m_frames.size())
        {
            setFrameInternal(m_frames.size() - 1);
            return;
        }
    }

    if(m_timer >= m_frames[m_currentIndex].duration)
    {
        if(m_animationSpeed >= 0)
        {
            setFrameInternal(m_currentIndex + 1);
        }
        else
        {
            setFrameInternal(m_currentIndex - 1);
        }
    }
}

void Animation::pause()
{
    m_paused = true;
}

void Animation::resume()
{
    if(!isPaused()) return;
    m_paused = false;
}

void Animation::play()
{
    if(!m_texturePtr || !m_spritePtr) return;
    restart();
    resume();
}

void Animation::restart()
{
    if(m_animationSpeed >= 0)
    {
        setFrameInternal(0);
    }
    else
    {
        setFrameInternal(m_frames.size() - 1);
    }
    m_timer = sf::Time::Zero;
    m_finished = false;
}

bool Animation::isPaused()
{
    return m_paused;
}

bool Animation::isFinished()
{
    return m_finished;
}

}
