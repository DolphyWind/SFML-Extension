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

#ifndef _SFEX_GRAPHICS_TEXTURE_MANAGER_HPP_
#define _SFEX_GRAPHICS_TEXTURE_MANAGER_HPP_

#include <unordered_map>
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <SFEX/General/FilteringMethods.hpp>

namespace sfex
{

/// @brief Simple texture manager. Loads textures from various resources and stores textures into hashmaps.
class TextureManager
{
public:

    /// @brief A function to check if the key is present in the hashmap
    /// @param key Key to check
    /// @return true if the key is present in the hashmap
    bool contains(const std::string &key) const;

    /// @brief Get number of textures stored
    /// @return Number of textures stored
    std::size_t size() const;

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
    bool loadFromStream(const std::string &key, sf::InputStream &inputStream, const sf::IntRect &area=sf::IntRect());

    /// @brief Load texture from sf::Image
    /// @param key Unique identifier of texture
    /// @param image Image to load into the texture
    /// @param area Area of the texture to load
    /// @return True if loading was successfull
    bool loadFromImage(const std::string &key, const sf::Image &image, const sf::IntRect &area=sf::IntRect());

    /// @brief Get texture corresponding to key
    /// @param key Unique identifier of texture
    /// @return A pointer to the texture corresponding to key. Returns nullptr if key doesn't correspond to anything.
    sf::Texture* get(const std::string &key);

    /// @brief Get all keys
    /// @return All keys in a vector
    std::vector<std::string> getKeys() const;

    /// @brief Get texture corresponding to key
    /// @param key Unique identifier of texture
    /// @return A pointer to the texture corresponding to key. Returns nullptr if key doesn't correspond to anything.
    sf::Texture* operator[](const std::string &key);

    /// @brief Filter each key by pattern and method then return matching textures
    /// @param pattern Pattern to look for while filtering
    /// @param method Filtering method to use while filtering
    /// @return Textures that are filtered
    std::vector<sf::Texture*> filter(std::string pattern, sfex::FilterType method);

private:
    /// @brief HashMap to store all textures
    std::unordered_map<std::string, sf::Texture> m_textures;

};

} // namespace sfex


#endif // !_SFEX_GRAPHICS_TEXTURE_MANAGER_HPP_