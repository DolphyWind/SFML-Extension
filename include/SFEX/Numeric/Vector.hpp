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
#ifndef _SFEX_NUMERIC_VECTOR_HPP_
#define _SFEX_NUMERIC_VECTOR_HPP_

#include <array>
#include <SFEX/Numeric/Math.hpp>

#define VECTOR_TEMPLATE template<std::size_t N, class T, class AdderType, class SubtracterType, class MultiplierType, class DividerType, class SqrtTakerType>
#define VECTOR_TEMPLATE_ARGS N, T, AdderType, SubtracterType, MultiplierType, DividerType, SqrtTakerType

namespace sfex
{

/// @brief A class that represents N-Dimesional mathematical vectors.
/// @tparam N The dimension count of the vector
/// @tparam T Type of the components of the vector
/// @tparam AdderType An adder functor for type T
/// @tparam SubtracterType A subtracter functor for type T
/// @tparam MultiplierType A multiplier functor for type T
/// @tparam DividerType A divider functor for type T
template<std::size_t N, class T, class AdderType=Math::Adder<T, T>, class SubtracterType=Math::Subtracter<T, T>, class MultiplierType=Math::Multiplier<T, T>, class DividerType=Math::Divider<T, T>, class SqrtTakerType=Math::SqrtTaker<T>>
class Vector
{
public:
    using adder_type = AdderType;
    using subtracter_type = SubtracterType;
    using multiplier_type = MultiplierType;
    using divider_type = DividerType;
    using component_type = T;

    /// @brief Copy constructor for Vectors.
    /// @tparam U The component type of the source vector
    /// @param source Vector to copy
    template<typename U, typename... Functors>
    Vector(const Vector<N, U, Functors...>& source) noexcept;

    /// @brief Copy constructor for Vectors
    /// @tparam M The dimension count of the source vector
    /// @tparam U The component type of the source vector
    /// @param source Vector to copy
    template<std::size_t M, typename U, typename... Functors>
    Vector(const Vector<M, U, Functors...>& source) noexcept;

    /// @brief Create a vector with initial values.
    /// @param components Components of the vector
    Vector(std::initializer_list<T> components) noexcept;

    /// @brief Creates an empty vector
    Vector() noexcept;

    /// @brief Returns a const reference to the array holding the components of the vector
    /// @return A const reference to the array holding the components of the vector
    [[nodiscard]] const std::array<T, N>& getComponents() const noexcept;

    /// @brief Returns a reference to the array holding the components of the vector
    /// @return A reference to the array holding the components of the vector
    [[nodiscard]] std::array<T, N>& getComponents() noexcept;

    /// @brief Returns a const pointer to the beggining of the array holding the components of the vector
    /// @return A const pointer to the beggining of the array holding the components of the vector
    [[nodiscard]] T const * const getComponentsPtr() const noexcept;

    /// @brief Returns pointer to the beggining of the array holding the components of the vector
    /// @return A pointer to the beggining of the array holding the components of the vector
    [[nodiscard]] T* getComponentsPtr() noexcept;

private:
    std::array<T, N> m_components;
};



}

#include <SFEX/Numeric/Vector.inl>

#endif // !_SFEX_NUMERIC_VECTOR_HPP_
