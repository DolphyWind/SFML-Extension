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

#include <SFEX/Managers/MusicManager.hpp>

namespace sfex
{

bool MusicManager::contains(const std::string &key) const
{
    return (m_musics.find(key) != m_musics.end());
}

std::size_t MusicManager::size() const
{
    return m_musics.size();
}

bool MusicManager::openFromFile(const std::string &key, const std::string &filename)
{
    sf::Music music;
    if(!music.openFromFile(filename)) return false;

    m_musics[key].openFromFile(filename);
    return true;
}

bool MusicManager::openFromMemory(const std::string &key, const void *data, std::size_t size)
{
    sf::Music music;
    if(!music.openFromMemory(data, size)) return false;

    m_musics[key].openFromMemory(data, size);
    return true;
}

bool MusicManager::openFromStream(const std::string &key, sf::InputStream &stream)
{
    sf::Music music;
    if(!music.openFromStream(stream)) return false;

    m_musics[key].openFromStream(stream);
    return true;
}

void MusicManager::play(const std::string &key)
{
    if(!this->get(key)) return;

    this->get(key)->play();
}

void MusicManager::pause(const std::string &key)
{
    if(!this->get(key)) return;

    this->get(key)->pause();
}

void MusicManager::stop(const std::string &key)
{
    if(!this->get(key)) return;

    this->get(key)->stop();
}

sf::Time MusicManager::getDuration(const std::string &key)
{
    if(!this->get(key)) return sf::Time::Zero;

    return this->get(key)->getDuration();
}

sf::Music::Status MusicManager::getStatus(const std::string &key)
{
    if(!this->get(key)) return sf::Music::Status::Stopped;

    return this->get(key)->getStatus();
}

sf::Music* MusicManager::get(const std::string &key)
{
    if(!contains(key)) return nullptr;

    return &m_musics[key];
}

std::vector<std::string> MusicManager:: getKeys() const
{
    std::vector<std::string> result;
    for(auto &p : m_musics)
    {
        result.push_back(p.first);
    }
    return result;
}

sf::Music* MusicManager::operator[](const std::string &key)
{
    return this->get(key);
}

std::vector<sf::Music*> MusicManager::filter(std::string pattern, sfex::FilterType method)
{
    std::vector<sf::Music*> result;
    for(auto &p : m_musics)
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
