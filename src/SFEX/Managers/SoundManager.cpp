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

#include <SFEX/Managers/SoundManager.hpp>

namespace sfex
{

bool SoundManager::loadFromFile(const std::string &key, const std::string &filename)
{
    m_buffers[key] = sf::SoundBuffer();
    if(!m_buffers[key].loadFromFile(filename)) return false;

    (*this)[key] = sf::Sound(m_buffers[key]);
    return true;
}

bool SoundManager::loadFromMemory(const std::string &key, const void *data, std::size_t size)
{
    m_buffers[key] = sf::SoundBuffer();
    if(!m_buffers[key].loadFromMemory(data, size)) return false;

    (*this)[key] = sf::Sound(m_buffers[key]);
    return true;
}

bool SoundManager::loadFromStream(const std::string &key, sf::InputStream &stream)
{
    m_buffers[key] = sf::SoundBuffer();
    if(!m_buffers[key].loadFromStream(stream)) return false;

    (*this)[key] = sf::Sound(m_buffers[key]);
    return true;
}

bool SoundManager::loadFromSamples(const std::string &key, const sf::Int16 *sample, sf::Uint64 sampleCount, unsigned int channelCount, unsigned int sampleRate)
{
    m_buffers[key] = sf::SoundBuffer();
    if(!m_buffers[key].loadFromSamples(sample, sampleCount, channelCount, sampleRate)) return false;

    (*this)[key] = sf::Sound(m_buffers[key]);
    return true;
}

void SoundManager::play(const std::string &key)
{
    if(!this->contains(key)) return;
    (*this)[key].play();
}

void SoundManager::pause(const std::string &key)
{
    if(!this->contains(key)) return;
    (*this)[key].pause();
}

void SoundManager::stop(const std::string &key)
{
    if(!this->contains(key)) return;
    (*this)[key].stop();
}

sf::Time SoundManager::getDuration(const std::string &key)
{
    if(!this->contains(key)) return sf::Time::Zero;
    return (*this)[key].getBuffer()->getDuration();
}

sf::Sound::Status SoundManager::getStatus(const std::string &key)
{
    if(!this->contains(key)) return sf::Sound::Status::Stopped;
    return (*this)[key].getStatus();
}

} // namespace sfex
