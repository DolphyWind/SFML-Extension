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

#ifndef _SFEX_MANAGERS_MANAGERBASE_HPP_
#define _SFEX_MANAGERS_MANAGERBASE_HPP_

#include <string>
#include <vector>
#include <unordered_map>
#include <optional>

namespace sfex
{

/// @brief Base manager class. Stores <std::string, T> pairs in a hashmap aka std::unordered_map
template<typename T>
class ManagerBase : public std::unordered_map<std::string, T>
{
public:

    enum class FilterType
    {
        Starts_with,
        Ends_with,
        Contains,
        Does_not_contain,
    };
    
    /// @brief A function to check if the key is present in the hashmap
    /// @param key Key to check
    /// @return true if the key is present in the hashmap
    bool contains(const std::string &key) const;

    /// @brief Get all keys
    /// @return All keys in a vector
    std::vector<std::string> keys() const;

    /// @brief Filter each key by pattern and method then return matching keys
    /// @param pattern Pattern to look for while filtering
    /// @param method Filtering method to use while filtering
    /// @return Keys that are filtered
    std::vector<std::string> filter(std::string pattern, FilterType method);

    /// @brief Remove a key from the hashmap
    /// @param key Key to remove
    void remove(const std::string &key);

    /// @brief Remove multiple keys from the hashmap
    /// @param keys Keys to remove
    void remove(const std::vector<std::string> &keys);
};

} // namespace sfex

#include <SFEX/Managers/ManagerBase.inl>
#endif // !_SFEX_MANAGERS_MANAGERBASE_HPP_