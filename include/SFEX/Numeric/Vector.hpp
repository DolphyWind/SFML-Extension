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

#define VECTOR_TEMPLATE template<std::size_t N, typename T>
#define VECTOR_TEMPLATE_ARGS N, T

namespace sfex
{

namespace impl
{
    template <std::size_t A, std::size_t B>
    struct MinValue {
        static constexpr std::size_t value = std::conditional<(A < B), std::integral_constant<int, A>, std::integral_constant<int, B>>::type::value;
    };
}

/// @brief A class that represents N-Dimesional mathematical vectors.
/// @tparam N The dimension count of the vector
/// @tparam T Type of the components of the vector
template<std::size_t N, class T>
class Vector
{
public:
    using component_type = T;
    static const std::size_t size = N;

    /// @brief Copy constructor for Vectors.
    /// @tparam U The component type of the source vector
    /// @param source Vector to copy
    template<typename U>
    Vector(const Vector<N, U>& source) noexcept;

    /// @brief Copy constructor for Vectors
    /// @tparam M The dimension count of the source vector
    /// @tparam U The component type of the source vector
    /// @param source Vector to copy
    template<std::size_t M, typename U>
    Vector(const Vector<M, U>& source) noexcept;

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

    /// @brief Returns a const reference to the component that corresponds to given index.
    /// @param index Index of the component that you want to get.
    /// @return Const reference to the component that corresponds to given index.
    [[nodiscard]] const T& operator[](std::size_t index) const noexcept;

    /// @brief Returns a const reference to the component that corresponds to given index.
    /// @param index Index of the component that you want to get.
    /// @return Const reference to the component that corresponds to given index.
    [[nodiscard]] T& operator[](std::size_t index) noexcept;

    /// @brief Returns the magnitude of the vector squared
    /// @return The magnitude of the vector squared
    [[nodiscard]] T magnitude2() const;

    /// @brief Returns the magnitude of the vector
    /// @return The magnitude of the vector
    [[nodiscard]] T magnitude() const;

    /// @brief Sets the magnitude of the vector to given magnitude.
    /// @param newMag New magnitude.
    void setMagnitude(const T& newMag);

    /// @brief Computes the dot product between this vector and the given vector. It dots first min(this->size(), other.size()) dimensions since the other ones will result zero.
    /// @param other Vector to dot.
    /// @return Result of the dot product between this and other.
    template<std::size_t M, typename U>
    [[nodiscard]] T dot(const Vector<M, U>& other) const;

    /// @brief Normalizes the vector.
    void normalize();

    /// @brief Returns the normalized version of the vector.
    [[nodiscard]] Vector<N, T> normalized() const;

    /// @brief Computes the cross product between two 2D vectors. Interprets them as 3D vector, computes the cross product and returns the z component of the resulting vector.
    /// @param other Other vector.
    /// @return Result of the cross product.
    template<typename U>
    [[nodiscard]] std::enable_if_t<N==2, std::common_type_t<T, U>> cross(const Vector<2, U>& other) const;

    /// @brief Computes the cross product between two 3D vectors.
    /// @param other Other vector.
    /// @return Result of the cross product.
    template<typename U>
    [[nodiscard]] std::enable_if_t<N==3, Vector<3, std::common_type_t<T, U>>> cross(const Vector<3, U>& other) const;

    /// @brief Computates component-wise multiplication aka the hadamard multiplication between two vectors
    /// @param rhs rhs vector
    /// @return Result of component-wise multiplication.
    template<std::size_t M, typename U>
    [[nodiscard]] Vector<impl::MinValue<N, M>::value, std::common_type_t<T, U>> cwiseMul(const Vector<M, U>& rhs) const;

    /// @brief Computates component-wise division aka the hadamard division between two vectors
    /// @param rhs rhs vector
    /// @return Result of component-wise division.
    template<std::size_t M, typename U>
    [[nodiscard]] Vector<impl::MinValue<N, M>::value, std::common_type_t<T, U>> cwiseDiv(const Vector<M, U>& rhs) const;

    /// @brief Scales the vector with a scalar
    /// @param scalar scalar
    template<typename V>
    void scale(const V& scalar);

    /// @brief Returns a scaled version of the vector
    /// @param scalar scalar
    /// @return Scaled version of the vector
    template<typename V>
    Vector<VECTOR_TEMPLATE_ARGS> scaled(const V& scalar) const;

    template<std::size_t M, typename U>
    bool operator==(const Vector<M, U>& other) const noexcept;

    template<std::size_t M, typename U>
    bool operator!=(const Vector<M, U>& other) const noexcept;

private:
    std::array<T, N> m_components;
};

}

#include <SFEX/Numeric/Vector.inl>

#endif // !_SFEX_NUMERIC_VECTOR_HPP_
