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

#include <SFEX/Managers/SpriteManager.hpp>

namespace sfex
{

bool SpriteManager::contains(const std::string &key) const
{
    return (m_sprites.find(key) != m_sprites.end());
}

std::size_t SpriteManager::size() const
{
    return m_sprites.size();
}

void SpriteManager::setTexture(const std::string &key, const sf::Texture& texture)
{
    if(contains(key))
    {
        this->get(key)->setTexture(texture);
        return;
    }
    m_sprites[key] = sf::Sprite(texture);
}

sf::Sprite* SpriteManager::get(const std::string &key)
{
    if(!contains(key)) return nullptr;
    return &m_sprites[key];
}

std::vector<std::string> SpriteManager::getKeys() const
{
    std::vector<std::string> result;
    for(auto &p : m_sprites)
    {
        result.push_back(p.first);
    }
    return result;
}

sf::Sprite* SpriteManager::operator[](const std::string& key)
{
    return this->get(key);
}

std::vector<sf::Sprite*> SpriteManager::filter(std::string pattern, sfex::FilterType method)
{
    std::vector<sf::Sprite*> result;
    for(auto &p : m_sprites)
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
