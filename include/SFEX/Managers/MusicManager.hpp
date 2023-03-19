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

#ifndef _SFEX_MANAGERS_MUSICMANAGER_HPP_
#define _SFEX_MANAGERS_MUSICMANAGER_HPP_

#include <unordered_map>
#include <SFML/Audio/Music.hpp>
#include <SFEX/General/FilteringMethods.hpp>
#include <string>

namespace sfex
{

/// @brief Simple music manager class that stores musics in a hashmap and can play them
class MusicManager
{
public:

    /// @brief A function to check if the key is present in the hashmap
    /// @param key Key to check
    /// @return true if the key is present in the hashmap
    bool contains(const std::string& key) const;

    /// @brief Get number of musics stored
    /// @return Number of musics stored
    std::size_t size() const;

    /// @brief Open a music from an audio file
    /// @param key Unique identifier of music
    /// @param filename Path of the file to load
    /// @return True if loading was successfull
    bool openFromFile(const std::string &key, const std::string &filename);

    /// @brief Open a music from memory
    /// @param key Unique identifier of muic
    /// @param data Pointer to data on the memory
    /// @param size Size of the data on the memory
    /// @return True if loading was successfull
    bool openFromMemory(const std::string &key, const void *data, std::size_t size);

    /// @brief Open a music from stream
    /// @param key Unique identifier of music
    /// @param stream Source stream to read from
    /// @return True if loading was successfull
    bool openFromStream(const std::string &key, sf::InputStream &stream);

    /// @brief Play music corresponding to key
    /// @param key Unique identifier of music
    void play(const std::string &key);

    /// @brief Pause music corresponding to key
    /// @param key Unique identifier of music
    void pause(const std::string &key);

    /// @brief Stop music corresponding to key
    /// @param key Unique identifier of music
    void stop(const std::string &key);

    /// @brief Get the total duration of music corresponding to key
    /// @param key Unique identifier of the music
    /// @return Duration of the music
    sf::Time getDuration(const std::string &key);

    /// @brief Get the playing status of the music corresponding to key
    /// @param key Unique identifier of the music
    /// @return Duration of the music
    sf::Music::Status getStatus(const std::string &key);

    /// @brief Get music corresponding to key
    /// @param key Unique identifier of music
    /// @return A pointer to the music corresponding to key. Returns nullptr if key doesn't correspond to anything.
    sf::Music* get(const std::string &key);

    /// @brief Get all keys
    /// @return All keys in a vector
    std::vector<std::string> getKeys() const;

    /// @brief Get music corresponding to key
    /// @param key Unique identifier of music
    /// @return A pointer to the music corresponding to key. Returns nullptr if key doesn't correspond to anything.
    sf::Music* operator[](const std::string &key);

    /// @brief Filter each key by pattern and method then return matching musics
    /// @param pattern Pattern to look for while filtering
    /// @param method Filtering method to use while filtering
    /// @return musics that are filtered
    std::vector<sf::Music*> filter(std::string pattern, sfex::FilterType method);


private:
    /// @brief Hashmap to store all musics
    std::unordered_map<std::string, sf::Music> m_musics;
};

} // namespace sfex


#endif // !_SFEX_MANAGERS_MUSICMANAGER_HPP_