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
template<typename U>
Vector<VECTOR_TEMPLATE_ARGS>::Vector(const Vector<N, U>& source) noexcept: m_components(source.getComponents())
{
}

VECTOR_TEMPLATE
template<std::size_t M, typename U>
Vector<VECTOR_TEMPLATE_ARGS>::Vector(const Vector<M, U>& source) noexcept: m_components()
{
    std::size_t minSize = MINSIZE(M, N);
    for(unsigned int i = 0; i < minSize; ++i)
    {
        m_components.at(i) = static_cast<T>(source.getComponents()[i]);
    }
}

VECTOR_TEMPLATE
Vector<VECTOR_TEMPLATE_ARGS>::Vector(std::initializer_list<T> components) noexcept: m_components()
{
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

VECTOR_TEMPLATE
const T& Vector<VECTOR_TEMPLATE_ARGS>::operator[](std::size_t index) const noexcept
{
    return m_components[index];
}

VECTOR_TEMPLATE
T& Vector<VECTOR_TEMPLATE_ARGS>::operator[](std::size_t index) noexcept
{
    return m_components[index];
}

VECTOR_TEMPLATE
T Vector<VECTOR_TEMPLATE_ARGS>::magnitude2() const noexcept
{
    return this->dot(*this);
}

VECTOR_TEMPLATE
T Vector<VECTOR_TEMPLATE_ARGS>::magnitude() const noexcept
{
    return std::sqrt( this->magnitude2() );
}

VECTOR_TEMPLATE
void Vector<VECTOR_TEMPLATE_ARGS>::setMagnitude(const T& newMag)
{
    // Replace with this
    // this->scale(newMag / magnitude());

    T mag = this->magnitude();

    for(auto& component : m_components)
    {
        component *= (newMag / mag);
    }
}

VECTOR_TEMPLATE
template<std::size_t M, typename U>
T Vector<VECTOR_TEMPLATE_ARGS>::dot(const Vector<M, U>& other) const noexcept
{
    T sum = 0;
    std::size_t minSize = MINSIZE(N, other.size);

    for(std::size_t i = 0; i < minSize; ++i)
    {
        sum +=  this->getComponents()[i] * other.getComponents()[i];
    }

    return sum;
}

VECTOR_TEMPLATE
void Vector<VECTOR_TEMPLATE_ARGS>::normalize() noexcept
{
    this->setMagnitude(1);
}

VECTOR_TEMPLATE
Vector<VECTOR_TEMPLATE_ARGS> Vector<VECTOR_TEMPLATE_ARGS>::normalized() const noexcept
{
    Vector<VECTOR_TEMPLATE_ARGS> copy = *this;
    copy.normalize();
    return copy;
}

VECTOR_TEMPLATE
template<typename U>
std::enable_if_t<N==2, std::common_type_t<T, U>> Vector<VECTOR_TEMPLATE_ARGS>::cross(const Vector<2, U>& other) const noexcept
{
    return ( (*this)[0] * other[1] - (*this)[1] * other[0] );
}

VECTOR_TEMPLATE
template<typename U>
std::enable_if_t<N==3, Vector<3, std::common_type_t<T, U>>> Vector<VECTOR_TEMPLATE_ARGS>::cross(const Vector<3, U>& other) const noexcept
{
    return {
        (*this)[1] * other[2] - (*this)[2] * other[1],
        (*this)[2] * other[0] - (*this)[0] * other[2],
        (*this)[0] * other[1] - (*this)[1] * other[0]
    };
}

VECTOR_TEMPLATE
template<std::size_t M, typename U>
bool Vector<N, T>::operator==(const Vector<M, U>& other) const noexcept
{
    if constexpr (N != M) return false;

    for(std::size_t i = 0; i < N; ++i)
    {
        if((*this)[i] != other[i]) return false;
    }
    return true;
}

VECTOR_TEMPLATE
template<std::size_t M, typename U>
bool Vector<N, T>::operator!=(const Vector<M, U>& other) const noexcept
{
    return !(*this == other);
}



}

#endif // !_SFEX_NUMERIC_VECTOR2_INL_