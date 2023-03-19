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
#include <unordered_map>

namespace sfex
{

/// @brief Simple keyboard class for detecting and proccessing the keyboard input. Only contains static methods.
class Keyboard
{
public:
    typedef sf::Keyboard::Key Key;

    /// @brief Returns true if the given key is held down
    /// @param key Key to check
    /// @return True if key is being held down, false otherwise
    static bool getKey(sfex::Keyboard::Key key);
    
    /// @brief Returns true if the given key started being held down in the current frame
    /// @param key Key to check
    /// @return True if key is started being held down in the current frame, false otherwise
    static bool getKeyDown(sfex::Keyboard::Key key);
    
    /// @brief Returns true if the given key is released in the current frame
    /// @param key Key to check
    /// @return True if key is released in the current frame, false otherwise
    static bool getKeyUp(sfex::Keyboard::Key key);

protected:
    /// To prevent instantiating from this class
    Keyboard() {};

private:
    static std::unordered_map<sfex::Keyboard::Key, bool> m_keysForDown;
    static std::unordered_map<sfex::Keyboard::Key, bool> m_keysForUp;

};

} // namespace sfex


#endif // !_SFEX_GENERAL_KEYBOARD_HPP_