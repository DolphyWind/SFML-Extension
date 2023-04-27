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

#ifndef _SFEX_GRAPHICS_SPRITEMANAGER_HPP_
#define _SFEX_GRAPHICS_SPRITEMANAGER_HPP_

#include <unordered_map>
#include <string>
#include <vector>
#include <SFEX/Managers/ManagerBase.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace sfex
{

/// @brief Simple SpriteManager class. Inherits from sfex::ManagerBase<sf::Sprite>
class SpriteManager : public ManagerBase<sf::Sprite>
{
public:

    /// @brief Creates an empty new sprite at the specified key. Overrides existing sprite if key already has one.
    /// @param key Key value
    void createEmpty(const std::string &key);

    /// @brief Creates a new sprite with its texture or modifies an existing one. 
    /// @param key Key value
    /// @param texture Texture of the sprite corresponding to key
    void setTexture(const std::string &key, const sf::Texture &texture);

private:

};

} // namespace sfex

#endif // !_SFEX_GRAPHICS_SPRITEMANAGER_HPP_