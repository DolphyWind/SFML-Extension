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
#ifndef _SFEX_NUMERIC_VECTOR2_INL_
#define _SFEX_NUMERIC_VECTOR2_INL_

#include <SFEX/Numeric/Vector.hpp>

namespace sfex
{

VECTOR_TEMPLATE
template<typename U, typename... Functors>
Vector<VECTOR_TEMPLATE_ARGS>::Vector(const Vector<N, U, Functors...>& source) noexcept: m_components(source.getComponents())
{
}

VECTOR_TEMPLATE
template<std::size_t M, typename U, typename... Functors>
Vector<VECTOR_TEMPLATE_ARGS>::Vector(const Vector<M, U, Functors...>& source) noexcept: m_components()
{
    std::size_t minSize = (M < N) ? (M) : (N);
    for(unsigned int i = 0; i < minSize; ++i)
    {
        m_components.at(i) = static_cast<T>(source.getComponents()[i]);
    }
}

VECTOR_TEMPLATE
Vector<VECTOR_TEMPLATE_ARGS>::Vector(std::initializer_list<T> components) noexcept: m_components()
{
    const std::size_t componentsSize = components.size();

    std::size_t i = 0;
    for(auto& component : components)
    {
        if(i == N) break;
        m_components.at(i) = component;
        ++i;
    }
}

VECTOR_TEMPLATE
Vector<VECTOR_TEMPLATE_ARGS>::Vector() noexcept: m_components()
{
}

VECTOR_TEMPLATE
const std::array<T, N>& Vector<VECTOR_TEMPLATE_ARGS>::getComponents() const noexcept
{
    return m_components;
}

VECTOR_TEMPLATE
std::array<T, N>& Vector<VECTOR_TEMPLATE_ARGS>::getComponents() noexcept
{
    return m_components;
}

VECTOR_TEMPLATE
T const* const Vector<VECTOR_TEMPLATE_ARGS>::getComponentsPtr() const noexcept
{
    return m_components.data();
}


VECTOR_TEMPLATE
T* Vector<VECTOR_TEMPLATE_ARGS>::getComponentsPtr() noexcept
{
    return m_components.data();
}

}


#endif // !_SFEX_NUMERIC_VECTOR2_INL_