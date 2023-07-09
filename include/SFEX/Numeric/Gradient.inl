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

#pragma once
#include <SFEX/Numeric/Gradient.hpp>
#include <iostream>

namespace sfex
{

template<typename T, typename AdderType, typename MultiplierType>
void Gradient<T, AdderType, MultiplierType>::setKey(float time, const T& key)
{
    m_gradientMap[time] = key;
}

template<typename T, typename AdderType, typename MultiplierType>
void Gradient<T, AdderType, MultiplierType>::removeKey(const T& value)
{
    m_gradientMap.erase(value);
}

template<typename T, typename AdderType, typename MultiplierType>
void Gradient<T, AdderType, MultiplierType>::removeKey(float time)
{
    m_gradientMap.erase(time);
}

template<typename T, typename AdderType, typename MultiplierType>
std::map<float, T> Gradient<T, AdderType, MultiplierType>::getKeys()
{
    return m_gradientMap;
}

template<typename T, typename AdderType, typename MultiplierType>
T Gradient<T, AdderType, MultiplierType>::evaluate(float time)
{
    std::pair<float, T> pairBefore, pairAfter;
    bool pairFound = false;

    for(auto it = m_gradientMap.begin(); it != m_gradientMap.end(); ++it)
    {
        const auto& pair = *it;
        if(pair.first >= time)
        {
            if(it == m_gradientMap.begin()) return pair.second;
            pairAfter = pair;
            pairBefore = *(--it);
            pairFound = true;
            break;
        }
    }
    if(!pairFound)
    {
        auto it = m_gradientMap.end();
        --it;
        return it->second;
    }

    float leftDistance = time - pairBefore.first;
    float rightDistance = pairAfter.first - time;
    float lerpTime = leftDistance / (leftDistance + rightDistance);
    return sfex::Math::lerp<T, AdderType, MultiplierType>(pairBefore.second, pairAfter.second, lerpTime);
}

template<typename T, typename AdderType, typename MultiplierType>
T Gradient<T, AdderType, MultiplierType>::operator()(float time)
{
    return this->evaluate(time);
}

template<typename T, typename AdderType, typename MultiplierType>
T &Gradient<T, AdderType, MultiplierType>::operator[](float time)
{
    return m_gradientMap[time];
}

} // namespace sfex
