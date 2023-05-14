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

#ifndef _SFEX_GENERAL_JOYSTICK_HPP_
#define _SFEX_GENERAL_JOYSTICK_HPP_

#include <SFML/Window/Joystick.hpp>
#include <SFEX/General/StaticClass.hpp>
#include <unordered_map>

namespace sfex
{

/// @brief Simple joystick class for detecting and proccessing the joystick input. Only contains static methods.
class Joystick : StaticClass
{
public:
    typedef sf::Joystick::Axis Axis;
    typedef sf::Joystick::Identification Identification;

    /// @brief Check if a joystick is connected
    /// @return True if a joystick is connected, false otherwise
    static bool isConnected(unsigned int id);

    /// @brief Return the number of buttons on a joystick
    /// @return The number of buttons on a joystick
    static unsigned int getButtonCount(unsigned int id);

    /// @brief Check if a joystick supports given axis
    /// @param joystick Index of the joystick  
    /// @param axis Axis to check
    /// @return True if a joystick supports given axis, false otherwise
    static bool hasAxis(unsigned int joystick, Axis axis);

    /// @brief Returns true if the given joystick button is held down
    /// @param joystick Index of the joystick 
    /// @param button Joystick button to check
    /// @return True if key is being held down, false otherwise
    static bool getButton(unsigned int joystick, unsigned int button);

    /// @brief Returns true if the given joystick button is pressed in the current frame
    /// @param joystick Index of the joystick 
    /// @param button Joystick button to check 
    /// @return True if joystick button is started being held down in the current frame, false otherwise
    static bool getButtonDown(unsigned int joystick, unsigned int button);

    /// @brief Returns true if the given joystick button is released in the current frame
    /// @param joystick Index of the joystick 
    /// @param button Joystick button to check
    /// @return True if joystick button is released in the current frame, false otherwise
    static bool getButtonUp(unsigned int joystick, unsigned int button);

    /// @brief Get the current position between -1 and 1 of the specified axis
    /// @param joystick Index of the joystick 
    /// @param axis Axis to check
    /// @param minSensitivity Minimum sensitivity
    /// @return Current position of axis. Returns 0 If the absolute position of the axis is smaller than minimum sensitivity
    static float getAxisPosition(unsigned int joystick, Axis axis, float minSensitivity=0.0f);

    /// @brief Get the joystick information
    /// @param joystick Index of the joystick 
    /// @return Structure containing joystick information
    static Identification getIdentification(unsigned int joystick);

    /// @brief Update the states of all joysticks
    static void update();
private:

    /// @brief Hash function to for std::pair<unsigned int, unsigned int>
    struct JoystickPairHash 
    {
        template <typename T1, typename T2>
        std::size_t operator () (const std::pair<T1, T2> &p) const
        {
            // To make each hash unique
            return p.first * sf::Joystick::ButtonCount + p.second;
        }
    };

    static std::unordered_map<std::pair<unsigned int, unsigned int>, bool, JoystickPairHash> m_buttonsForDown;
    static std::unordered_map<std::pair<unsigned int, unsigned int>, bool, JoystickPairHash> m_buttonsForUp;
};

} // namespace sfex


#endif // !_SFEX_GENERAL_JOYSTICK_HPP_