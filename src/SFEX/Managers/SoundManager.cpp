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

#include <SFEX/Managers/SoundManager.hpp>

namespace sfex
{

bool SoundManager::contains(const std::string &key) const
{
    return (m_sounds.find(key) != m_sounds.end());
}

std::size_t SoundManager::size() const
{
    return m_sounds.size();
}

bool SoundManager::loadFromFile(const std::string &key, const std::string &filename)
{
    m_buffers[key] = sf::SoundBuffer();
    if(!m_buffers[key].loadFromFile(filename)) return false;

    m_sounds[key] = sf::Sound(m_buffers[key]);
    return true;
}

bool SoundManager::loadFromMemory(const std::string &key, const void *data, std::size_t size)
{
    m_buffers[key] = sf::SoundBuffer();
    if(!m_buffers[key].loadFromMemory(data, size)) return false;

    m_sounds[key] = sf::Sound(m_buffers[key]);
    return true;
}

bool SoundManager::loadFromStream(const std::string &key, sf::InputStream &stream)
{
    m_buffers[key] = sf::SoundBuffer();
    if(!m_buffers[key].loadFromStream(stream)) return false;

    m_sounds[key] = sf::Sound(m_buffers[key]);
    return true;
}

bool SoundManager::loadFromSamples(const std::string &key, const sf::Int16 *sample, sf::Uint64 sampleCount, unsigned int channelCount, unsigned int sampleRate)
{
    m_buffers[key] = sf::SoundBuffer();
    if(!m_buffers[key].loadFromSamples(sample, sampleCount, channelCount, sampleRate)) return false;

    m_sounds[key] = sf::Sound(m_buffers[key]);
    return true;
}

void SoundManager::play(const std::string &key)
{
    if(!this->get(key)) return;

    this->get(key)->play();
}

void SoundManager::pause(const std::string &key)
{
    if(!this->get(key)) return;

    this->get(key)->pause();
}

void SoundManager::stop(const std::string &key)
{
    if(!this->get(key)) return;

    this->get(key)->stop();
}

sf::Time SoundManager::getDuration(const std::string &key)
{
    if(!this->get(key)) return sf::Time::Zero;

    return this->get(key)->getBuffer()->getDuration();
}

sf::Sound::Status SoundManager::getStatus(const std::string &key)
{
    if(!this->get(key)) return sf::Sound::Status::Stopped;

    return this->get(key)->getStatus();
}

sf::Sound* SoundManager::get(const std::string &key)
{
    if(!contains(key)) return nullptr;

    return &m_sounds[key];
}

std::vector<std::string> SoundManager:: getKeys() const
{
    std::vector<std::string> result;
    for(auto &p : m_sounds)
    {
        result.push_back(p.first);
    }
    return result;
}

sf::Sound* SoundManager::operator[](const std::string &key)
{
    return this->get(key);
}

std::vector<sf::Sound*> SoundManager::filter(std::string pattern, sfex::FilterType method)
{
    std::vector<sf::Sound*> result;
    for(auto &p : m_sounds)
    {
        bool filtered = false;
        switch (method)
        {
            case FilterType::Starts_with:
            {
                filtered = p.first.find(pattern) == 0;
                break;
            }
            case FilterType::Ends_with:
            {
                filtered = p.first.substr(p.first.length() - pattern.length(), pattern.length()) == pattern;
                break;
            }
            case FilterType::Contains:
            {
                filtered = p.first.find(pattern) != std::string::npos;
                break;
            }
            case FilterType::Does_not_contain:
            {
                filtered = p.first.find(pattern) == std::string::npos;
                break;
            }
            
            default:
                break;
        }
        if (filtered) result.push_back(&p.second);
    }
    return result;
}

} // namespace sfex
