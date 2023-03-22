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
#include <string>
#include <SFML/Audio/Music.hpp>
#include <SFEX/Managers/MangerBase.hpp>

namespace sfex
{

/// @brief Simple music manager class that stores musics in a hashmap and can play them. Inherits from ManagerBase<sf::Music>
class MusicManager : public ManagerBase<sf::Music>
{
public:

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

private:
    
};

} // namespace sfex


#endif // !_SFEX_MANAGERS_MUSICMANAGER_HPP_