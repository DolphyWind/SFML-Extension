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

#ifndef _TEXTURE_MANAGER_HPP_
#define _TEXTURE_MANAGER_HPP_

#include <unordered_map>
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFEX/Graphics/Color.hpp>

namespace sfex
{

/// @brief Simple texture manager. Loads textures from various resources and stores both texture and sprite into seperate hashmaps.
class TextureManager
{
public:

/// @brief Creates an empty texture
/// @param key Unique identifier of texture
/// @param width Width of the texture
/// @param height Height of the texture
/// @return True if loading was successfull
bool create(const std::string &key, unsigned int width, unsigned int height);

/// @brief Load texture from file
/// @param key Unique identifier of texture
/// @param filename Path of the texture file to load
/// @param area Area of the texture to load
/// @return True if loading was successfull
bool loadFromFile(const std::string &key, const std::string &filename, const sf::IntRect &area=sf::IntRect());

/// @brief Load texture from memory
/// @param key Unique identifier of texture 
/// @param data Pointer to texture data on the memory
/// @param size Size of the texture data on the memory
/// @param area Area of the texture to load
/// @return True if loading was successfull
bool loadFromMemory(const std::string &key, const void *data, std::size_t size, const sf::IntRect &area=sf::IntRect());

/// @brief Load texture from stream
/// @param key Unique identifier of texture
/// @param inputStream Source stream to read from
/// @param area Area of the texture to load
/// @return True if loading was successfull
bool loadFromStream(const std::string &key, sf::InputStream& inputStream, const sf::IntRect &area=sf::IntRect());

/// @brief Load texture from sf::Image
/// @param key Unique identifier of texture
/// @param image Image to load into the texture
/// @param area Area of the texture to load
/// @return True if loading was successfull
bool loadFromImage(const std::string &key, const sf::Image &image, const sf::IntRect &area=sf::IntRect());

/// @brief Get texture corresponding to key
/// @param key Unique identifier of texture
/// @return A reference to the sprite corresponding to key
sf::Texture &getTexture(const std::string &key);

/// @brief Get sprite corresponding to key
/// @param key Unique identifier of sprite
/// @return A reference to the sprite corresponding to key
sf::Sprite &getSprite(const std::string &key);

/// @brief Update sprite corresponding to key. Use this if you did something to sprite's texture.
/// @param key Unique identifier of sprite
void updateSprite(const std::string &key);

private:

/// @brief HashMap to store all textures
std::unordered_map<std::string, sf::Texture> m_textures;

/// @brief HashMap to store all sprites
std::unordered_map<std::string, sf::Sprite> m_sprites;

/// @brief A function to check if the key is present in the texture hashmap
bool textureHasKey(const std::string &key);

/// @brief A function to check if the key is present in the sprite hashmap
bool spriteHasKey(const std::string &key);

};

} // namespace sfex


#endif // !_TEXTURE_MANAGER_HPP_