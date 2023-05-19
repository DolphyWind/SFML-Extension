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

#ifndef _SFEX_GENERAL_LISTENER_HPP_
#define _SFEX_GENERAL_LISTENER_HPP_

#include <SFML/Audio/Listener.hpp>
#include <SFEX/Numeric/Vector3.hpp>

namespace sfex
{

/// @brief Listener class that can be instantiated unlike sf::Listener.
class Listener
{
public:

    /// @brief Default constructor
    Listener();

    /// @brief Construct a new Listener object
    /// @param globalVolume Global volume of the listener
    /// @param position Position of the listener
    /// @param direction Direction of the listener
    /// @param upVector Up Vector of the listener
    Listener(float globalVolume, const sfex::Vec3 &position, const sfex::Vec3 &direction, const sfex::Vec3 &upVector);

    /// @brief Equals operator of Listener class
    /// @param other Other Listener object
    /// @return This listener after equals operation
    Listener operator=(const Listener &other);

    /// @brief Equality check operator of Listener class
    /// @param other Other Listener object
    /// @return Result of the equality check operation
    bool operator==(const Listener &other) const;

    /// @brief Inequality check operator of Listener class
    /// @param other Other Listener object
    /// @return Result of the inequality check operation
    bool operator!=(const Listener &other) const;

    /// @brief Set global volume of the listener
    /// @param volume New global volume of the listener
    void setGlobalVolume(float volume);
    
    /// @brief Get global volume of the listener
    /// @return Global volume of the listener
    float getGlobalVolume() const;

    /// @brief Set 3D position of the listener
    /// @param position New position of the listener
    void setPosition(const sfex::Vec3 &position);

    /// @brief Set 3D position of the listener
    /// @param x New x coordinate of the listener
    /// @param y New y coordinate of the listener
    /// @param z New z coordinate of the listener
    void setPosition(float x, float y, float z);

    /// @brief Get 3D position of the listener
    /// @return 3D position of the listener
    sfex::Vec3 getPosition() const;

    /// @brief Set direction of the listener
    /// @param direction New direction of the listener
    void setDirection(const sfex::Vec3 &direction);

    /// @brief Set direction of the listener
    /// @param x New x coordinate of the direction of the listener
    /// @param y New y coordinate of the direction of the listener
    /// @param z New z coordinate of the direction of the listener
    void setDirection(float x, float y, float z);

    /// @brief Get direction of the listener
    /// @return Direction of the listener
    sfex::Vec3 getDirection() const;

    /// @brief Set up vector of the listener
    /// @param upVector New up vector of the listener
    void setUpVector(const sfex::Vec3 &upVector);

    /// @brief Set up vector of the listener
    /// @param x New x coordinate of the up vector of the listener
    /// @param y New y coordinate of the up vector of the listener
    /// @param z New z coordinate of the up vector of the listener
    void setUpVector(float x, float y, float z);

    /// @brief Get up vector of the listener
    /// @return Up vector of the listener
    sfex::Vec3 getUpVector() const;

    /// @brief Activates the listener. 
    void activate() const;

    /// @brief Get the Default Listener
    /// @return Default Listener
    static const Listener getDefaultListener();

private:
    float m_globalVolume;
    sfex::Vec3 m_position;
    sfex::Vec3 m_direction;
    sfex::Vec3 m_upVector;
    static Listener defaultListener;
};


} // namespace sfex


#endif // !_SFEX_GENERAL_LISTENER_HPP_