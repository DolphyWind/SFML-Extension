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

#ifndef _SFEX_GENERAL_MOUSE_HPP_
#define _SFEX_GENERAL_MOUSE_HPP_

#include <SFML/Window/Mouse.hpp>
#include <SFEX/Numeric/Vector2.hpp>
#include <SFEX/General/StaticClass.hpp>
#include <unordered_map>

namespace sfex
{

/// @brief Simple mouse class for detecting and proccessing the mouse input. Only contains static methods.
class Mouse : StaticClass
{
public:
    typedef sf::Mouse::Wheel Wheel;
    typedef sf::Mouse::Button Button;

    /// @brief Returns true if the given mouse button is held down
    /// @param button Mouse button to check
    /// @return True if mouse button is being held down, false otherwise
    static bool getButton(sfex::Mouse::Button button);
    
    /// @brief Returns true if the given mouse button started being held down in the current frame
    /// @param button Mouse button to check
    /// @see update
    /// @return True if mouse button is started being held down in the current frame, false otherwise
    static bool getButtonDown(sfex::Mouse::Button button);
    
    /// @brief Returns true if the given mouse button is released in the current frame
    /// @param button Mouse button to check
    /// @see update
    /// @return True if mouse button is released in the current frame, false otherwise
    static bool getButtonUp(sfex::Mouse::Button button);

    /// @brief Update the internal button states of the mouse. Does nothing if SFEX_USE_UPDATE_BASED_INPUT_HANDLING is not defined.
    /// When compiling SFEX. If the said option is not defined, getButtonDown and getButtonUp instantly update the internal state for the given key.
    /// This means, if getButtonDown or getButtonUp is called twice consecutively, the second call will return false if the first one returns true.
    /// If you are 100% sure that you won't use same function call twice, you may not define the said option. Otherwise define it and call
    /// sfex::Mouse::update() on each update
    static void update();
    
    
    /// @brief Get the current mouse position in window or desktop coordinates
    /// @param relativeTo Reference window
    /// @return Current mouse position in window coordinates
    static sfex::Vec2i getPosition(const sf::Window *relativeTo=nullptr);
    
    /// @brief Set the current position of the mouse in window or desktop coordinates.
    /// @param position New position of the mouse
    /// @param relativeTo Reference window
    static void setPosition(const sfex::Vec2i &position, const sf::Window *relativeTo=nullptr);
private:
#ifdef SFEX_USE_UPDATE_BASED_INPUT_HANDLING
    static std::unordered_map<sfex::Mouse::Button, bool> m_buttonStates;
    static std::unordered_map<sfex::Mouse::Button, bool> m_buttonStatesNew;
#else
    static std::unordered_map<sfex::Mouse::Button, bool> m_buttonStatesForDown;
    static std::unordered_map<sfex::Mouse::Button, bool> m_buttonStatesForUp;
#endif
};

} // namespace sfex


#endif // !_SFEX_GENERAL_MOUSE_HPP_