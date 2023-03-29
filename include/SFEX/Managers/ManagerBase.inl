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

#include <SFEX/Managers/MangerBase.hpp>

namespace sfex
{

template<typename T>
bool ManagerBase<T>::contains(const std::string &key) const
{
    return (m_hashmap.find(key) != m_hashmap.end());
}

template<typename T>
std::size_t ManagerBase<T>::size() const
{
    return m_hashmap.size();
}

template<typename T>
bool ManagerBase<T>::empty() const
{
    return m_hashmap.empty();
}

template<typename T>
typename ManagerBase<T>::iterator ManagerBase<T>::begin()
{
    return m_hashmap.begin();
}

template<typename T>
typename ManagerBase<T>::iterator ManagerBase<T>::end()
{
    return m_hashmap.end();
}

template<typename T>
typename ManagerBase<T>::const_iterator ManagerBase<T>::cbegin()
{
    return m_hashmap.cbegin();
}

template<typename T>
typename ManagerBase<T>::const_iterator ManagerBase<T>::cend()
{
    return m_hashmap.cend();
}

template<typename T>
T& ManagerBase<T>::at(const std::string &key)
{
    return m_hashmap.at(key);
}

template<typename T>
std::vector<std::string> ManagerBase<T>::keys() const
{
    std::vector<std::string> result;
    for(auto &p : m_hashmap)
    {
        result.push_back(p.first);
    }
    return result;
}

template<typename T>
T& ManagerBase<T>::operator[](const std::string& key)
{
    return m_hashmap[key];
}

template<typename T>
std::vector<std::string> ManagerBase<T>::filter(std::string pattern, ManagerBase<T>::FilterType method)
{
    std::vector<std::string> result;
    for(auto &p : m_hashmap)
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
        if (filtered) result.push_back(p.first);
    }
    return result;
}

template<typename T>
void ManagerBase<T>::remove(const std::string &key)
{
    if(!this->contains(key)) return;
    m_hashmap.erase(key);
}

template<typename T>
void ManagerBase<T>::remove(const std::vector<std::string> &keys)
{
    for(auto &key : keys)
    {
        m_hashmap.erase(key);
    }
}

template<typename T>
void ManagerBase<T>::clear()
{
    m_hashmap.clear();  
}

template<typename T>
void ManagerBase<T>::insert(const std::pair<std::string, T> &pair)
{
    m_hashmap.insert(pair);
}

} // namespace sfex
