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
#include <unordered_set>

namespace sfex
{

/// @brief Simple joystick class for detecting and proccessing the joystick input. Only contains static methods.
class Joystick : StaticClass
{
public:
    typedef sf::Joystick::Axis Axis;
    typedef sf::Joystick::Identification Identification;

    enum 
    {
        Count = sf::Joystick::Count,
        AxisCount = sf::Joystick::AxisCount,
        ButtonCount = sf::Joystick::ButtonCount,
    };

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
    /// @return Current position of axis. Returns 0 If the absolute position of the axis is smaller than minimum sensitivity to ignore small inputs on sensitive sticks.
    static float getAxisPosition(unsigned int joystick, Axis axis, float minSensitivity=0.0f);

    /// @brief Get the joystick information
    /// @param joystick Index of the joystick 
    /// @return Structure containing joystick information
    static Identification getIdentification(unsigned int joystick);

    /// @brief Update the states of all joysticks.
    /// @brief Update the internal button states of all jostrics. Only calls sf::Joystick::update() if SFEX_USE_UPDATE_BASED_INPUT_HANDLING is not defined.
    /// When compiling SFEX. If the said option is not defined, getButtonDown and getButtonUp instantly update the internal state for the given key.
    /// This means, if getButtonDown or getButtonUp is called twice consecutively, the second call will return false if the first one returns true.
    /// If you are 100% sure that you won't use same function call twice, you may not define the said option. If it is not defined,
    /// sfex::Joystick::update() only calls sf::Joystick::update()
    static void update();
private:

    struct JoystickButtonPair
    {
        unsigned int joystickId;
        unsigned int button;

        bool operator==(const JoystickButtonPair& other) const;
    };

    /// @brief Hash function to for Joystick::JoystickButtonPair
    struct JoystickPairHash 
    {
        std::size_t operator ()(const JoystickButtonPair& p) const;
    };

    static std::unordered_map<JoystickButtonPair, bool, JoystickPairHash> buttonStatesForButtonDown;
    static std::unordered_map<JoystickButtonPair, bool, JoystickPairHash> buttonStatesForButtonUp;
#ifdef SFEX_USE_UPDATE_BASED_INPUT_HANDLING
    static std::unordered_map<JoystickButtonPair, bool, JoystickPairHash> deltaButtonStatesForButtonDown;
    static std::unordered_map<JoystickButtonPair, bool, JoystickPairHash> deltaButtonStatesForButtonUp;
#else
#endif
};

} // namespace sfex

#endif // !_SFEX_GENERAL_JOYSTICK_HPP_