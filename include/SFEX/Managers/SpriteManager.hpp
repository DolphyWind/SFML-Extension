// MIT License

// Copyright (c) 2023 Yunus Emre Aydın

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef _SFEX_GRAPHICS_SPRITEMANAGER_HPP_
#define _SFEX_GRAPHICS_SPRITEMANAGER_HPP_

#include <unordered_map>
#include <string>
#include <vector>
#include <SFEX/Managers/Filtering.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace sfex
{

class SpriteManager
{
public:

/// @brief A function to check if the key is present in the hashmap
/// @param key Key to check
/// @return true if the key is present in the hashmap
bool hasSprite(const std::string &key) const;

/// @brief Get number of sprites stored
/// @return Number of sprites stored
std::size_t size() const;

/// @brief Creates a new sprite with its texture or modifies an existing one 
/// @param key Unique identifier of sprite
/// @param texture Texture of the sprite corresponding to key
void setTexture(const std::string &key, const sf::Texture &texture);

/// @brief Get sprite corresponding to key
/// @param key Unique identifier of sprite
/// @return A pointer to the sprite corresponding to key. Returns nullptr if key doesn't correspond to anything.
sf::Sprite* get(const std::string &key);

/// @brief Get all keys
/// @return All keys in a vector
std::vector<std::string> getKeys() const;

/// @brief Get sprite corresponding to key
/// @param key Unique identifier of sprite
/// @return A pointer to the sprite corresponding to key. Returns nullptr if key doesn't correspond to anything.
sf::Sprite* operator[](const std::string &key);

/// @brief Filter each key by pattern and method then return matching sprites
/// @param pattern Pattern to look for while filtering
/// @param method Filtering method to use while filtering
/// @return Sprites that are filtered
std::vector<sf::Sprite*> filter(std::string pattern, sfex::FilterType method);


private:
std::unordered_map<std::string, sf::Sprite> m_sprites;

};

} // namespace sfex

#endif // !_SFEX_GRAPHICS_SPRITEMANAGER_HPP_