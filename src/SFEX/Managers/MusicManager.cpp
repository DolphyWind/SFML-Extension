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

#include <SFEX/Managers/MusicManager.hpp>

namespace sfex
{

bool MusicManager::openFromFile(const std::string &key, const std::string &filename)
{
    sf::Music music;
    if(!music.openFromFile(filename)) return false;

    m_hashmap[key].openFromFile(filename);
    return true;
}

bool MusicManager::openFromMemory(const std::string &key, const void *data, std::size_t size)
{
    sf::Music music;
    if(!music.openFromMemory(data, size)) return false;

    m_hashmap[key].openFromMemory(data, size);
    return true;
}

bool MusicManager::openFromStream(const std::string &key, sf::InputStream &stream)
{
    sf::Music music;
    if(!music.openFromStream(stream)) return false;

    m_hashmap[key].openFromStream(stream);
    return true;
}

void MusicManager::play(const std::string &key)
{
    if(!this->contains(key)) return;
    m_hashmap[key].play();
}

void MusicManager::pause(const std::string &key)
{
    if(!this->contains(key)) return;
    m_hashmap[key].pause();
}

void MusicManager::stop(const std::string &key)
{
    if(!this->contains(key)) return;
    m_hashmap[key].stop();
}

sf::Time MusicManager::getDuration(const std::string &key)
{
    if(!this->contains(key)) return sf::Time::Zero;
    return m_hashmap[key].getDuration();
}

sf::Music::Status MusicManager::getStatus(const std::string &key)
{
    if(!this->contains(key)) return sf::Music::Status::Stopped;
    return m_hashmap[key].getStatus();
}

} // namespace sfex
