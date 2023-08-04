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

#ifndef _SFEX_GENERAL_KEYBOARD_HPP_
#define _SFEX_GENERAL_KEYBOARD_HPP_

#include <SFML/Window/Keyboard.hpp>
#include <SFEX/General/StaticClass.hpp>
#include <unordered_map>
#include <unordered_set>

namespace sfex
{

/// @brief Simple keyboard class for detecting and proccessing the keyboard input. Only contains static methods.
class Keyboard : StaticClass
{
public:
    typedef sf::Keyboard::Key Key;

    /// @brief Returns true if the given key is held down
    /// @param key Key to check
    /// @return True if key is being held down, false otherwise
    static bool getKey(sfex::Keyboard::Key key);
    
    /// @brief Returns true if the given key started being held down in the current frame
    /// @param key Key to check
    /// @see update
    /// @return True if key is started being held down in the current frame, false otherwise
    static bool getKeyDown(sfex::Keyboard::Key key);
    
    /// @brief Returns true if the given key is released in the current frame
    /// @param key Key to check
    /// @see update
    /// @return True if key is released in the current frame, false otherwise
    static bool getKeyUp(sfex::Keyboard::Key key);

    /// @brief Update the internal key states of the keyboard. Does nothing if SFEX_USE_UPDATE_BASED_INPUT_HANDLING is not defined.not defined
    /// When compiling SFEX. If the said option is not defined, getKeyDown and getKeyUp instantly update the internal state for the given key.
    /// This means, if getKeyDown or getKeyUp is called twice consecutively, the second call will return false, if the first one returns true.
    /// If you are 100% sure that you won't use same function call twice, you may not define the said option. Otherwise define it and call
    /// sfex::Keyboard::update() on each loop.
    static void update();

private:
#ifdef SFEX_USE_UPDATE_BASED_INPUT_HANDLING
    static std::unordered_map<sfex::Keyboard::Key, bool> m_keyStates;
    static std::unordered_set<sfex::Keyboard::Key> m_newKeyStatesForDown;
    static std::unordered_set<sfex::Keyboard::Key> m_newKeyStatesForUp;
#else
    static std::unordered_map<sfex::Keyboard::Key, bool> m_keyStatesForDown;
    static std::unordered_map<sfex::Keyboard::Key, bool> m_keyStatesForUp;
#endif
};

} // namespace sfex


#endif // !_SFEX_GENERAL_KEYBOARD_HPP_