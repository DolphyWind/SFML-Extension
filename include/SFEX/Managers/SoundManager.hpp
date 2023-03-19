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

#ifndef _SFEX_MANAGERS_SOUNDMANAGER_HPP_
#define _SFEX_MANAGERS_SOUNDMANAGER_HPP_

#include <unordered_map>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFEX/Numeric/Vector3.hpp>
#include <SFEX/General/FilteringMethods.hpp>

namespace sfex
{

/// @brief Simple sound manager class that stores sounds and their buffers into seperate hashmaps and can play them
class SoundManager
{
public:

    /// @brief A function to check if the key is present in the hashmap
    /// @param key Key to check
    /// @return true if the key is present in the hashmap
    bool contains(const std::string& key) const;

    /// @brief Get number of sounds stored
    /// @return Number of sounds stored
    std::size_t size() const;

    /// @brief Loads sf::SoundBuffer from file then creates a sf::Sound from it
    /// @param key Unique identifier of sound
    /// @param filename Path of the file to load
    /// @return True if loading was successfull
    bool loadFromFile(const std::string &key, const std::string &filename);

    /// @brief Load sf::SoundBuffer from memory then creates sf::Sound from it
    /// @param key Unique identifier of sound
    /// @param data Pointer to data on the memory
    /// @param size Size of the data on the memory
    /// @return True if loading was successfull
    bool loadFromMemory(const std::string &key, const void *data, std::size_t size);

    /// @brief Loads sf::SoundBuffer from stream then creates a sf::Sound from it
    /// @param key Unique identifier of sound
    /// @param stream Source stream to read from
    /// @return True if loading was successfull
    bool loadFromStream(const std::string &key, sf::InputStream &stream);

    /// @brief Load the sound buffer from an array of audio samples then create an sf::Sound to 
    /// @param key Unique identifier of sound
    /// @param sample Pointer to the array of samples in memory
    /// @param sampleCount Number of samples in the array
    /// @param channelCount Number of channels (1 = mono, 2 = stereo, ...)
    /// @param sampleRate Sample rate (number of samples to play per second)
    /// @return True if loading was successfull
    bool loadFromSamples(const std::string &key, const sf::Int16 *sample, sf::Uint64 sampleCount, unsigned int channelCount, unsigned int sampleRate);

    /// @brief Play sound corresponding to key
    /// @param key Unique identifier of sound
    void play(const std::string &key);

    /// @brief Pause sound corresponding to key
    /// @param key Unique identifier of sound
    void pause(const std::string &key);

    /// @brief Stop sound corresponding to key
    /// @param key Unique identifier of sound
    void stop(const std::string &key);

    /// @brief Get the total duration of sound corresponding to key
    /// @param key Unique identifier of the sound
    /// @return Duration of the sound
    sf::Time getDuration(const std::string &key);

    /// @brief Get the playing status of the sound corresponding to key
    /// @param key Unique identifier of the sound
    /// @return Duration of the sound
    sf::Sound::Status getStatus(const std::string &key);

    /// @brief Get sound corresponding to key
    /// @param key Unique identifier of sound
    /// @return A pointer to the sound corresponding to key. Returns nullptr if key doesn't correspond to anything.
    sf::Sound* get(const std::string &key);

    /// @brief Get all keys
    /// @return All keys in a vector
    std::vector<std::string> getKeys() const;

    /// @brief Get sound corresponding to key
    /// @param key Unique identifier of sound
    /// @return A pointer to the sound corresponding to key. Returns nullptr if key doesn't correspond to anything.
    sf::Sound* operator[](const std::string &key);

    /// @brief Filter each key by pattern and method then return matching sounds
    /// @param pattern Pattern to look for while filtering
    /// @param method Filtering method to use while filtering
    /// @return Sounds that are filtered
    std::vector<sf::Sound*> filter(std::string pattern, sfex::FilterType method);


private:
    /// @brief Hashmap to store all sounds
    std::unordered_map<std::string, sf::Sound> m_sounds;

    /// @brief Hashmap to store all soundbuffers
    std::unordered_map<std::string, sf::SoundBuffer> m_buffers; 
};

} // namespace sfex


#endif // !_SFEX_MANAGERS_SOUNDMANAGER_HPP_